#include <stdint.h>
#include "mouse.h"
#include "vga.h"
#include "ui_input.h"
#include "ui_button.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static void mouse_wait(uint8_t type) {
    uint32_t timeout = 100000;
    if (type == 0) {
        while (timeout--) {
            if (inb(0x64) & 1) return;
        }
    } else {
        while (timeout--) {
            if (!(inb(0x64) & 2)) return;
        }
    }
}

static void mouse_write(uint8_t val) {
    mouse_wait(1);
    outb(0x64, 0xD4);
    mouse_wait(1);
    outb(0x60, val);
}

uint8_t mouse_read() {
    mouse_wait(0);
    return inb(0x60);
}

/* Maus-Zustand + Cursor-Darstellung */

static int mouse_x = 40;
static int mouse_y = 12;

static uint16_t *const vga_mem = (uint16_t*)0xB8000;
static uint16_t saved_cell = 0;
static int saved_x = 40;
static int saved_y = 12;

#define MOUSE_CHAR '+'
#define MOUSE_COLOR 0x16

static void draw_mouse(uint8_t color) {
    saved_x = mouse_x;
    saved_y = mouse_y;
    saved_cell = vga_mem[mouse_y * 80 + mouse_x];
    vga_mem[mouse_y * 80 + mouse_x] = ((uint16_t)color << 8) | MOUSE_CHAR;
}

static void clear_mouse() {
    vga_mem[saved_y * 80 + saved_x] = saved_cell;
}

void mouse_init() {
    mouse_wait(1);
    outb(0x64, 0xA8);

    mouse_wait(1);
    outb(0x64, 0x20);
    uint8_t status = mouse_read();
    status |= 2;

    mouse_wait(1);
    outb(0x64, 0x60);
    mouse_wait(1);
    outb(0x60, status);

    mouse_write(0xF6);
    mouse_read();

    mouse_write(0xF4);
    mouse_read();

    draw_mouse(MOUSE_COLOR);
}

void mouse_poll() {
    uint8_t status = inb(0x64);
    if (!(status & 1)) return;
    if (!(status & 0x20)) return;

    uint8_t packet[3];
    packet[0] = mouse_read();
    packet[1] = mouse_read();
    packet[2] = mouse_read();

    int dx = (int8_t)packet[1];
    int dy = (int8_t)packet[2];
    uint8_t left = packet[0] & 1;

    clear_mouse();

    mouse_x += dx / 4;
    mouse_y -= dy / 4;

    if (mouse_x < 0) mouse_x = 0;
    if (mouse_x > 79) mouse_x = 79;
    if (mouse_y < 0) mouse_y = 0;
    if (mouse_y > 24) mouse_y = 24;

    if (left) {
        ui_input_focus_at(mouse_x, mouse_y);
        ui_button_check_click(mouse_x, mouse_y);
    }

    draw_mouse(MOUSE_COLOR);
}
