#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED


#include "game_window.h"

class mainWindow
{
public:
    mainWindow(mainGame&);

    void setgame(mainGame&);

    // return false if the game shall quit
    bool input(int);

    void print();

private:
    mainGame *game;

    enum Window
    {
        WINDOW_GAME,
        WINDOW_MAX
    } current_window;

    gameWindow game_window;

};

#endif // MAIN_WINDOW_H_INCLUDED
