#ifndef MENU_WINDOW_H_INCLUDED
#define MENU_WINDOW_H_INCLUDED

#include "main_game.h"

#include <ncurses.h>

#include <string>
#include <cstddef>


/* Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class menuWindow
{
public:
    // input() return status
    enum returnValue
    {
        RETURN_NONE,
        RETURN_RESUME,
        RETURN_SCORES,
        RETURN_QUIT,
        RETURN_MAX
    };

    menuWindow(mainGame*);
    ~menuWindow();

    void setgame(mainGame*);

    void print();

    returnValue input(int);


private:
    WINDOW *window;

    mainGame *game;

    enum menuEntry
    {
        ENTRY_RESUME,
        ENTRY_RESTART,
        ENTRY_SAVE,
        ENTRY_LOAD,
        ENTRY_SCORES,
        ENTRY_QUIT,
        ENTRY_MAX
    };
    std::string entry[ENTRY_MAX];

    size_t selected_entry;

    // perform actions corresponding to an entry and return the appropriate code
    returnValue excecute_entry(int);
};

#endif // MENU_WINDOW_H_INCLUDED
