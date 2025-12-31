#include "vga.h"

static volatile uint16_t *vga = (uint16_t*)0xB8000;

void vga_clear(uint8_t color) {
    for (int i = 0; i < 80 * 25; i++) {
        vga[i] = ((uint16_t)color << 8) | ' ';
    }
}

void vga_write_at(int x, int y, const char *s, uint8_t color) {
    int i = 0;
    while (s[i]) {
        vga[y * 80 + x + i] = ((uint16_t)color << 8) | s[i];
        i++;
    }
}

void vga_draw_chi(const char *s, uint8_t c) {
    for (int i = 0; i < 80 * 4; i++) {
        vga[i] = ((0x30) << 8) | ' ';
    }

    vga_write_at(0, 0, "=^-^=", 0x30);
    vga_write_at(8, 0, s, c);
}

