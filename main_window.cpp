#include "main_window.h"

#include "global_log.h" // errors

#include <ncurses.h>    // doupdate() - some definition

#include <fstream>      // autosave on exit
#include <exception>    // terminate



mainWindow::mainWindow() :
    game(new mainGame),
    current_window(WINDOW_GAME),
    game_window(new gameWindow(this)),
    menu_window(new menuWindow(this))
{
}

mainWindow::mainWindow(const mainGame &newgame) :
    game(new mainGame(newgame)),
    current_window(WINDOW_GAME),
    game_window(new gameWindow(this)),
    menu_window(new menuWindow(this))
{
    initialize_game();
}

mainWindow::mainWindow(const char* file) :
    game(new mainGame),
    current_window(WINDOW_GAME),
    game_window(new gameWindow(this)),
    menu_window(new menuWindow(this))
{
    load(file, MESSAGE_ERROR);
}

mainWindow::~mainWindow()
{
    delete game_window;
    delete menu_window;
    delete game;
}


void mainWindow::setgame(const mainGame &newgame)
{
    // but some require to be warned of changes
    // specifically, gameWindow needs to rebuild WINDOWS if dimentions changed
    *game = newgame;
    game_window->update_dimensions();
    initialize_game();
}

bool mainWindow::changegame(const mainGame& newgame)
{
    // use of this method is only allowed if dimentions are unchanged
    if(newgame.getwidth() == game->getwidth() &&
       newgame.getheight() == game->getheight() &&
       newgame.getform_size() == game->getform_size())
    {
        // because dimentions are the same, no other action is required
        *game = newgame;
        return true;
    }
    else return false;
}

const mainGame& mainWindow::getgame() const
{
    return *game;
}


bool mainWindow::input(int ch)
{
    // transfer input to the current active window and preform required
    // action depending on return code
    switch(current_window)
    {
    case WINDOW_GAME:
        switch(game_window->input(ch))
        {
        case gameWindow::RETURN_NONE:
            break;
        case gameWindow::RETURN_QUIT:
            current_window = WINDOW_MENU;
            break;
        case gameWindow::RETURN_NO_MOVE:
            // game over : save score and reinitialize game
            menu_window->add_score(game->getscore());
            game->restart();
            menu_window->print_score();
            break;
        default:
            mlog << "Unknown return code" << std::endl;
            std::terminate();
            break;
        }
        break;
    case WINDOW_MENU:
        switch(menu_window->input(ch))
        {
        case menuWindow::RETURN_NONE:
            break;
        case menuWindow::RETURN_RESUME:
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
        game_window->print();
        break;
    case WINDOW_MENU:
        menu_window->print();
        break;
    default:
        mlog << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }

    // and refresh screen
    doupdate();
}


bool mainWindow::save(const char *file, messageLevel verbose) const
{
    return menu_window->save(file, verbose);
}

bool mainWindow::load(const char *file, messageLevel verbose)
{
    bool success = menu_window->load(file, verbose);
    if(success) {
        initialize_game();
    }
    return success;
}

bool mainWindow::save_scores(const char *file) const
{
    return menu_window->save_score(file);
}

bool mainWindow::load_scores(const char *file)
{
    return menu_window->load_score(file);
}


bool mainWindow::add_form(size_t form, int x, int y)
{
    return game->add_form(form, x, y);
}


void mainWindow::initialize_game()
{
    // a loaded game may not have no forms selected
    game->random_select_forms(false);
}
