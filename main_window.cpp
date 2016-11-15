#include "main_window.h"

#include <iostream>
#include <exception>


mainWindow::mainWindow(size_t width, size_t height, size_t form_size)
{
    int row, col, required_row, required_col;
    getmaxyx(stdscr, row, col);

    required_row = height + form_size + 7;

    required_col = 8;
    if(required_col < width+2) required_col = width+2;
    if(required_col < 3*form_size + 4) required_col = 3*form_size + 4;
    required_col *= 2;

    if(row < required_row || col < required_col)
    {
        endwin();
        std::cerr << "Terminal is too small : " << col << "x" << row
                  << " available, " << required_col << "x"
                  << required_row << " required." << std::endl;
        std::terminate();
    }

    borderWindow = newwin(required_row, required_col, 0, (col-required_col)/2);
    scoreWindow = newwin(3, required_col-4, 1, (col-required_col+4)/2);
    boardWindow = newwin(height, width*2, 5, (col - width*2)/2);
    formWindow1 = newwin(form_size, form_size*2,
                         height+6, (col - form_size*6 -4)/2);
    formWindow2 = newwin(form_size, form_size*2,
                         height+6, (col - form_size*2)/2);
    formWindow3 = newwin(form_size, form_size*2,
                         height+6, (col + form_size*2 +4)/2);


    if(has_colors())
    {
        wbkgd(borderWindow, COLOR_PAIR(BLACK_RED));
        wattron(scoreWindow, A_BOLD | COLOR_PAIR(RED_BLACK));
    }
    else
    {
        wbkgd(borderWindow, A_REVERSE);
        wattron(scoreWindow, A_BOLD);
    }

    //board = new mainGame(width, height, form_size);
}


mainWindow::~mainWindow()
{
    delwin(borderWindow);
    delwin(boardWindow);
    delwin(formWindow1);
    delwin(formWindow2);
    delwin(formWindow3);
    //delete board;
}


void mainWindow::print()
{
    wclear(scoreWindow);
    wclear(boardWindow);
    wclear(formWindow1);
    wclear(formWindow2);
    wclear(formWindow3);

    mvwprintw(scoreWindow, 1, 0, "over 9000");

    wrefresh(borderWindow);
    wrefresh(scoreWindow);
    wrefresh(boardWindow);
    wrefresh(formWindow1);
    wrefresh(formWindow2);
    wrefresh(formWindow3);
}
