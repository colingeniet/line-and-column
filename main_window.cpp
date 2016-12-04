#include "main_window.h"

#include <iostream>
#include <exception>



mainWindow::mainWindow() :
    game(new mainGame()),
    current_window(WINDOW_GAME),
    game_window(game),
    menu_window(game),
    score_window()
{
}

mainWindow::mainWindow(const mainGame &newgame) :
    game(new mainGame(newgame)),
    current_window(WINDOW_GAME),
    game_window(game),
    menu_window(game),
    score_window()
{
}

void mainWindow::setgame(const mainGame &newgame)
{
    *game = newgame;
    game_window.setgame(game);
    menu_window.setgame(game);
}

mainWindow::~mainWindow()
{
    delete game;
}


bool mainWindow::input(int ch)
{
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
            score_window.add_score(game->getscore());
            game->restart();
            current_window = WINDOW_SCORE;
            break;
        default:
            std::cerr << "Unknown return code" << std::endl;
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
        case menuWindow::RETURN_SCORES:
            current_window = WINDOW_SCORE;
            break;
        case menuWindow::RETURN_QUIT:
            return false;
            break;
        default:
            std::cerr << "Unknown return code" << std::endl;
            std::terminate();
            break;
        }
        break;
    case WINDOW_SCORE:
        // the only thing to do when in the score window is to quit
        // so there is no proper input method for it
        if(ch != KEY_MOUSE) current_window = WINDOW_MENU;
        break;
    default:
        std::cerr << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }
    return true;
}

void mainWindow::print()
{
    switch(current_window)
    {
    case WINDOW_GAME:
        game_window.print();
        break;
    case WINDOW_MENU:
        menu_window.print();
        break;
    case WINDOW_SCORE:
        score_window.print();
        break;
    default:
        std::cerr << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }

    doupdate();
}


void mainWindow::initialize_game()
{
    game->random_select_forms(false);
}


void mainWindow::write(std::ostream &os) const
{
    game->stream_write(os);
}

void mainWindow::read(std::istream &is)
{
    setgame(mainGame::stream_read(is));
}


std::ostream& operator<<(std::ostream &os, const mainWindow &win)
{
    win.write(os);
    return os;
}

std::istream& operator>>(std::istream &is, mainWindow &win)
{
    win.read(is);
    return is;
}
