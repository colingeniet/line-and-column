#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"      // used by mainWindow
#include "game_window.h"    // same
#include "menu_window.h"    // same
#include "score_window.h"   // same


/* This class handle interaction between all GUI parts
 * Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class mainWindow
{
public:
    mainWindow();
    mainWindow(const char *file);
    mainWindow(const mainGame&);

    ~mainWindow();

    void setgame(const mainGame&);

    // take a getch() input. return false if the game shall quit
    bool input(int);

    void print();

private:
    mainGame *game;

    enum Window
    {
        WINDOW_GAME,
        WINDOW_MENU,
        WINDOW_SCORE,
        WINDOW_MAX
    };
    Window current_window;

    gameWindow game_window;
    menuWindow menu_window;
    scoreWindow score_window;

    // perform required action to make the game playable after
    // modification via setgame() or read()
    void initialize_game();
};

#endif // MAIN_WINDOW_H_INCLUDED
