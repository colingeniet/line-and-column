#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

//#include "main_game.h"

#include <ncurses.h>
#include "color.h"

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
    //mainGame *board;

    int cursor_x, cursor_y;

    bool has_mouse, has_color;
};


#endif // MAIN_WINDOW_H_INCLUDED
