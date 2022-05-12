/*
Copyright (C) 2015-2019 The University of Notre Dame
This software is distributed under the GNU General Public License.
See the file LICENSE for details.
*/

#include "console.h"
#include "page.h"
#include "process.h"
#include "keyboard.h"
#include "mouse.h"
#include "interrupt.h"
#include "clock.h"
#include "ata.h"
#include "device.h"
#include "cdromfs.h"
#include "string.h"
#include "graphics.h"
#include "kernel/ascii.h"
#include "kernel/syscall.h"
#include "rtc.h"
#include "kernelcore.h"
#include "kmalloc.h"
#include "memorylayout.h"
#include "kshell.h"
#include "cdromfs.h"
#include "diskfs.h"
#include "serial.h"
void graphics_string(struct graphics* g, int x, int y, const char* str, int length);
void sleep(int x) {

    for (int i = 0; i < x; i++) {
        for (int k = 0; k < x; k++) {


        }
    }

}
static struct graphics_color white = { 255, 255, 255, 0 };
static struct graphics_color black = { 0, 0, 0, 0 };
int kernel_main()
{
    int player_one = 0;
    int player_two = 0;

    int paddle_one_y = 370;
    int paddle_two_y = 370;

    int paddle_one_x = 10;
    int paddle_two_x = 1010;

    int ballx = 500;
    int bally = 420;
    int line_top = 170;
    int line_bottom = 670;
    int dirx = +1;
    int diry = -1;
    int f = 1;
    struct console* console = console_create_root();


    struct graphics* g = graphics_create_root();

    graphics_create(g);

    graphics_line(g, 0, line_top, 1023, 0);
    graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
    graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);
    graphics_line(g, 0, line_bottom, 1023, 0);
    keyboard_init();
    console_addref(g);
    page_init();
    kmalloc_init((char*)KMALLOC_START, KMALLOC_LENGTH);
    interrupt_init();
    mouse_init();
    keyboard_init();
    rtc_init();
    clock_init();
    process_init();
    ata_init();
    cdrom_init();
    diskfs_init();

    graphics_char(g, ballx, bally, 'O');

    while (f) {

        switch (console_getchar(console)) {
        case 'w':
            if (paddle_one_y != 170) {
                graphics_fgcolor(g, black);
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
                graphics_fgcolor(g, white);
                paddle_one_y -= 20;
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);

            }
            break;
        case 's':
            if (paddle_one_y + 100 != 670) {
                graphics_fgcolor(g, black);
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
                graphics_fgcolor(g, white);
                paddle_one_y += 20;
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);

            }
            break;
        case 'o':
            if (paddle_two_y != 170) {
                graphics_fgcolor(g, black);
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);
                graphics_fgcolor(g, white);
                paddle_two_y -= 20;
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);

            }
            break;
        case 'l':
            if (paddle_two_y + 100 != 670) {
                graphics_fgcolor(g, black);
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);
                graphics_fgcolor(g, white);
                paddle_two_y += 20;
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);

            }
            break;
        }

        if (ballx >= 0 && ballx <= 1023 && bally >= line_top && bally <= line_bottom) {
            graphics_char(g, ballx, bally, ' ');
            ballx += dirx;
            bally += diry;
            graphics_char(g, ballx, bally, 'O');

            if (bally + 8 == line_bottom) {
                diry *= -1;
            }
            else if (bally - 8 == line_top) {
                diry *= -1;
            }
            else if (ballx == 1023) {
                graphics_char(g, ballx, bally, ' ');
                ballx = 500;
                bally = 420;
                graphics_fgcolor(g, black);
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);
                dirx *= -1;
                diry *= -1;
                paddle_one_y = 370;
                paddle_two_y = 370;
                paddle_one_x = 10;
                paddle_two_x = 1010;
                graphics_fgcolor(g, white);
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);
                player_one += 1;
            }
            else if (ballx == 0) {
                graphics_char(g, ballx, bally, ' ');
                graphics_fgcolor(g, black);
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);
                ballx = 500;
                bally = 420;
                dirx *= -1;
                diry *= -1;
                paddle_one_y = 370;
                paddle_two_y = 370;
                paddle_one_x = 10;
                paddle_two_x = 1010;
                graphics_fgcolor(g, white);
                graphics_rect(g, paddle_one_x, paddle_one_y, 3, 100);
                graphics_rect(g, paddle_two_x, paddle_two_y, 3, 100);

                player_two += 1;
            }
            else if (ballx + 8 == paddle_two_x && bally >= paddle_two_y && bally <= paddle_two_y + 100) {
                dirx *= -1;
            }

            else if (ballx - 4 == paddle_one_x && bally >= paddle_one_y && bally <= paddle_one_y + 100) {
                dirx *= -1;
            }

        }
        int countc = 40;
        char arro[10] = { 'P','L','A','Y','E','R',' ','O','N','E' };
        for (int i = 0; i < 10; i++) {

            graphics_char(g, countc, 200, arro[i]);

            countc += 8;
        }
        graphics_char(g, 128, 200, '-');
        graphics_char(g, 142, 200, '0');
        if (player_one == 1) {
            graphics_char(g, 142, 200, '1');

        }
        else if (player_one == 2) {
            graphics_fgcolor(g, white);
            graphics_char(g, 142, 200, '2');
        }
        else if (player_one == 3) {
            graphics_fgcolor(g, white);
            graphics_char(g, 142, 200, '3');
        }
        else if (player_one == 4) {
            graphics_fgcolor(g, white);
            graphics_char(g, 142, 200, '4');
        }
        else if (player_one == 5) {
            graphics_fgcolor(g, white);
            graphics_char(g, 142, 200, '5');
            f = 0;
        }

        int countt = 800;
        char arrt[10] = { 'P','L','A','Y','E','R',' ','T','W','O' };
        for (int i = 0; i < 10; i++) {

            graphics_char(g, countt, 200, arrt[i]);

            countt += 8;
        }
        graphics_char(g, 890, 200, '-');
        graphics_char(g, 906, 200, '0');

        if (player_two == 1) {
            graphics_char(g, 906, 200, '1');

        }
        else if (player_two == 2) {
            graphics_fgcolor(g, white);
            graphics_char(g, 906, 200, '2');
        }
        else if (player_two == 3) {
            graphics_fgcolor(g, white);
            graphics_char(g, 906, 200, '3');
        }
        else if (player_two == 4) {
            graphics_fgcolor(g, white);
            graphics_char(g, 906, 200, '4');
        }
        else if (player_two == 5) {
            graphics_fgcolor(g, white);
            graphics_char(g, 906, 200, '5');
            f = 0;

        }



        sleep(1300);
    }
    graphics_fgcolor(g, black);
    graphics_rect(g, 0, 170, 1023, 510);
    graphics_fgcolor(g, white);
    if (player_one == 1) {
        int count1 = 450;
        char arr[14] = { 'P','L','A','Y','E','R',' ','O','N','E',' ','W','I','N' };
        for (int r = 0; r < 14; r++) {

            graphics_char(g, count1, 400, arr[r]);
            count1 += 8;
        }
    }
    else if (player_two == 1) {
        int count2 = 450;
        char arr2[14] = { 'P','L','A','Y','E','R',' ','T','W','O',' ','W','I','N' };
        for (int t = 0; t < 14; t++) {

            graphics_char(g, count2, 400, arr2[t]);
            count2 += 8;
        }
    }

    return 0;
}
