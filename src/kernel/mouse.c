#include <stdint.h>
#include "mouse.h"
#include "vga.h"
#include "ui_input.h"
#include "ui_button.h"

static inline uint8_t inb(uint16_t port) {
    uint8_t r;
    __asm__ volatile("inb %1,%0":"=a"(r):"Nd"(port));
    return r;
}

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile("outb %0,%1"::"a"(val),"Nd"(port));
}

static void mouse_wait(uint8_t t) {
    uint32_t to = 100000;
    if (!t) while (to--) if (inb(0x64) & 1) return;
    else while (to--) if (!(inb(0x64) & 2)) return;
}

static void mouse_write(uint8_t v) {
    mouse_wait(1);
    outb(0x64,0xD4);
    mouse_wait(1);
    outb(0x60,v);
}

uint8_t mouse_read() {
    mouse_wait(0);
    return inb(0x60);
}

static int mouse_x = 40;
static int mouse_y = 12;

static uint16_t *const vga_mem = (uint16_t*)0xB8000;

static uint16_t saved_cell = 0;
static int saved_x = 40;
static int saved_y = 12;

extern uint8_t mousecolor;

#define MOUSE_CHAR '+'

static void draw_mouse() {
    saved_x = mouse_x;
    saved_y = mouse_y;
    saved_cell = vga_mem[mouse_y*80 + mouse_x];

    uint8_t bg = (saved_cell >> 12) & 0x0F;
    uint8_t attr = (bg << 4) | (mousecolor & 0x0F);

    vga_mem[mouse_y*80 + mouse_x] = (attr << 8) | MOUSE_CHAR;
}


static void clear_mouse() {
    vga_mem[saved_y*80 + saved_x] = saved_cell;
}

void mouse_init() {
    mouse_wait(1);
    outb(0x64,0xA8);
    mouse_wait(1);
    outb(0x64,0x20);
    uint8_t s = mouse_read();
    s |= 2;
    mouse_wait(1);
    outb(0x64,0x60);
    mouse_wait(1);
    outb(0x60,s);
    mouse_write(0xF6);
    mouse_read();
    mouse_write(0xF4);
    mouse_read();
    draw_mouse();
}

void mouse_poll() {
    uint8_t st = inb(0x64);
    if (!(st & 1)) return;
    if (!(st & 0x20)) return;

    uint8_t p0 = mouse_read();
    uint8_t p1 = mouse_read();
    uint8_t p2 = mouse_read();

    int dx = (int8_t)p1;
    int dy = (int8_t)p2;
    uint8_t left = p0 & 1;

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

    draw_mouse();
}
