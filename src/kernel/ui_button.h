#pragma once

typedef struct {
    int x, y;
    int w;
    const char *label;
    void (*on_click)();
} Button;

void ui_button_init();
void ui_button_add(int x, int y, const char *label, void (*on_click)());
void ui_button_draw(int x, int y, const char *label, unsigned char color);
void ui_button_check_click(int mx, int my);
