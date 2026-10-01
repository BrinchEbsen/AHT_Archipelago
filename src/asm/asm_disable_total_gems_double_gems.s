# Rewritten bit of XGemItem::UpDateGem.
# Didn't want to replace the whole function, but didn't have enough space to
# rewrite the assembly in place, so I made it divert into this bit of code
# before returning where it was.

.global disable_total_gems_double_gems
.type disable_total_gems_double_gems, @function
disable_total_gems_double_gems:
    bne- _dg_flag_not_set
    li 11, 0

_dg_flag_not_set:
    mr 9, 8         # Added line, keep the non-multiplied value.
    cmpwi 11, 0
    beq- _dg_skip_multiplication
    add 9, 8, 8     # Store multiplied value in r9 instead of r8. r8 keeps original.

_dg_skip_multiplication:
    # Add gems value (which could be double gems)
    lwz 0, 0x8 (10)
    add 0, 0, 9
    stw 0, 0x8 (10)

    # Add total gems value (which isn't multiplied)
    lwz 0, 0xC (10)
    add 0, 0, 8
    stw 0, 0xC (10)

    # Set whatever flag it was setting
    lwz 11, 0x48 (1)
    ori 11, 11, 0x1
    stw 11, 0x48 (1)
    blr



    # Original instructions:
    # lwz 0, 0x8 (10)
    # lwz 9, 0xC (10)
    # lwz 11, 0x48 (1)
    # add 0, 0, 8
    # add 9, 9, 8
    # stw 0, 0x8 (10)
    # ori 11, 11, 0x1
    # stw 9, 0xC (10)
    # stw 11, 0x48 (1)
