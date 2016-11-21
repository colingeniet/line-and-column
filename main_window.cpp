#include "main_window.h"

#include <iostream>
#include <exception>



mainWindow::mainWindow(int width, int height, int form_size) :
    cursor_x(width/2),
    cursor_y(height/2),
    selected_form(0)
{
    // Windows placement
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

    // create windows
    borderWindow = newwin(required_row, required_col, 0, (col-required_col)/2);
    scoreWindow = newwin(3, required_col-4, 1, (col-required_col+4)/2);
    boardWindow = newwin(height, width*2, 5, (col - width*2)/2);
    for(size_t i=0; i<N_FORMS; i++) {
        formWindow[i] = newwin(form_size, form_size*2, height+6,
                               col/2 + (2*i - N_FORMS)*(form_size+1) + 1);
    }


    // initialise colors
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


bool mainWindow::add_form_to_set(const Form &form, int color)
{
    return board->add_form_to_set(form, color);
}


bool mainWindow::input(int ch)
{
    switch(ch)
    {
        // no bound testing here, done below
    case KEY_UP:
        cursor_y--;
        break;
    case KEY_DOWN:
        cursor_y++;
        break;
    case KEY_LEFT:
        cursor_x--;
        break;
    case KEY_RIGHT:
        cursor_x++;
        break;
    case '1':
        selected_form = 0;
        break;
    case '2':
        selected_form = 1;
        break;
    case '3':
        selected_form = 2;
        break;
    case '\n':
        board->add_form(selected_form, cursor_x, cursor_y);
        if( !board->move_available() ) return false;
        break;
    case 'q':
        return false;
        break;
    default:
        break;
    }
    // since various command may affect bounds, testing is done here
    int minx = - board->getform(selected_form).getboxmin().x;
    int miny = - board->getform(selected_form).getboxmin().y;
    int maxx = board->getwidth()
                - board->getform(selected_form).getboxmax().x - 1;
    int maxy = board->getheight()
                - board->getform(selected_form).getboxmax().y - 1;
    if(cursor_x < minx) cursor_x = minx;
    if(cursor_y < miny) cursor_y = miny;
    if(cursor_x > maxx) cursor_x = maxx;
    if(cursor_y > maxy) cursor_y = maxy;

    return true;
}

void mainWindow::random_select_forms()
{
    board->random_select_forms();
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
    for(int x=0; x<board->getwidth(); x++) {
        for(int y=0; y<board->getheight(); y++) {
            int attr = get_attr_color( (*board)[x][y] );
            wattron(boardWindow, attr);
            mvwprintw(boardWindow, y, 2*x, "  ");
            wattroff(boardWindow, attr);
        }
    }

    Form form = board->getform(selected_form);
    wattron(boardWindow, get_attr_color(board->getform_color(selected_form)));
    for(size_t i=0; i<form.getsize(); i++) {
        int x = cursor_x + form[i].x;
        int y = cursor_y + form[i].y;
        if(0<=x && x<board->getwidth() && 0<=y && y<board->getheight()) {
            mvwprintw(boardWindow, y, 2*x, "  ");
        }
    }
    wattroff(boardWindow, get_attr_color(board->getform_color(selected_form)));
}

void mainWindow::print_form(size_t n)
{
    Form form = board->getform(n);
    wclear(formWindow[n]);
    wattron(formWindow[n], get_attr_color(board->getform_color(n)));
    for(size_t i=0; i<form.getsize(); i++) {
        mvwprintw(formWindow[n],
                  form[i].y + board->getform_size()/2,
                  2*form[i].x + (board->getform_size()/2)*2, "  ");
    }
    wattroff(formWindow[n], get_attr_color(board->getform_color(n)));
}
