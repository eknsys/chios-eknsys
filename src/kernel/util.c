#include "util.h"

uint8_t to_uint8_t(const char *s) {
    uint8_t value = 0;

    // optionales "0x" überspringen
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
        s += 2;

    while (*s) {
        value <<= 4;

        if (*s >= '0' && *s <= '9')
            value |= (*s - '0');
        else if (*s >= 'A' && *s <= 'F')
            value |= (*s - 'A' + 10);
        else if (*s >= 'a' && *s <= 'f')
            value |= (*s - 'a' + 10);

        s++;
    }

    return value;
}
