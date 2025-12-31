#include "p_settings.h"
#include "vga.h"
#include "ui_input.h"
#include "ui_button.h"
#include "app.h"
#include "util.h"

void startProgramSettings() {
    vga_clear(0x1F);
    vga_draw_chi("Du willst etwas aendern? Vielleicht die...  ...Maus...  ...MAUS! WO? WO? MEIN MITTAGESSEN!", 0x30);

    ui_button_init();
    ui_button_draw(64, 22, "<- main menu", 0x1E);
    ui_button_add(64, 22, "<- main menu", mainapp);
}