#include "ui_button.h"
#include "vga.h"

#define MAX_BUTTONS 10

static Button buttons[MAX_BUTTONS];
static int button_count = 0;

void ui_button_init() {
    button_count = 0;
}

void ui_button_draw(int x, int y, const char *label, unsigned char color) {
    int len = 0;
    while (label[len]) len++;

    vga_write_at(x, y, "[", color);
    for (int i = 0; i < len; i++) {
        char s[2] = { label[i], 0 };
        vga_write_at(x + 1 + i, y, s, color);
    }
    vga_write_at(x + 1 + len, y, "]", color);
}

void ui_button_add(int x, int y, const char *label, void (*on_click)()) {
    if (button_count >= MAX_BUTTONS) return;

    int len = 0;
    while (label[len]) len++;

    buttons[button_count].x = x;
    buttons[button_count].y = y;
    buttons[button_count].w = len + 2;
    buttons[button_count].label = label;
    buttons[button_count].on_click = on_click;
    button_count++;
}

void ui_button_check_click(int mx, int my) {
    for (int i = 0; i < button_count; i++) {
        Button *b = &buttons[i];
        if (my == b->y && mx >= b->x && mx < b->x + b->w) {
            if (b->on_click) {
                b->on_click();
            }
        }
    }
}
