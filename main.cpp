#include "main_window.h"    // main class
#include "color.h"          // init_color_pairs()

#include <ncurses.h>        // ncurses initialization

#include <cstdlib>          // srand()
#include <ctime>            // for srand()
#include <exception>        // terminate setting



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
    abort();
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

int main(int argc, char** argv)
{
    ncurses_init();
    srand(time(NULL));

    mainWindow win;

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

    ncurses_quit();

    return 0;
}
