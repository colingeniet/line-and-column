#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"
#include "color.h"

#include <ncurses.h>

/* main GUI class, link the GUI with the main game class */
class mainWindow
{
public:
    /* parameters : width, height (main board), maximum form size */
    mainWindow(size_t, size_t, size_t);
    ~mainWindow();

    void print();

private:
    WINDOW *borderWindow, *boardWindow, *scoreWindow,
            *formWindow1, *formWindow2, *formWindow3;
    mainGame *board;

    void print_score();
    void print_board();
    void print_form1();
    void print_form2();
    void print_form3();

    int cursor_x, cursor_y;
};


#endif // MAIN_WINDOW_H_INCLUDED
