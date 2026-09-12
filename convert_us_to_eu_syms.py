import sys

if len(sys.argv) < 3:
    print("Usage: python convert_us_to_eu_syms.py [NTSC .map file path] [PAL .map file path]")
    sys.exit(0)

us_map_file = sys.argv[1]
eu_map_file = sys.argv[2]
us_sym_file = "symbols/GC_NTSC.txt"
eu_sym_file = "symbols/GC_PAL.txt"


class MapEntry:
    def __init__(self, name: str, addr: int) -> None:
        self.name = name
        self.addr = addr


def get_map_entries(file_path: str) -> list[MapEntry]:
    entries: list[MapEntry] = []
    with open(file_path) as file:
        lines = file.readlines()
        for line in lines:
            split = line.split()
            if len(split) < 5:
                continue
            addr = int(split[0], 16)
            name = line[29:]
            entries.append(MapEntry(name, addr))
    return entries


us_map_entries = get_map_entries(us_map_file)
eu_map_entries = get_map_entries(eu_map_file)


def find_equivalent_eu_address(addr: int) -> int | None:
    global us_map_entries
    global eu_map_entries

    found_entry: MapEntry | None = None
    for entry in us_map_entries:
        if entry.addr == addr:
            found_entry = entry

    if found_entry is None:
        return None

    for entry in eu_map_entries:
        if found_entry.name == entry.name:
            return entry.addr

    return None


us_sym_lines: list[str] = []
eu_sym_lines: list[str] = []

with open(us_sym_file) as file:
    us_sym_lines = file.readlines()

for line in us_sym_lines:
    split = line.split()
    if len(split) >= 3:
        if "/*" not in split[0]:
            addr_str = split[2]
            addr = int(addr_str.replace("0x", "").replace(";", ""), 16)
            eq_addr = find_equivalent_eu_address(addr)
            if eq_addr is not None:
                line = line.replace(addr_str, hex(eq_addr)+";")
            else:
                line = line.replace(addr_str, "0x;")

    eu_sym_lines.append(line)

with open(eu_sym_file, 'w+t') as file:
    file.writelines(eu_sym_lines)
