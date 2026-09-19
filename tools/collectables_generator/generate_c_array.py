import os
import json

output_str: str = "#include <ap_collectables_array.h>\n"
output_str += "#include <hashcodes.h>\n\n"
output_str += "APCollectable g_ap_collectables[] = {\n"

in_dicts: dict[str, list[dict[str, int | float | str | dict[str, int]]]] = {}

for entry in os.scandir("arrays"):
    if entry.is_file():
        region_name = entry.name.replace(".json", "")
        filepath = entry.path
        with open(filepath, 'r+t') as file:
            in_dicts[region_name] = json.loads(file.read())

in_dicts = dict(sorted(in_dicts.items()))

curr_index = 0
for region_name, entries in in_dicts.items():
    # Remove the sorting numbers and replace underscores
    cleaned_region_name = region_name[3:].replace("_", " ")

    output_str += "\t#pragma region "+cleaned_region_name+"\n"

    for entry in entries:
        if "comment" in entry.keys():
            index_str = str(curr_index).rjust(3)
            m_comment = entry["comment"]
            assert isinstance(m_comment, str)
            output_str += "\t// ["+index_str+"] "+m_comment+"\n"

        output_str += "\t{\n"
        curr_index += 1

        m_type = entry["type"]
        assert isinstance(m_type, str)
        output_str += "\t\t.type = "+m_type+",\n"

        m_map_index = entry["map_index"]
        assert isinstance(m_map_index, int)
        output_str += "\t\t.map_index = "+str(m_map_index)+",\n"

        # probably the ugliest code i've ever written
        m_trig_index = entry["trig_index"]
        assert isinstance(m_trig_index, dict)
        separate_builds = False
        prev_v: int | None = None
        for k, v in m_trig_index.items():
            if prev_v is None:
                prev_v = v
                continue
            else:
                if v != prev_v:
                    separate_builds = True
                    break
                prev_v = v
        if separate_builds:
            first = True
            for k, v in m_trig_index.items():
                if first:
                    first = False
                    output_str += "#if defined("+k+")\n"
                else:
                    output_str += "#elif defined("+k+")\n"
                output_str += "\t\t.trig_index = "+str(v)+",\n"
            output_str += "#endif\n"
        else:
            output_str += "\t\t.trig_index = "+str(prev_v)+",\n"

        if "objective" in entry.keys():
            m_objective = entry["objective"]
            assert isinstance(m_objective, str)
            output_str += "\t\t.objective = "+m_objective+" & 0xFFFF,\n"
        else:
            output_str += "\t\t.objective = 0xFFFF,\n"

        if "x" in entry.keys():
            m_x = entry["x"]
            assert isinstance(m_x, float)
            output_str += "\t\t.x = "+str(m_x)+"f,\n"

        if "z" in entry.keys():
            m_z = entry["z"]
            assert isinstance(m_z, float)
            output_str += "\t\t.z = "+str(m_z)+"f\n"

        output_str += "\t},\n"

    output_str += "\t#pragma endregion /* "+cleaned_region_name+" */\n"

# Remove the last comma in the array
last_comma_pos = output_str.rfind(",")
if last_comma_pos != -1:
    output_str = output_str[:last_comma_pos] + output_str[last_comma_pos + 1:]

output_str += "};\n"

with open("../../src/ap_collectables_array.c", 'w+t') as file:
    file.write(output_str)
