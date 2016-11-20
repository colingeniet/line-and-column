#include "main_window.h"
#include "color.h"

#include <iostream>

int main(int argc, char** argv)
{
    initscr();                  // ncruses initialisation
    cbreak();                   // no input buffering
    keypad(stdscr, TRUE);       // recieve functions key input
    noecho();                   // no input echo
    curs_set(0);                // cursor invisible
    // refresh of is required after initialization or windows won't display
    refresh();
    if(has_colors())
    {
        start_color();
        init_color_pairs();
    }

    Form square;
    square.add(0,0);
    square.add(0,1);
    square.add(1,0);
    square.add(1,1);

    Form bigsquare;
    bigsquare.add(-1, -1);
    bigsquare.add(-1, 0);
    bigsquare.add(-1, 1);
    bigsquare.add(0, -1);
    bigsquare.add(0, 0);
    bigsquare.add(0, 1);
    bigsquare.add(1, -1);
    bigsquare.add(1, 0);
    bigsquare.add(1, 1);

    mainWindow win(10, 10, 5);
    win.add_form_to_set(square);
    win.add_form_to_set(bigsquare);
    win.random_select_forms();

    win.print();
    while(win.input(getch()))
    {
        win.print();
    }

    endwin();

    return 0;
}
