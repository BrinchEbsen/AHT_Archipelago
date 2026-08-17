import os
import json

output_str: str = "#include <ap_collectables_array.h>\n"
output_str += "#include <hashcodes.h>\n\n"
output_str += "APCollectable g_ap_collectables[] = {\n"

in_dicts: dict[str, list[dict[str, int | float | str]]] = {}

for entry in os.scandir("arrays"):
    if entry.is_file():
        region_name = entry.name.replace(".json", "")
        filepath = entry.path
        with open(filepath, 'r+t') as file:
            in_dicts[region_name] = json.loads(file.read())

in_dicts = dict(sorted(in_dicts.items()))

for region_name, entries in in_dicts.items():
    # Remove the sorting numbers and replace underscores
    cleaned_region_name = region_name[3:].replace("_", " ")

    output_str += "\t#pragma region "+cleaned_region_name+"\n"

    for entry in entries:
        if "comment" in entry.keys():
            m_comment = entry["comment"]
            assert isinstance(m_comment, str)
            output_str += "\t// "+m_comment+"\n"

        output_str += "\t{\n"

        m_type = entry["type"]
        assert isinstance(m_type, str)
        output_str += "\t\t.type = "+m_type+",\n"

        m_map_index = entry["map_index"]
        assert isinstance(m_map_index, int)
        output_str += "\t\t.map_index = "+str(m_map_index)+",\n"

        m_trig_index = entry["trig_index"]
        assert isinstance(m_trig_index, int)
        output_str += "\t\t.trig_index = "+str(m_trig_index)+",\n"

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
