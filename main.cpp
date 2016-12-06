#include "main_window.h"    // main class
#include "color.h"          // init_color_pairs()

#include <ncurses.h>        // ncurses initialization

#include <cstdlib>          // srand(), exit()
#include <ctime>            // for srand()
#include <iostream>         // errors
#include <exception>        // terminate setting, terminate



void ncurses_quit()
{
    clear();
    refresh();
    endwin();
}

// terminate handler : ncurses must always quit before exiting
void ncurses_terminate()
{
    ncurses_quit();
    std::cerr << "terminate called : exiting ncurses and aborting" << std::endl;
    exit(EXIT_FAILURE);     // destroy objects, flush streams ...
}


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

    std::set_terminate(ncurses_terminate);
}

int main(int, char**)
{
    ncurses_init();
    srand(time(NULL));

    mainWindow win;
    if(!win.load(DEFAULT_BOARD, menuWindow::MESSAGE_ERROR)) {
        std::cerr << "Default configuration file is invalid" << std::endl;
        std::terminate();
    }

    bool quit = false;
    // main loop
    while(!quit)
    {
        win.print();

        // input
        int ch = getch();
        if(!win.input(ch))
        {
            quit = true;
        }
    }

    win.save(AUTOSAVE_FILE, menuWindow::MESSAGE_NONE);

    ncurses_quit();

    return 0;
}
