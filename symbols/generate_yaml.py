import yaml
from os import listdir
from sys import exit

# If run, this will overwrite the current yaml file.
# Only comment out this exit statement if you know what you're doing.
exit(0)

inputpath = "symbols"
outputfile = "symbols/symbols.yaml"

class HexDumper(yaml.SafeDumper):
    pass

def represent_hex(dumper: yaml.SafeDumper, value):
    return dumper.represent_scalar(
        "tag:yaml.org,2002:int",
        hex(value)
    )

HexDumper.add_representer(int, represent_hex)

txtfiles: dict[str, list[str]] = {}
for p in listdir(inputpath):
    if p.endswith('.txt'):
        with open(f"{inputpath}/{p}", 'r+t') as file:
            txtfiles[p[:-4]] = file.read().splitlines()

if len(txtfiles) == 0:
    print("No symbol files to generate from.")
    exit(0)

output: dict[str, dict[str, dict[str, int]]] = {}

for build_ver, text in txtfiles.items():
    curr_header = ""
    for line in text:
        if line.startswith("/*"):
            header = line.strip()[3:][:-3].strip()
            curr_header = header
            if header not in output:
                output[header] = {}
        elif curr_header == "":
            continue

        split = line.replace(';', '').split('=')
        if len(split) < 2:
            continue

        symbol = split[0].strip()
        address = int(split[1].strip()[2:], 16)

        if symbol not in output[curr_header]:
            output[curr_header][symbol] = {}

        output[curr_header][symbol][build_ver] = address

with open(outputfile, 'w+t') as file:
    yaml.dump(output, file, HexDumper)
