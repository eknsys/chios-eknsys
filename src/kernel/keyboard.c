#include "keyboard.h"
#include "port_io.h"

int keyboard_shift = 0;

// US/DE Keymap (ASCII only)
static const char keymap[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','\'','+','\b',
    '\t','q','w','e','r','t','z','u','i','o','p','[',']','\n', 0,
    'a','s','d','f','g','h','j','k','l',';','\'','`', 0,
    '\\','y','x','c','v','b','n','m',',','.','/', 0,
    '*', 0,' ', 0,
};

char keyboard_read_raw() {
    uint8_t status = inb(0x64);

    // keine Daten?
    if (!(status & 1))
        return 0;

    // Mausdaten? → ignorieren
    if (status & (1 << 5))
        return 0;

    uint8_t sc = inb(0x60);

    if (sc > 127)
        return 0;

    return keymap[sc];
}

char keyboard_apply_shift(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 32;

    switch (c) {
        case '1': return '!';
        case '2': return '"';
        case '3': return '#';
        case '4': return '$';
        case '5': return '%';
        case '6': return '&';
        case '7': return '/';
        case '8': return '(';
        case '9': return ')';
        case '0': return '=';
        case '\'': return '?';
        case '+': return '*';
        case ',': return ';';
        case '.': return ':';
        case '-': return '_';
    }

    return c;
}

char keyboard_read() {
    uint8_t status = inb(0x64);

    if (!(status & 1))
        return 0;

    // Mausdaten ignorieren
    if (status & (1 << 5))
        return 0;

    uint8_t sc = inb(0x60);

    // Shift down
    if (sc == KEY_LSHIFT_DOWN || sc == KEY_RSHIFT_DOWN) {
        keyboard_shift = 1;
        return 0;
    }

    // Shift up
    if (sc == KEY_LSHIFT_UP || sc == KEY_RSHIFT_UP) {
        keyboard_shift = 0;
        return 0;
    }

    if (sc > 127)
        return 0;

    char c = keymap[sc];
    if (!c)
        return 0;

    if (keyboard_shift)
        c = keyboard_apply_shift(c);

    return c;
}
