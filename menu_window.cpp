#include "menu_window.h"

#include <iostream>
#include <exception>


menuWindow::menuWindow(mainGame *newgame) :
    window(newwin(0,0,0,0)),
    game(newgame),
    selected_entry(0)
{
    entry[ENTRY_RESUME] = "resume";
    entry[ENTRY_RESTART] = "restart";
    entry[ENTRY_SAVE] = "save";
    entry[ENTRY_LOAD] = "load";
    entry[ENTRY_SCORES] = "scores";
    entry[ENTRY_QUIT] = "quit";
}

menuWindow::~menuWindow()
{
    delwin(window);
}

void menuWindow::setgame(mainGame *newgame)
{
    game = newgame;
}


void menuWindow::print()
{
    wclear(window);

    int maxx, maxy, x, y;
    getmaxyx(window, maxy, maxx);

    y = (maxy - ENTRY_MAX + 1)/2;

    wattrset(window, A_BOLD);

    for(size_t i=0; i<ENTRY_MAX; i++) {
        x = (maxx - entry[i].size() + 1)/2;
        if(i == selected_entry) wattron(window, A_REVERSE);
        mvwprintw(window, y+i, x, "%s", entry[i].c_str());
        if(i == selected_entry) wattroff(window, A_REVERSE);
    }

    wnoutrefresh(window);
}

menuWindow::returnValue menuWindow::input(int ch)
{
    MEVENT event;

    switch(ch)
    {
    case KEY_UP:
        if(selected_entry == 0) selected_entry = ENTRY_MAX-1;
        else selected_entry--;
        break;
    case KEY_DOWN:
        if(selected_entry == ENTRY_MAX-1) selected_entry = 0;
        else selected_entry++;
        break;
    case '\n':
        return excecute_entry(selected_entry);
        break;
    case KEY_MOUSE:
        if(getmouse(&event) == OK)
        {
            if(wenclose(window, event.y, event.x))
            {
                wmouse_trafo(window, &event.y, &event.x, false);
                int x, y, maxx, maxy;
                getmaxyx(window, maxy, maxx);
                y = (maxy - ENTRY_MAX + 1)/2;
                for(size_t i=0; i<ENTRY_MAX; i++) {
                    x = (maxx - entry[i].size() + 1)/2;
                    if(event.y == y+(int)i &&
                       x <= event.x && event.x < x + (int)entry[i].size())
                    {
                        selected_entry = i;
                        if(event.bstate & BUTTON1_PRESSED) {
                            return excecute_entry(i);
                        }
                    }
                }
            }
        }
        break;
    default:
        break;
    }
    return RETURN_NONE;
}



menuWindow::returnValue menuWindow::excecute_entry(int entry)
{
    selected_entry = 0;
    switch(entry)
    {
    case ENTRY_RESUME:
        return RETURN_RESUME;
        break;
    case ENTRY_RESTART:
        game->restart();
        return RETURN_RESUME;
        break;
    case ENTRY_SAVE:
        return RETURN_NONE;
        break;
    case ENTRY_LOAD:
        return RETURN_RESUME;
        break;
    case ENTRY_SCORES:
        return RETURN_SCORES;
        break;
    case ENTRY_QUIT:
        return RETURN_QUIT;
        break;
    default:
        std::cerr << "Incorrect menu code" << std::endl;
        std::terminate();
        break;
    }
}
