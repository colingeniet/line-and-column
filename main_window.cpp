#include "main_window.h"

#include <iostream>
#include <exception>


mainWindow::mainWindow(mainGame &newgame) :
    game(&newgame),
    current_window(WINDOW_GAME),
    game_window(newgame)
{
}

void mainWindow::setgame(mainGame &newgame)
{
    game = &newgame;
    game_window.setgame(newgame);
}


bool mainWindow::input(int ch)
{
    switch(current_window)
    {
    case WINDOW_GAME:
        return game_window.input(ch);
        break;
    default:
        std::cerr << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }
}

void mainWindow::print()
{
    switch(current_window)
    {
    case WINDOW_GAME:
        game_window.print();
        break;
    default:
        std::cerr << "Incorrect window code" << std::endl;
        std::terminate();
        break;
    }
}
