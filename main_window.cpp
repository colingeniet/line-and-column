#include "includeGUI.h"

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
    initialize_game();
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
    load(file, menuWindow::MESSAGE_ERROR);
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
        game_window->input(ch);
        break;
    case WINDOW_MENU:
        return menu_window->input(ch);
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


void mainWindow::setwindow(mainWindow::Window win)
{
    current_window = win;
}


bool mainWindow::add_score(int score)
{
    return menu_window->add_score(score);
}

void mainWindow::print_score()
{
    menu_window->print_score();
}

bool mainWindow::save(const char *file, menuWindow::messageLevel verbose) const
{
    return menu_window->save(file, verbose);
}

bool mainWindow::load(const char *file, menuWindow::messageLevel verbose)
{
    bool success = menu_window->load(file, verbose);
    if(success) initialize_game();
    return success;
}

bool mainWindow::save_scores(const char *file) const
{
    return menu_window->save_score(file);
}

bool mainWindow::load_scores(const char *file)
{
    bool success = menu_window->load_score(file);
    if(success) initialize_game();
    return success;
}


bool mainWindow::add_form(size_t form, int x, int y)
{
    return game->add_form(form, x, y);
}


void mainWindow::initialize_game()
{
    // a loaded game may not have no forms selected
    game->random_select_forms(false);
    // set max score
    menu_window->updatemax_score();
    // start history
    game_window->initialize_history();
}
