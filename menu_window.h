#ifndef INCLUDEGUI_H_INCLUDED
// this file shall never be included, includeGUI.h must be used instead
#include "includeGUI.h"

#else

#ifndef MENU_WINDOW_H_INCLUDED
#define MENU_WINDOW_H_INCLUDED


#define DEFAULT_BOARD "default_board"
#define AUTOSAVE_FILE "autosave"
#define SCORE_FILE ".highscores"


#include "main_game.h"      // used by menuWindow
#include "config_load.h"    // used for highscore file

#include <ncurses.h>        // used by menuWindow

#include <string>           // used by menuWindow
#include <cstddef>          // size_t


#define SCORE_NUMBER 5


/* Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class menuWindow
{
public:
    enum messageLevel
    {
        MESSAGE_NONE,
        MESSAGE_ERROR,
        MESSAGE_ALL,
        MESSAGE_MAX
    };

    menuWindow(mainWindow*);
    ~menuWindow();

    // copying makes no sense : ncurses windows can not be copied
    menuWindow(const menuWindow&) = delete;
    menuWindow& operator=(const menuWindow&) = delete;

    void print();
    void print_score();

    bool input(int);


    // if the score is a highscore, prompt a name, add it and return true
    // else return false
    bool add_score(int);

    // return true if successfull, verbose control message printing
    // suppressed error message are printed to stderr instead
    bool save(const char *file, messageLevel verbose) const;
    bool load(const char *file, messageLevel verbose);

    bool save_score(const char*) const;
    bool load_score(const char*);

private:
    WINDOW *window;

    mainWindow *main_window;

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

    std::string names[SCORE_NUMBER];
    int scores[SCORE_NUMBER];

    // perform actions corresponding to an entry and return the appropriate code
    bool excecute_entry(int);

    // nice prompt window with custom prompt message.
    std::string prompt(const std::string&) const;

    void updatemax_score();

    // wait for any input
    void hang() const;
};


#endif // MENU_WINDOW_H_INCLUDED

#endif // INCLUDEGUI_H_INCLUDED
