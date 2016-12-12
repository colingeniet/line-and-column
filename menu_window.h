#ifndef MENU_WINDOW_H_INCLUDED
#define MENU_WINDOW_H_INCLUDED

#include "main_game.h"      // used by menuWindow
#include "config_load.h"    // used for highscore file

#include <ncurses.h>        // used by menuWindow

#include <string>           // used by menuWindow
#include <cstddef>          // size_t

#define DEFAULT_BOARD "default_board"
#define AUTOSAVE_FILE "autosave"

#define SCORE_NUMBER 5
#define SCORE_FILE ".highscores"


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
        RETURN_QUIT,
        RETURN_MAX
    };

    menuWindow(mainGame*);
    ~menuWindow();

    // copying makes no sense : ncurses windows can not be copied
    menuWindow(const menuWindow&) = delete;
    menuWindow& operator=(const menuWindow&) = delete;

    void setgame(mainGame*);

    void print();
    void print_score();

    returnValue input(int);


    // add new score with name prompt (only if it is better than current scores)
    void add_score(int);

    enum messageLevel
    {
        MESSAGE_NONE,
        MESSAGE_ERROR,
        MESSAGE_ALL,
        MESSAGE_MAX
    };
    // return true if successfull, verbose control message printing
    // suppressed error message are printed to stderr instead
    bool save(const char *file, messageLevel verbose) const;
    bool load(const char *file, messageLevel verbose);

    bool save_score(const char*) const;
    bool load_score(const char*);

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

    std::string names[SCORE_NUMBER];
    int scores[SCORE_NUMBER];

    // perform actions corresponding to an entry and return the appropriate code
    returnValue excecute_entry(int);

    // nice prompt window with custom prompt message.
    std::string prompt(const std::string&) const;

    void updatemax_score();

    // wait for any input
    void hang() const;
};

#endif // MENU_WINDOW_H_INCLUDED
