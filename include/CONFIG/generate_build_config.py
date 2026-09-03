import json
from typing import TypedDict

# Generates the "build_config.h" file for the mod's build options.
# Options are derived from "build_config_settings.json".
# REMEMBER TO SET THE VERSION NUMBER AFTER GENERATING, IT INITIALIZES AS 0.0!

col1_offs = 56
col2_offs = col1_offs+8
col3_offs = col2_offs+44

settings_json_file = "build_config_settings.json"
build_config_h = "build_config.h"

pre_setting_define_prefix = "_build_config_"

class Setting(TypedDict):
    name: str
    description: str
    default_value: int

class SettingsJson(TypedDict):
    general: list[Setting]
    debug: list[Setting]


def generate_separator_comment(width: int, header: str | None = None, header_offs: int | None = None) -> str:
    if header is None or header_offs is None:
        return '// '+('-'*(width-3))
    else:
        width -= 3 # Subtract "// "
        header_len = len(header)+2 # Space on either side
        header_start = header_offs-4 # Subtract "// " and the first space
        string = '// '+('-'*header_start)+' '+header+' '
        return string+('-'*(width-(header_start+header_len)))


def create_pre_setting_define(setting: Setting, debug: bool = False) -> str:
    string = '#define '
    string += pre_setting_define_prefix+setting['name']
    string = string.ljust(col1_offs)
    string += str(setting['default_value'])
    string = string.ljust(col2_offs) + '// '
    if debug:
        string += '[DEBUG] '
    string += setting['description']
    return string


def create_post_setting_define(setting: Setting, value_override: int | None = None) -> str:
    string = '#ifndef '+setting['name']+'\n'
    if value_override is None:
        string += '#define '+setting['name']+' '+pre_setting_define_prefix+setting['name']+'\n'
    else:
        string += '#define '+setting['name']+' '+str(value_override)+'\n'
    string += '#endif /* '+setting['name']+' */\n'
    return string


settings: SettingsJson | None = None

with open(settings_json_file) as file:
    settings = json.loads(file.read())

assert settings is not None

with open(build_config_h, 'w+t') as file:
    # Header
    file.writelines([
        '#ifndef AP_BUILD_CONFIG_H\n',
        '#define AP_BUILD_CONFIG_H\n\n',
        '/*\n',
        ' * General build configuration for the mod.\n',
        ' * Settings can be overridden with compiler flags.\n',
        ' * Debug options can be forced off with "-D AP_DEBUG_ENABLE=0".\n',
        ' */\n\n'
    ])

    # General options
    file.write(generate_separator_comment(col3_offs, "OPTIONS (GENERAL)", col1_offs)+'\n')
    for opt in settings['general']:
        file.write(create_pre_setting_define(opt)+'\n')
    # Debug options
    file.write(generate_separator_comment(col3_offs, "OPTIONS (DEBUG)", col1_offs)+'\n')
    for opt in settings['debug']:
        file.write(create_pre_setting_define(opt)+'\n')
    file.write(generate_separator_comment(col3_offs)+('\n'*6))

    # Create general option defines
    for opt in settings['general']:
        file.write(create_post_setting_define(opt))
    # Create debug option defines (if enabled)
    file.write('#if AP_DEBUG_ENABLE != 0\n')
    for opt in settings['debug']:
        file.write(create_post_setting_define(opt))
    # Create debug option defines (forced to zero)
    file.write('#else /* AP_DEBUG_ENABLE != 0 */\n')
    for opt in settings['debug']:
        file.write(create_post_setting_define(opt, 0))
    file.write('#endif /* AP_DEBUG_ENABLE != 0 */\n')

    file.write('\n#endif /* AP_BUILD_CONFIG_H */\n')
