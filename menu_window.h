#ifndef MENU_WINDOW_H_INCLUDED
#define MENU_WINDOW_H_INCLUDED

#include "main_game.h"  // used by menuWindow

#include <ncurses.h>    // used by menuWindow

#include <string>       // used by menuWindow
#include <cstddef>      // size_t

#define DEFAULT_BOARD "default_board"
#define AUTOSAVE_FILE "autosave"


/* Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class menuWindow
{
public:
    // input() return status to be interpreted by mainWindow::input()
    enum returnValue
    {
        RETURN_NONE,
        RETURN_RESUME,
        RETURN_UPDATE_GAME,
        RETURN_SCORES,
        RETURN_QUIT,
        RETURN_MAX
    };

    menuWindow(mainGame*);
    ~menuWindow();

    // copying makes no sense
    menuWindow(const menuWindow&) = delete;
    menuWindow& operator=(const menuWindow&) = delete;

    void setgame(mainGame*);

    void print();

    returnValue input(int);

    // return true if successfull, verbose control message printing
    bool save(const char *file, bool verbose) const;
    bool load(const char *file, bool verbose);

private:
    WINDOW *window;

    mainGame *game;

    enum menuEntry
    {
        ENTRY_RESUME,
        ENTRY_RESTART,
        ENTRY_SAVE,
        ENTRY_LOAD,
        ENTRY_LAST_SAVE,
        ENTRY_DEFAULT_SETTING,
        ENTRY_SCORES,
        ENTRY_QUIT,
        ENTRY_MAX
    };
    std::string entry[ENTRY_MAX];

    size_t selected_entry;

    // perform actions corresponding to an entry and return the appropriate code
    returnValue excecute_entry(int);

    // nice prompt window with custom prompt message
    std::string prompt(const std::string&) const;
};

#endif // MENU_WINDOW_H_INCLUDED
