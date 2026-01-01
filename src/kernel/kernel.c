#include <stdint.h>
#include "vga.h"
#include "mouse.h"
#include "keyboard.h"
#include "ui_input.h"
#include "ui_button.h"
#include "util.h"
#include "app.h"


uint8_t mousecolor = 0x6C;
uint8_t fontcolor = 0x1F;


char *sysver = "1.0dev1.0";

void kernel_main(uint32_t magic, void *mb_info) {
    (void)magic;
    (void)mb_info;

    vga_clear(0x1F);
    vga_write_at(1, 1, "Loading mainapp...", fontcolor);

    ui_input_init();
    ui_button_init();

    mainapp();

    mouse_init();   // initialisiert Maus und zeichnet Cursor

    while (1) {
        mouse_poll();          // kümmert sich um Mausbewegung & Klicks
        ui_input_handle();     // liest Tastatur und aktualisiert Input-Felder
    }
}
