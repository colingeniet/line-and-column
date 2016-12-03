#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED


#include "window_enum.h"
#include "game_window.h"

class mainWindow
{
public:
    mainWindow(mainGame&);

    void setgame(mainGame&);

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
