#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"      // used by mainWindow
#include "game_window.h"    // same
#include "menu_window.h"    // same


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

    // copying makes no sense
    mainWindow(const mainWindow&) = delete;
    mainWindow& operator=(const mainWindow&) = delete;

    // change the mainGame used
    void setgame(const mainGame&);

    // take a getch() input. return false if the game shall quit
    bool input(int);

    // print the current active window
    void print();

    // return true if successfull, verbose control message printing
    bool save(const char *file, menuWindow::messageLevel verbose) const;
    bool load(const char *file, menuWindow::messageLevel verbose);

    bool save_scores(const char *file = SCORE_FILE) const;
    bool load_scores(const char *file = SCORE_FILE);

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

    gameWindow game_window;
    menuWindow menu_window;

    // perform required action to make the game playable after
    // modification via setgame()
    void initialize_game();
};

#endif // MAIN_WINDOW_H_INCLUDED
