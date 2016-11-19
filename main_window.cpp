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
    delwin(formWindow1);
    delwin(formWindow2);
    delwin(formWindow3);
    delete board;
}


void mainWindow::print()
{
    print_score();
    print_board();
    print_form1();
    print_form2();
    print_form3();

    wrefresh(borderWindow);
    wrefresh(scoreWindow);
    wrefresh(boardWindow);
    wrefresh(formWindow1);
    wrefresh(formWindow2);
    wrefresh(formWindow3);
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

void mainWindow::print_form1()
{
    Form form = board->getform1();
    wclear(formWindow1);
    wattron(formWindow1, COLOR_PAIR(BLACK_RED));
    for(size_t n=0; n<form.getsize(); n++) {
        mvwprintw(formWindow1, form[n].y, form[n].y, " ");
    }
    wattroff(formWindow1, COLOR_PAIR(BLACK_RED));
}

void mainWindow::print_form2()
{
    Form form = board->getform2();
    wclear(formWindow2);
    wattron(formWindow2, COLOR_PAIR(BLACK_RED));
    for(size_t n=0; n<form.getsize(); n++) {
        mvwprintw(formWindow2, form[n].y, form[n].y, " ");
    }
    wattroff(formWindow2, COLOR_PAIR(BLACK_RED));
}

void mainWindow::print_form3()
{
    Form form = board->getform3();
    wclear(formWindow3);
    wattron(formWindow3, COLOR_PAIR(BLACK_RED));
    for(size_t n=0; n<form.getsize(); n++) {
        mvwprintw(formWindow3, form[n].y, form[n].y, " ");
    }
    wattroff(formWindow3, COLOR_PAIR(BLACK_RED));
}
