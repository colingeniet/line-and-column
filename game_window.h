#ifndef GAME_WINDOW_H_INCLUDED
#define GAME_WINDOW_H_INCLUDED

#include "main_game.h"
#include "color.h"

#include <ncurses.h>

#include <cstddef>


/* main GUI class, link the GUI with the main game class */
class gameWindow
{
public:
    // input() return status
    enum returnValue
    {
        RETURN_NONE,
        RETURN_MAX
    };

    gameWindow(mainGame&);
    ~gameWindow();

    void setgame(mainGame&);

    void print();

    // take a getch() input and perform corresponding move
    // return false if the game shall quit, true otherwise
    bool input(int);


private:
    WINDOW *borderWindow, *boardWindow, *scoreWindow;
    WINDOW *formWindow[N_FORMS];
    mainGame *game;

    void init_windows();

    void cursor_bounds();

    void print_score();
    void print_board();
    void print_form(size_t);

    int cursor_x, cursor_y;
    size_t selected_form;
};


#endif // GAME_WINDOW_H_INCLUDED
