#include "menu_window.h"

#include <iostream>
#include <exception>


menuWindow::menuWindow() :
    window(newwin(0,0,0,0)),
    selected_entry(0)
{
    entry[ENTRY_RESUME] = "resume";
    entry[ENTRY_RESTART] = "restart";
    entry[ENTRY_SCORES] = "scores";
    entry[ENTRY_QUIT] = "quit";
}

menuWindow::~menuWindow()
{
    delwin(window);
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
        switch(selected_entry)
        {
        case ENTRY_RESUME:
            return RETURN_RESUME;
            break;
        case ENTRY_RESTART:
            return RETURN_RESTART;
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
    default:
        break;
    }
    return RETURN_NONE;
}
