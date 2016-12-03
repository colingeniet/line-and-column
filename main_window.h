#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"
#include "game_window.h"

#include <iostream>

/* This class handle interaction between all GUI parts
 * Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class mainWindow
{
public:
    mainWindow();
    mainWindow(const mainGame&);

    ~mainWindow();

    void setgame(const mainGame&);

    // take a getch() input. return false if the game shall quit
    bool input(int);

    void print();

    // perform required action to make the game playable after
    // modification via setgame() or read()
    void initialize_game();

    void write(std::ostream&) const;
    void read(std::istream&);

private:
    mainGame *game;

    enum Window
    {
        WINDOW_GAME,
        WINDOW_MAX
    } current_window;

    gameWindow game_window;

};


std::ostream& operator<<(std::ostream&, const mainWindow&);
std::istream& operator>>(std::istream&, mainWindow&);

#endif // MAIN_WINDOW_H_INCLUDED
