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
    /* parameters : width, height (main board), maximum form size */
    mainWindow(int, int, int);
    ~mainWindow();

    void print();

    bool input(int);

    bool add_form_to_set(const Form&, int);

    void random_select_forms();

private:
    WINDOW *borderWindow, *boardWindow, *scoreWindow;
    WINDOW *formWindow[N_FORMS];
    mainGame *board;

    void print_score();
    void print_board();
    void print_form(size_t);

    int cursor_x, cursor_y;
    size_t selected_form;
};


#endif // MAIN_WINDOW_H_INCLUDED
