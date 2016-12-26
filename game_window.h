#ifndef INCLUDEGUI_H_INCLUDED
// this file shall never be included, includeGUI.h must be used instead
#include "includeGUI.h"

#else

#ifndef GAME_WINDOW_H_INCLUDED
#define GAME_WINDOW_H_INCLUDED


#include "main_game.h"      // used by gameWindow
#include "color.h"          // used for printing

#include <ncurses.h>        // used by gameWindow

#include <cstddef>          // size_t
#include <list>             // for move history


/* main game display
 * Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class gameWindow
{
public:
    gameWindow(mainWindow*);
    ~gameWindow();

    // copying makes no sense : ncurses windows can not be copied
    gameWindow(const gameWindow&) = delete;
    gameWindow& operator=(const gameWindow&) = delete;

    void update_dimensions();

    void print();

    void input(int);


private:
    WINDOW *borderWindow, *boardWindow, *scoreWindow;
    WINDOW *formWindow[N_FORMS];

    mainWindow *main_window;

    int cursor_x, cursor_y;
    size_t selected_form;

    std::list<mainGame> history;
    std::list<mainGame>::iterator history_pos;

    // create all WINDOW objects (size calculation)
    void init_windows();

    // put cursor back inside bounds
    void cursor_bounds();

    // subwindows print functions
    void print_score();
    void print_board();
    void print_form(size_t);
};


#endif // GAME_WINDOW_H_INCLUDED

#endif // INCLUDEGUI_H_INCLUDED
