#ifndef UTIL_H
#define UTIL_H
#include <types.h>

/// @brief Get the value of a bit in a u8 bitfield.
/// @param array Bitfield array.
/// @param index Index of the bit to access.
/// @return True if bit is set, false otherwise.
static inline bool get_u8_bitfield_value(const u8* array, size_t index)
{
    size_t byte = index / 8;
    size_t bit = index % 8;

    u8 mask = (u8)(1u << bit);

    return (array[byte] & mask) != 0;
}

/// @brief Set the value of a bit in a u8 bitfield and get the previous value.
/// @param array Bitfield array.
/// @param index Index of the bit to write to.
/// @param value Value to write to the bit.
/// @return True if bit was previously set, false otherwise.
static inline bool set_u8_bitfield_value(u8* array, size_t index, bool value)
{
    size_t byte = index / 8;
    size_t bit = index % 8;

    u8* val = &array[byte];
    u8 mask = (u8)(1u << bit);

    bool previous = ((*val) & mask) != 0;

    if (value) {
        *val |= mask;
    } else {
        *val &= ~mask;
    }

    return previous;
}

#endif /* UTIL_H */