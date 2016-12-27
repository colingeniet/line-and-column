#include "includeGUI.h"     // main class
#include "color.h"          // init_color_pairs()
#include "global_log.h"     // error stream initialization
#include "option.h"

#include <ncurses.h>        // ncurses initialization

#include <cstdlib>          // srand(), exit()
#include <ctime>            // for srand()
#include <iostream>         // errors
#include <exception>        // terminate setting, terminate
#include <string>           // arguments parsing


#define GLOBAL_LOG_FILE "log.txt"


void ncurses_init();
void ncurses_init_mouse();
void ncurses_quit();
void ncurses_terminate();

void display_help();
void display_version();
void display_authors();


void ncurses_init()
{
    std::set_terminate(ncurses_terminate);

    initscr();                  // ncruses initialisation
    clear();
    cbreak();                   // no input buffering
    keypad(stdscr, true);       // recieve functions key input
    noecho();                   // no input echo
    curs_set(0);                // cursor invisible

    // refresh is required after initialization or windows won't display
    refresh();

    // use colors if available (compatibility, all that stuff ...)
    if(has_colors())
    {
        start_color();
        init_color_pairs();
    }
}

void ncurses_init_mouse()
{
    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION, NULL);
    mouseinterval(0);           // disable click resolution to avoid input delay
}

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



void display_help()
{
    std::cout << "Usage : line-and-column [OPTION] [FILE]\n"
              << "\n"
              << "Launch the game line-and-column and load FILE as a save file.\n"
              << "By default, default_board is loaded\n"
              << "\n"
              << "Options :\n"
              << "  -h, --help          show this help message and exit\n"
              << "  -v, --version       display program version and exit\n"
              << "  --authors           display authors names and exit\n"
              << "\n"
              << "  --enable-mouse/--disable-mouse      default : disable\n"
              << "                      enable/disable mouse control\n"
              << "                      please refer to README.txt for more details\n"
              << "\n"
              << "Please refer to README.txt for in game shortcuts"
              << std::endl;
    exit(EXIT_SUCCESS);
}

void display_version()
{
    std::cout << "line-and-column 2.1.0" << std::endl;
    exit(EXIT_SUCCESS);
}

void display_authors()
{
    std::cout << "Youcef Cherfaoui, Colin Geniet, Victor Huesca and Alexandre Ribeyre" << std::endl;
    exit(EXIT_SUCCESS);
}


int main(int argc, char** argv)
{
    // initialize log error stream
    mlog.setfile(GLOBAL_LOG_FILE);

    // create option set
    OptionSet options;
    options.add_option(Option("help", 'h'));
    options.add_option(Option("version", 'v'));
    options.add_option(Option("authors"));
    options.add_option(Option("enable-mouse"));
    options.add_option(Option("disable-mouse"));


    // Configuration values
    char *init_save_file = nullptr;
    bool mouse_enabled = false;


    // command line parameter parsing
    for(int i=1; i<argc; i++) {
        if(argv[i][0] == '-')       // options
        {
            std::string name, value;
            if(!options.find(argv[i], &name, &value))
            {
                mlog << "Invalid argument : " << argv[i] << std::endl;
                exit(EXIT_FAILURE);
            }
            else if(name == "help") display_help();
            else if(name == "version") display_version();
            else if(name == "authors") display_authors();
            else if(name == "enable-mouse") mouse_enabled = true;
            else if(name == "disable-mouse") mouse_enabled = false;
        }
        else                        // other parameters
        {
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
    if(mouse_enabled) ncurses_init_mouse();
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
