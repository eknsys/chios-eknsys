#include "ui_input.h"
#include "vga.h"
#include "keyboard.h"

#define MAX_INPUTS 9999

static InputField inputs[MAX_INPUTS];
static int input_count = 0;

static void draw_input(InputField *in) {
    vga_write_at(in->x, in->y, "[", 0x1F);

    for (int i = 0; i < in->w; i++) {
        char c = (i < in->len) ? in->buffer[i] : ' ';
        char s[2] = { c, 0 };
        vga_write_at(in->x + 1 + i, in->y, s, 0x1F);
    }

    vga_write_at(in->x + 1 + in->w, in->y, "]", 0x1F);
}

void ui_input_init() {
    input_count = 0;
}

void ui_input_add(int x, int y, int w) {
    if (input_count >= MAX_INPUTS) return;

    InputField *in = &inputs[input_count++];
    in->x = x;
    in->y = y;
    in->w = w;
    in->len = 0;
    in->focused = 0;
    in->buffer[0] = '\0';
}

void ui_input_draw_all() {
    for (int i = 0; i < input_count; i++) {
        draw_input(&inputs[i]);
    }
}

void ui_input_focus_at(int mx, int my) {
    for (int i = 0; i < input_count; i++) {
        InputField *in = &inputs[i];
        if (my == in->y && mx >= in->x && mx <= in->x + in->w + 1) {
            for (int j = 0; j < input_count; j++) inputs[j].focused = 0;
            in->focused = 1;
        }
    }
}

static void handle_char(InputField *in, char c) {
    if (c == '\b') {
        if (in->len > 0) {
            in->len--;
            in->buffer[in->len] = '\0';
        }
    } else if (c >= 32 && c <= 126) {
        if (in->len < in->w && in->len < 127) {
            in->buffer[in->len++] = c;
            in->buffer[in->len] = '\0';
        }
    }
    draw_input(in);
}

void ui_input_handle() {
    char c = keyboard_read();
    if (!c) return;

    for (int i = 0; i < input_count; i++) {
        if (inputs[i].focused) {
            handle_char(&inputs[i], c);
        }
    }
}

const char *ui_input_get_buffer(int idx) {
    if (idx < 0 || idx >= input_count) return 0;
    return inputs[idx].buffer;
}
