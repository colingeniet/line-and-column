#include "main_window.h"

#include <iostream>
#include <exception>


mainWindow::mainWindow(size_t width, size_t height, size_t form_size) :
    cursor_x(width/2),
    cursor_y(height/2)
{
    int row, col, required_row, required_col;
    getmaxyx(stdscr, row, col);

    required_row = height + form_size + 7;

    required_col = 8;
    if(required_col < width+2) {
        required_col = width+2;
    }
    if(required_col < N_FORMS*form_size + N_FORMS + 1) {
        required_col = N_FORMS*form_size + N_FORMS + 1;
    }
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
    for(size_t i=0; i<N_FORMS; i++) {
        formWindow[i] = newwin(form_size, form_size*2, height+6,
                               col/2 + (2*i - N_FORMS)*(form_size+1) + 1);
    }


    wbkgd(borderWindow, A_REVERSE);

    if(has_colors())
    {
        wattron(scoreWindow, A_BOLD | COLOR_PAIR(BLUE_BLACK));
    }
    else
    {
        wattron(scoreWindow, A_BOLD);
    }

    board = new mainGame(width, height, form_size);
}


mainWindow::~mainWindow()
{
    delwin(borderWindow);
    delwin(boardWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        delwin(formWindow[i]);
    }
    delete board;
}


void mainWindow::print()
{
    print_score();
    print_board();
    for(size_t i=0; i<N_FORMS; i++) {
        print_form(i);
    }

    wrefresh(borderWindow);
    wrefresh(scoreWindow);
    wrefresh(boardWindow);

    for(size_t i=0; i<N_FORMS; i++) {
        wrefresh(formWindow[i]);
    }
}

void mainWindow::print_score()
{
    wclear(scoreWindow);
    mvwprintw(scoreWindow, 1, 1,
              "%i", board->getscore());
    if(board->getcombo() >= 2) {
        wprintw(scoreWindow, " X%i", board->getcombo());
    }
}

void mainWindow::print_board()
{
    wclear(boardWindow);
    for(size_t x=0; x<board->getwidth(); x++) {
        for(size_t y=0; y<board->getheight(); y++) {
            if( (*board)[x][y] ) {
                wattron(boardWindow, COLOR_PAIR(BLACK_RED));
                mvwprintw(boardWindow, y, x, " ");
                wattroff(boardWindow, COLOR_PAIR(BLACK_RED));
            }
        }
    }
}

void mainWindow::print_form(size_t n)
{
    Form form = board->getform(n);
    wclear(formWindow[n]);
    wattron(formWindow[n], COLOR_PAIR(BLACK_RED));
    for(size_t i=0; i<form.getsize(); i++) {
        mvwprintw(formWindow[n], form[i].y, form[i].y, " ");
    }
    wattroff(formWindow[n], COLOR_PAIR(BLACK_RED));
}
