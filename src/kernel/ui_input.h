#pragma once
#include <stdint.h>

typedef struct {
    int x, y;
    int w;
    char buffer[128];
    int len;
    int focused;
} InputField;

static void draw_input(InputField *in);

#ifndef KEYBOARD_H
#define KEYBOARD_H

// Scancodes für Shift
#define KEY_LSHIFT_DOWN  0x2A
#define KEY_LSHIFT_UP    0xAA
#define KEY_RSHIFT_DOWN  0x36
#define KEY_RSHIFT_UP    0xB6

// Wird vom Treiber gesetzt
extern int keyboard_shift;

// Liest rohen Scancode → ASCII (unshifted)
char keyboard_read_raw();

// Wendet Shift auf ASCII an
char keyboard_apply_shift(char c);

// Öffentliche API: gibt fertiges ASCII zurück
char keyboard_read();

#endif

void ui_input_init();
void ui_input_add(int x, int y, int w);
void ui_input_draw_all();
void ui_input_focus_at(int mx, int my);
void ui_input_handle();                 // liest Tastatur und aktualisiert Inputs
const char *ui_input_get_buffer(int idx);
