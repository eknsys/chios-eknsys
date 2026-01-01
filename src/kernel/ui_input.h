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
void ui_input_init();
void ui_input_add(int x, int y, int w);
void ui_input_draw_all();
void ui_input_focus_at(int mx, int my);
void ui_input_handle();                 // liest Tastatur und aktualisiert Inputs
const char *ui_input_get_buffer(int idx);
