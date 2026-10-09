import yaml

yamlpath = "symbols/symbols.yaml"
outputpath = "symbols"

yamlsyms: dict[str, dict[str, dict[str, int]]] = {}
with open(yamlpath) as file:    
    yamlsyms = yaml.load(file, yaml.SafeLoader)


class WorkingFile:
    def __init__(self, filepath) -> None:
        self.file = open(filepath, 'w+t')
        self.begin_new_header = True

    def close(self):
        self.file.close()

    def writeline(self, string: str | None = None):
        if string is None:
            self.file.write("\n")
        else:
            self.file.write(string+"\n")


files: dict[str, WorkingFile] = {}
try:
    for header, symbol in yamlsyms.items():
        for symbol_name, locations in symbol.items():
            for build_ver_name, address in locations.items():
                if build_ver_name not in files:
                    files[build_ver_name] = WorkingFile(f"{outputpath}/{build_ver_name}.txt")
                currfile = files[build_ver_name]
                if currfile.begin_new_header:
                    currfile.writeline(f"/* {header} */")
                    currfile.begin_new_header = False
                currfile.writeline(f"{symbol_name} = {hex(address)};")

        # Write newline to every current file
        for f in files.values():
            if not f.begin_new_header:
                f.writeline()
                f.begin_new_header = True
                
finally:
    for f in files.values():
        f.close()
