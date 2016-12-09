#include "main_window.h"

#include "global_log.h" // errors

#include <ncurses.h>    // doupdate() - some definition

#include <fstream>      // autosave on exit
#include <exception>    // terminate



mainWindow::mainWindow() :
    game(new mainGame),
    current_window(WINDOW_GAME),
    game_window(game),
    menu_window(game)
{
}

mainWindow::mainWindow(const mainGame &newgame) :
    game(new mainGame(newgame)),
    current_window(WINDOW_GAME),
    game_window(game),
    menu_window(game)
{
    initialize_game();
}

mainWindow::~mainWindow()
{
    if(game) delete game;
}

void mainWindow::setgame(const mainGame &newgame)
{
    // all Window subclass share the reference to the same mainGame object
    // but some require to be warned if it is changed
    // specifically, gameWindow needs to rebuild WINDOWS if dimention changed
    *game = newgame;            // here game is changed for all classes
    game_window.setgame(game);  // tell other classes about it
    menu_window.setgame(game);
}


bool mainWindow::input(int ch)
{
    // transfer input to the current active window and preform required
    // action depending on return code
    switch(current_window)
    {
    case WINDOW_GAME:
        switch(game_window.input(ch))
        {
        case gameWindow::RETURN_NONE:
            break;
        case gameWindow::RETURN_QUIT:
            current_window = WINDOW_MENU;
            break;
        case gameWindow::RETURN_NO_MOVE:
            // game over : save score and reinitialize game
            menu_window.add_score(game->getscore());
            game->restart();
            menu_window.print_score();
            break;
        default:
            mlog << "Unknown return code" << std::endl;
            std::terminate();
            break;
        }
        break;
    case WINDOW_MENU:
        switch(menu_window.input(ch))
        {
        case menuWindow::RETURN_NONE:
            break;
        case menuWindow::RETURN_RESUME:
            current_window = WINDOW_GAME;
            break;
        case menuWindow::RETURN_UPDATE_GAME:
            // this code means that the game board was modified in a way that
            // require other windows to be warned (cf mainWindow::setgame())
            setgame(*game);
            initialize_game();
            current_window = WINDOW_GAME;
            break;
        case menuWindow::RETURN_QUIT:
            return false;
            break;
        default:
            mlog << "Unknown return code" << std::endl;
            std::terminate();
            break;
        }
        break;
    default:
        mlog << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }
    return true;
}

void mainWindow::print()
{
    wclear(stdscr);
    wnoutrefresh(stdscr);
    // just call print() for current active window
    switch(current_window)
    {
    case WINDOW_GAME:
        game_window.print();
        break;
    case WINDOW_MENU:
        menu_window.print();
        break;
    default:
        mlog << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }

    // and refresh screen
    doupdate();
}


bool mainWindow::save(const char *file, menuWindow::messageLevel verbose) const
{
    return menu_window.save(file, verbose);
}

bool mainWindow::load(const char *file, menuWindow::messageLevel verbose)
{
    bool success = menu_window.load(file, verbose);
    if(success) {
        setgame(*game);
        initialize_game();
    }
    return success;
}

bool mainWindow::save_scores(const char *file) const
{
    return menu_window.save_score(file);
}

bool mainWindow::load_scores(const char *file)
{
    return menu_window.load_score(file);
}


void mainWindow::initialize_game()
{
    // a loaded game may not have forms selected
    game->random_select_forms(false);
}
