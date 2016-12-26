#ifndef INCLUDEGUI_H_INCLUDED
// this file shall never be included, includeGUI.h must be used instead
#include "includeGUI.h"

#else

#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"

/* This class handle interaction between all GUI parts
 * Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class mainWindow
{
public:
    mainWindow();
    mainWindow(const char *file);
    mainWindow(const mainGame&);

    ~mainWindow();

    // copying makes no sense : ncurses windows can not be copied
    mainWindow(const mainWindow&) = delete;
    mainWindow& operator=(const mainWindow&) = delete;

    // change the mainGame used
    void setgame(const mainGame&);
    // unlike setgame(), it is required that board dimension are not changed
    // it does not reinitialize everything
    bool changegame(const mainGame&);

    const mainGame& getgame() const;

    // take a getch() input. return false if the game shall quit
    bool input(int);

    // print the current active window
    void print();

    // return true if successfull, verbose control message printing
    // int is used instead of menuWindow::messageLevel due to cross declarations
    bool save(const char *file, int verbose) const;
    bool load(const char *file, int verbose);

    bool save_scores(const char *file = SCORE_FILE) const;
    bool load_scores(const char *file = SCORE_FILE);

    // interface with mainGame
    bool add_form(size_t, int, int);

private:
    mainGame *game;

    // indicate which of the Window subclass is active
    enum Window
    {
        WINDOW_GAME,
        WINDOW_MENU,
        WINDOW_MAX
    };
    Window current_window;

    gameWindow *game_window;
    menuWindow *menu_window;

    // perform required action to make the game playable after
    // modification via setgame()
    void initialize_game();
};

#endif // MAIN_WINDOW_H_INCLUDED

#endif // INCLUDEGUI_H_INCLUDED
