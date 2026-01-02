#include "app.h"
#include "vga.h"
#include "p_about.h"
#include "p_settings.h"
#include "p_chisay.h"
#include "ui_button.h"
#include "ui_input.h"

extern char *sysver;
extern uint8_t fontcolor;


void mainapp(char *chistr) {


    vga_clear(fontcolor);

    vga_draw_chi("Miau! Suche dir mal ein Programm aus!", 0x30);

    vga_write_at(2, 6, "ChiOS - mainapp - Main Menu", 0x1B);

    vga_write_at(2, 9, "System Apps:", fontcolor);

    ui_button_init();
    ui_input_init();

    ui_button_draw(4, 11, "Info", 0x1E);
    ui_button_add(4, 11, "Info", startProgramAbout);

    ui_button_draw(11, 11, "Einstellungen", 0x1E);
    ui_button_add(11, 11, "Einstellungen", startProgramSettings);

    vga_write_at(4, 14, "Chi Apps:", fontcolor);

    ui_button_draw(4, 16, "Chi Say", 0x1E);
    ui_button_add(4, 16, "Chi Say", startProgramChiSay);


}
