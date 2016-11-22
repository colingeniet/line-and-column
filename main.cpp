#include "main_window.h"
#include "color.h"

#include <ncurses.h>

#include <cstdlib>
#include <ctime>


void ncurses_init()
{
    initscr();                  // ncruses initialisation
    clear();
    cbreak();                   // no input buffering
    keypad(stdscr, true);       // recieve functions key input
    noecho();                   // no input echo
    curs_set(0);                // cursor invisible
    // enable mouse
    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION, NULL);
    mouseinterval(0);           // disable click resolution to avoid input delay
    // refresh is required after initialization or windows won't display
    refresh();
    if(has_colors())
    {
        start_color();
        init_color_pairs();
    }
}

int main(int argc, char** argv)
{
    ncurses_init();

    srand(time(NULL));

    Form SQ1, SQ2, V2, V3, V4, V5, H2, H3, H4, H5;
    SQ1.add(0,0);
    SQ2.add(0,0); SQ2.add(1,0); SQ2.add(0,1); SQ2.add(1,1);

    V2.add(0,0); V2.add(0,-1);
    V3.add(0,-1); V3.add(0,0); V3.add(0,1);
    V4.add(0,-2); V4.add(0,-1); V4.add(0,0); V4.add(0,1);
    V5.add(0,-2); V5.add(0,-1); V5.add(0,0); V5.add(0,1); V5.add(0,2);

    H2.add(0,0); H2.add(-1,0);
    H3.add(-1,0); H3.add(0,0); H3.add(1,0);
    H4.add(-2,0); H4.add(-1,0); H4.add(0,0); H4.add(1,0);
    H5.add(-2,0); H5.add(-1,0); H5.add(0,0); H5.add(1,0); H5.add(2,0);


    mainWindow win(10, 10, 5);
    win.add_form_to_set(SQ1, COLOR_WHITE);
    win.add_form_to_set(SQ2, COLOR_RED);
    win.add_form_to_set(V2, COLOR_BLUE);
    win.add_form_to_set(H2, COLOR_BLUE);
    win.add_form_to_set(V3, COLOR_GREEN);
    win.add_form_to_set(H3, COLOR_GREEN);
    win.add_form_to_set(V4, COLOR_YELLOW);
    win.add_form_to_set(H4, COLOR_YELLOW);
    win.add_form_to_set(V5, COLOR_RED);
    win.add_form_to_set(H5, COLOR_RED);
    win.random_select_forms();


    bool quit = false;
    // main loop
    while(!quit)
    {
        win.print();

        // input
        int ch = getch();
        switch(ch)
        {
        case 'q':
            quit = true;
            break;
        default:
            if(!win.input(ch))
            {
                quit = true;
            }
            break;
        }
    }

    endwin();

    return 0;
}
