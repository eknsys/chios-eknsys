#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

// PS/2 Shift scancodes
#define KEY_LSHIFT_DOWN  0x2A
#define KEY_LSHIFT_UP    0xAA
#define KEY_RSHIFT_DOWN  0x36
#define KEY_RSHIFT_UP    0xB6

// Wird vom Keyboard-Treiber gesetzt
extern int keyboard_shift;

// Liest rohen Scancode → ASCII (unshifted)
char keyboard_read_raw();

// Wendet Shift auf ASCII an
char keyboard_apply_shift(char c);

// Öffentliche API: gibt fertiges ASCII zurück
char keyboard_read();

#endif
