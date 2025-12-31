#include "app.h"
#include "vga.h"
#include "p_about.h"
#include "ui_button.h"
#include "ui_input.h"

extern char *sysver;


void mainapp() {
    vga_clear(0x1F);

    vga_draw_chi("Miau! Suche dir mal ein Programm aus!", 0x30);

    vga_write_at(2, 6, "ChiOS - mainapp - Main Menu", 0x1B);

    vga_write_at(2, 9, "System Apps:", 0x1F);

    ui_button_init();
    ui_input_init();

    ui_button_draw(4, 11, "Info", 0x1E);
    ui_button_add(4, 11, "Info", startProgramAbout);


}
