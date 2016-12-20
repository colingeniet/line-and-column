#include "main_window.h"    // main class
#include "color.h"          // init_color_pairs()
#include "global_log.h"     // error stream initialization

#include <ncurses.h>        // ncurses initialization

#include <cstdlib>          // srand(), exit()
#include <ctime>            // for srand()
#include <iostream>         // errors
#include <exception>        // terminate setting, terminate


#define GLOBAL_LOG_FILE "log.txt"


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
    mlog << "terminate called : exiting ncurses and aborting" << std::endl;
    mlog.close();
    // may as well try to destroy other objects and close streams
    exit(EXIT_FAILURE);
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

    // use colors if available (compatibility, all that stuff ...)
    if(has_colors())
    {
        start_color();
        init_color_pairs();
    }

    std::set_terminate(ncurses_terminate);
}

int main(int argc, char** argv)
{
    // initialize log error stream
    mlog.setfile(GLOBAL_LOG_FILE);


    // initial file to load
    char *init_save_file = nullptr;

    // command line parameter parsing
    for(int i=1; i<argc; i++) {
        if(argv[i][0] == '-') {             // options
            if(argv[i][1] == '-') {         // long options
                mlog << "Unknown option : " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            } else {                        // short options
                mlog << "Unknown option : " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
        } else {                            // other parameters
            if(init_save_file) {
                // init_save_file was already set
                mlog << "Only one save file may be passed as parameter :\n"
                     << '\'' << argv[i] << "\' and \'"
                     << init_save_file << "\' are in conflict" << std::endl;
                exit(EXIT_FAILURE);
            } else {
                init_save_file = argv[i];
            }
        }
    }

    // initialisation
    ncurses_init();
    srand(time(NULL));


    // create main object, load initial state
    mainWindow win;
    if(init_save_file) {
        if(!win.load(init_save_file, menuWindow::MESSAGE_ERROR)) {
            mlog << "configuration file  " << init_save_file
                 << " is invalid" << std::endl;
            std::terminate();
        }
    } else {
        // no file was given as parameter, load default one
        if(!win.load(DEFAULT_BOARD, menuWindow::MESSAGE_ERROR)) {
            mlog << "Default configuration file is invalid" << std::endl;
            std::terminate();
        }
    }
    win.load_scores();


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

    // autosave
    win.save(AUTOSAVE_FILE, menuWindow::MESSAGE_NONE);
    win.save_scores();

    // exit
    ncurses_quit();

    return 0;
}
