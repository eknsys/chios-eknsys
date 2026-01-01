#include "p_about.h"
#include "vga.h"
#include "ui_input.h"
#include "ui_button.h"
#include "app.h"

extern char *sysver;
extern uint8_t fontcolor;

void startProgramAbout() {
    vga_clear(fontcolor);

    vga_draw_chi("...ChiOS... Das bin ja ich!", 0x30);

    vga_write_at(2, 6, "ChiOS System App - Info", 0x1B);

    vga_write_at(4, 10, "Systemversion: ", fontcolor);
    vga_write_at(20, 10, sysver, fontcolor);

    ui_button_init();
    ui_button_draw(64, 22, "<- main menu", 0x1E);
    ui_button_add(64, 22, "<- main menu", mainapp);
}