#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"
#include "color.h"

#include <ncurses.h>

#include <cstddef>


/* main GUI class, link the GUI with the main game class */
class mainWindow
{
public:
    mainWindow(mainGame&);
    ~mainWindow();

    void print();

    // take a getch() input and perform corresponding move
    // return false if the game shall quit, true otherwise
    bool input(int);

private:
    WINDOW *borderWindow, *boardWindow, *scoreWindow;
    WINDOW *formWindow[N_FORMS];
    mainGame *board;

    void init_windows();

    void print_score();
    void print_board();
    void print_form(size_t);

    int cursor_x, cursor_y;
    size_t selected_form;
};


#endif // MAIN_WINDOW_H_INCLUDED
