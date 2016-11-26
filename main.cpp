#include "main_window.h"
#include "main_game.h"
#include "color.h"

#include <ncurses.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <exception>



void ncurses_quit()
{
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
}

int main(int argc, char** argv)
{
    std::ifstream input;
    if(argc == 2)
        input.open(argv[1]);
    else
        input.open("default_board");

    mainGame game;

    input >> game;
    input.close();

    game.random_select_forms();

    ncurses_init();
    std::set_terminate(ncurses_terminate);

    mainWindow win(game);

    srand(time(NULL));


    win.print();
    while(win.input(getch()))
    {
        win.print();
    }

    ncurses_quit();

    std::ofstream output("save");
    output << game;
    output.close();

    return 0;
}
