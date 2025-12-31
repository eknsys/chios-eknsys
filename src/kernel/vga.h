#pragma once
#include <stdint.h>

void vga_clear(uint8_t color);
void vga_write_at(int x, int y, const char *s, uint8_t color);
void vga_draw_chi(const char *s, uint8_t c);
