#include "p_settings.h"
#include "vga.h"
#include "ui_input.h"
#include "ui_button.h"
#include "app.h"
#include "util.h"

extern uint8_t mousecolor;
extern uint8_t fontcolor;

void startProgramSettings();

void psetSetMouse() {
    mousecolor = to_uint8_t(ui_input_get_buffer(0));
    mainapp();
}

void psetSetTH() {
    fontcolor = to_uint8_t(ui_input_get_buffer(1));
    vga_clear(fontcolor);
    mainapp();
}

void startProgramSettings() {
    vga_clear(fontcolor);
    vga_draw_chi("Du willst etwas aendern? Vielleicht die...  ...Maus...  ...MAUS! WO? WO? MEIN MITTAGESSEN!", 0x30);

    ui_button_init();
    ui_input_init();


    vga_write_at(2, 6, "ChiOS System App - Einstellungen", 0x13);

    vga_write_at(2, 8, "Farbe des Mauszeigers: hex (z.B. 0x0f, 0x03, ...)", fontcolor);
    vga_write_at(2, 9, "Farbe:", fontcolor);

    ui_input_add(10, 9, 10);
    
    ui_button_draw(2, 11, "Mauszeiger Ok", 0x1E);
    ui_button_add(2, 11, "Mauszeiger Ok", psetSetMouse);


    vga_write_at(2, 14, "Text + Hintergrundfarbe: hex 0xHV, (z.b. 0x1f, 0x0f)", fontcolor);
    vga_write_at(2, 15, "V: Textfarbe, H: Hintergrundfarbe", fontcolor);
    vga_write_at(2, 16, "Farbe:", fontcolor);

    ui_input_add(10, 16, 10);

    ui_button_draw(2, 18, "T/H Farben Ok", 0x1E);
    ui_button_add(2, 18, "T/H Farben Ok", psetSetTH);

    ui_input_draw_all();

    ui_button_draw(64, 22, "<- main menu", 0x1E);
    ui_button_add(64, 22, "<- main menu", mainapp);
}