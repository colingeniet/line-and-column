#include "game_window.h"

#include <iostream>
#include <exception>


#define SCORE_WINDOW_WIDTH 8
#define SCORE_WINDOW_HEIGHT 3




gameWindow::gameWindow(mainGame *newgame) :
    game(newgame),
    cursor_x(game->getwidth()/2),
    cursor_y(game->getheight()/2),
    selected_form(0)
{
    init_windows();
}

gameWindow::~gameWindow()
{
    delwin(borderWindow);
    delwin(boardWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        delwin(formWindow[i]);
    }
}

void gameWindow::setgame(mainGame *newgame)
{
    delwin(borderWindow);
    delwin(boardWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        delwin(formWindow[i]);
    }

    game = newgame;
    cursor_x = game->getwidth()/2;
    cursor_y = game->getheight()/2;
    selected_form = 0;

    init_windows();
}



void gameWindow::init_windows()
{
    int width = game->getwidth();
    int height = game->getheight();
    int form_size = game->getform_size();

    // Windows placement
    int row, col, required_row, required_col;
    getmaxyx(stdscr, row, col);

    required_row = SCORE_WINDOW_HEIGHT + height + form_size + 4;

    required_col = SCORE_WINDOW_WIDTH + 2;
    if(required_col < width+2) {
        required_col = width+2;
    }
    if(required_col < N_FORMS*form_size + N_FORMS + 1) {
        required_col = N_FORMS*form_size + N_FORMS + 1;
    }
    required_col *= 2;  // 2 columns per square

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
    // score window is as large as possible
    scoreWindow = newwin(SCORE_WINDOW_HEIGHT, required_col-4,
                         1, (col-required_col+4)/2);
    boardWindow = newwin(height, width*2,
                         SCORE_WINDOW_HEIGHT + 2, (col - width*2)/2);
    for(size_t i=0; i<N_FORMS; i++) {
        formWindow[i] = newwin(form_size, form_size*2,
                               height + SCORE_WINDOW_HEIGHT + 3,
                               col/2 + (2*i - N_FORMS)*(form_size+1) + 1);
    }

    // initialise colors

    // border window is filled with background color, other windows are
    // print over it
    wbkgd(borderWindow, A_REVERSE);

    if(has_colors()) {
        wattron(scoreWindow, A_BOLD | COLOR_PAIR(BLUE_BLACK));
    } else {
        wattron(scoreWindow, A_BOLD);
    }
}


gameWindow::returnValue gameWindow::input(int ch)
{
    MEVENT event;

    switch(ch)
    {
    case 'q':
        return RETURN_QUIT;
        break;
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
    case 'x':
        if(0 < N_FORMS) selected_form = 0;
        break;
    case '2':
    case 'c':
        if(1 < N_FORMS) selected_form = 1;
        break;
    case '3':
    case 'v':
        if(2 < N_FORMS) selected_form = 2;
        break;
    case KEY_PPAGE:
        if(selected_form == 0) selected_form = N_FORMS-1;
        else selected_form--;
        break;
    case KEY_NPAGE:
        if(selected_form == N_FORMS-1) selected_form = 0;
        else selected_form++;
        break;
    case '\n':
        game->add_form(selected_form, cursor_x, cursor_y);
        break;
    case KEY_MOUSE:
        if(getmouse(&event) == OK)
        {
            if(wenclose(boardWindow, event.y, event.x))
            {
                wmouse_trafo(boardWindow, &event.y, &event.x, false);
                cursor_x = event.x / 2;
                cursor_y = event.y;

		// because mouse allow movement and click at the same time,
		// the cursor must be rechecked before adding the form
		cursor_bounds();

                if(event.bstate & BUTTON1_PRESSED)
                {
                    game->add_form(selected_form, cursor_x, cursor_y);
                }
            }
            else
            {
                for(size_t i=0; i<N_FORMS; i++) {
                    if(wenclose(formWindow[i], event.y, event.x) &&
                       (event.bstate & BUTTON1_PRESSED) ) {
                        selected_form = i;
                    }
                }
            }
        }
    default:
        break;
    }

    cursor_bounds();

    if( !game->move_available() ) return RETURN_NO_MOVE;
    else return RETURN_NONE;
}

void gameWindow::cursor_bounds()
{
    int minx = - game->getform(selected_form).getboxmin().x;
    int miny = - game->getform(selected_form).getboxmin().y;
    int maxx = game->getwidth()
      - game->getform(selected_form).getboxmax().x - 1;
    int maxy = game->getheight()
      - game->getform(selected_form).getboxmax().y - 1;
    if(cursor_x < minx) cursor_x = minx;
    if(cursor_y < miny) cursor_y = miny;
    if(cursor_x > maxx) cursor_x = maxx;
    if(cursor_y > maxy) cursor_y = maxy;
}


void gameWindow::print()
{
    print_score();
    print_board();
    for(size_t i=0; i<N_FORMS; i++) {
        print_form(i);
    }

    wnoutrefresh(borderWindow);
    wnoutrefresh(scoreWindow);
    wnoutrefresh(boardWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        wnoutrefresh(formWindow[i]);
    }

    doupdate();
}

void gameWindow::print_score()
{
    wclear(scoreWindow);
    mvwprintw(scoreWindow, 1, 1,
              "%i", game->getscore());
    if(game->getcombo() >= 2) {
        wprintw(scoreWindow, " X%i", game->getcombo());
    }
}

void gameWindow::print_board()
{
    wclear(boardWindow);
    // fixed forms
    for(int x=0; x<game->getwidth(); x++) {
        for(int y=0; y<game->getheight(); y++) {
            int attr = get_attr_color( (*game)[x][y] );
            wattron(boardWindow, attr);
            mvwprintw(boardWindow, y, 2*x, "  ");
            wattroff(boardWindow, attr);
        }
    }

    // current selected form
    Form form = game->getform(selected_form);
    wattron(boardWindow, get_attr_color(game->getform_color(selected_form)));
    for(size_t i=0; i<form.getsize(); i++) {
        int x = cursor_x + form[i].x;
        int y = cursor_y + form[i].y;
        if(0<=x && x<game->getwidth() && 0<=y && y<game->getheight()) {
            mvwprintw(boardWindow, y, 2*x, "  ");
        }
    }
    wattroff(boardWindow, get_attr_color(game->getform_color(selected_form)));
}

void gameWindow::print_form(size_t n)
{
    Form form = game->getform(n);
    wclear(formWindow[n]);
    wattron(formWindow[n], get_attr_color(game->getform_color(n)));
    for(size_t i=0; i<form.getsize(); i++) {
        mvwprintw(formWindow[n],
                  form[i].y + game->getform_size()/2,
                  2*form[i].x + (game->getform_size()/2)*2, "  ");
    }
    wattroff(formWindow[n], get_attr_color(game->getform_color(n)));
}
