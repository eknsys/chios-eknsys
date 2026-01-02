#include "p_chisay.h"
#include "vga.h"
#include "ui_input.h"
#include "ui_button.h"
#include "app.h"
#include "util.h"

extern char *sysver;
extern uint8_t fontcolor;


void run() {
    const char *icmd = ui_input_get_buffer(0);
    vga_draw_chi("...", 0x30);

    // Eingabe anzeigen
    vga_clear_at(11, 11, 0x0a);
    vga_write_at(0, 11, ">", 0x0a);
    vga_write_at(1, 11, icmd, 0x0a);

    if (str_contains(icmd, ":")) {

        char cmd[64];
        char subcmd[64];

        str_split_at(icmd, ':', cmd, subcmd);

        if (strcmp(cmd, "chios") == 0) {
        
            if (strcmp(subcmd, "help") == 0) {
                   vga_write_at(0, 12, "ChiOS help", 0x0a);
               vga_write_at(0, 13, ">> help", 0x0a);
           } else {
               char errormsg[128];
               str_concat3(errormsg, "ERROR: subcommand ", subcmd, " not found!");
               vga_draw_chi(errormsg, 0x34);
           }

        } else if (strcmp(cmd, "run") == 0) {

        } else {
            char errormsg[128];
            str_concat3(errormsg, "ERROR: command ", cmd, " not found!");
            vga_draw_chi(errormsg, 0x34);
        }
    } else {
        vga_draw_chi("ERROR: invalid syntax.", 0x34);
    }

}


void startProgramChiSay() {
    vga_clear(fontcolor);
    vga_draw_chi("...", 0x30);

    ui_input_init();
    ui_button_init();

    vga_write_at(2, 6, ">", fontcolor);
    ui_input_add(7, 6, 60);
    ui_button_draw(74, 6, "Ok", 0x1E);
    ui_button_add(74, 6, "Ok", run);

    vga_write_at(0, 8, "Ausgabe:", fontcolor);


    ui_input_draw_all();

    ui_button_draw(64, 22, "<- main menu", 0x1E);
    ui_button_add(64, 22, "<- main menu", mainapp);
}