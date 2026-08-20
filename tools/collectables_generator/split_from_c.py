import json

in_file = '../../src/ap_collectables_array.c'
out_dir = 'arrays'

str_pragma_region = "#pragma region"
str_pragma_endregion = "#pragma endregion"

curr_file_index: int = 0
curr_file: str | None = None
curr_entry: dict[str, int | float | str] | None = None
curr_entry_index: int = 0
curr_comment: str | None = None

outputs: dict[str, list[dict[str, int | float | str]]] = {}


def get_struct_value_string(line: str, name: str) -> str | None:
    if line.find("."+name) == -1:
        return None

    split_l = line.split('=')

    if len(split_l) < 2:
        return None

    val_str = split_l[1].strip()
    if val_str.endswith(','):
        val_str = val_str.rstrip(',')

    return val_str


with open(in_file) as file:
    for line in file:
        # Start a new file if needed
        region_idx = line.find(str_pragma_region)
        if region_idx != -1:
            curr_file = line[
                region_idx+len(str_pragma_region)+1:].strip().replace(' ', '_')
            # Add an index to the name to sort it when generating
            curr_file = str(curr_file_index).rjust(2, "0") + "_" + curr_file
            outputs[curr_file] = []

        # If we're not in a file, wait until we are
        if curr_file is None:
            continue

        # Close current file if we're at the end
        endregion_idx = line.find(str_pragma_endregion)
        if endregion_idx != -1:
            curr_file = None
            curr_file_index += 1
            continue

        comment_split = line.split("//")
        if len(comment_split) >= 2:
            curr_comment = comment_split[1].strip()

        if line.find("{") != -1:
            curr_entry = {}
            curr_entry["index"] = curr_entry_index
            curr_entry_index += 1
            continue

        if curr_entry is not None:
            val_str = get_struct_value_string(line, "type")
            if val_str is not None:
                curr_entry["type"] = val_str

            val_str = get_struct_value_string(line, "map_index")
            if val_str is not None:
                curr_entry["map_index"] = int(val_str)

            val_str = get_struct_value_string(line, "trig_index")
            if val_str is not None:
                curr_entry["trig_index"] = int(val_str)

            val_str = get_struct_value_string(line, "objective")
            if val_str is not None:
                if val_str != "0xFFFF":
                    curr_entry["objective"] = val_str.split()[0]

            val_str = get_struct_value_string(line, "x")
            if val_str is not None:
                val_str = val_str.rstrip('f')
                curr_entry["x"] = float(val_str)

            val_str = get_struct_value_string(line, "z")
            if val_str is not None:
                val_str = val_str.rstrip('f')
                curr_entry["z"] = float(val_str)

            # Add new entry to the file
            if line.find("}") != -1:
                if curr_comment is not None:
                    curr_entry["comment"] = curr_comment
                    curr_comment = None
                outputs[curr_file].append(curr_entry)
                curr_entry = None

for filename, items in outputs.items():
    with open("arrays/"+filename+".json", 'w+t') as file:
        file.write(json.dumps(items, indent=4))
