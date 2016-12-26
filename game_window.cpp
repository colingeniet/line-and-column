#include "includeGUI.h"

#include "global_log.h"     // errors

#include <string>           // for score display
#include <exception>        // terminate


#define SCORE_WINDOW_WIDTH 17
#define SCORE_WINDOW_HEIGHT 3




gameWindow::gameWindow(mainWindow *_main_window) :
    main_window(_main_window),
    cursor_x(main_window->getgame().getwidth()/2),
    cursor_y(main_window->getgame().getheight()/2),
    selected_form(0),
    history_pos(history.end())
{
    init_windows();
}

gameWindow::~gameWindow()
{
    if(borderWindow) delwin(borderWindow);
    if(boardWindow) delwin(boardWindow);
    if(scoreWindow) delwin(scoreWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        if(formWindow[i]) delwin(formWindow[i]);
    }
}


void gameWindow::update_dimensions()
{
    // recreation of all windows is required if size is changed
    delwin(borderWindow);
    delwin(boardWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        delwin(formWindow[i]);
    }

    cursor_x = main_window->getgame().getwidth()/2;
    cursor_y = main_window->getgame().getheight()/2;
    selected_form = 0;

    // modification which requires call to setgame() make the history invalid
    history.clear();
    history_pos = history.end();

    init_windows();
}



void gameWindow::init_windows()
{
    int width = main_window->getgame().getwidth();
    int height = main_window->getgame().getheight();
    int form_size = main_window->getgame().getform_size();

    // Windows placement
    int row, col, required_row, required_col, start_row, start_col;
    getmaxyx(stdscr, row, col);

    // just add everything for required height
    required_row = SCORE_WINDOW_HEIGHT + height + form_size + 4;

    // required width is the max of the 3 parts
    required_col = SCORE_WINDOW_WIDTH + 2;                  // score window
    if(required_col < width+2) {                            // board window
        required_col = width+2;
    }
    if(required_col < N_FORMS*form_size + N_FORMS + 1) {    // form windows
        required_col = N_FORMS*form_size + N_FORMS + 1;
    }
    required_col *= 2;  // 2 columns per square

    if(row < required_row || col < required_col)
    {
        endwin();
        mlog << "Terminal is too small : " << col << "x" << row
             << " available, " << required_col << "x"
             << required_row << " required." << std::endl;
        std::terminate();
    }

    // upper left corner of the used space
    start_row = (row - required_row)/2;
    start_col = (col - required_col)/2;

    // create windows
    borderWindow = newwin(required_row, required_col,
                          start_row, start_col);
    // score window is as large as possible
    scoreWindow = newwin(SCORE_WINDOW_HEIGHT, required_col - 4,
                         start_row + 1, start_col + 2);
    boardWindow = newwin(height, width*2,
                         start_row + SCORE_WINDOW_HEIGHT + 2, col/2 - width);
    for(size_t i=0; i<N_FORMS; i++) {
        formWindow[i] = newwin(form_size, form_size*2,
                               start_row + height + SCORE_WINDOW_HEIGHT + 3,
                               col/2 + (2*i - N_FORMS)*(form_size+1) + 1);
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
    case '\n':  // different codes enter may produce
    case '\r':
    case KEY_ENTER:
        // only keep history strictly before current position
        history.erase(history_pos, history.end());
        // add current state
        history.push_back(main_window->getgame());
        history_pos = history.end();

        main_window->add_form(selected_form, cursor_x, cursor_y);
        break;
    case 'z':
        // going back in history :
        // check not at the begining
        if(history_pos != history.begin()) {
            // if at the end, current state must be saved
            if(history_pos == history.end()) {
                history.push_back(main_window->getgame());
                // and set history_pos to the current state :
                // without this, history_pos was history.end(), and would still
                // be after push_back() due to the way lists works
                --history_pos;
            }
            // game in history have same dimensions
            // -> no need to warn to other classes from change
            main_window->changegame(*--history_pos);
        }
        break;
    case 'Z':
        // going forward in history
        if(history_pos != history.end() &&
           history_pos != --history.end() ) {
            // game in history have same dimensions
            // -> no need to warn to other classes from change
            main_window->changegame(*++history_pos);
        }
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
                    // only keep history strictly before current position
                    history.erase(history_pos, history.end());
                    // add current state
                    history.push_back(main_window->getgame());
                    history_pos = history.end();

                    main_window->add_form(selected_form, cursor_x, cursor_y);
                }
            }
            else
            {
                // test for form selection
                int startx, starty;
                getbegyx(formWindow[0], starty, startx);
                int x = event.x - startx;

                // mouse is inside bottom area
                if(starty <= event.y &&
                   event.y < starty + main_window->getgame().getform_size() &&
                   x >= 0 &&
                   x < N_FORMS * (main_window->getgame().getform_size()+1)*2)
                {
                    int n = x/((main_window->getgame().getform_size()+1)*2);

                    // check that the mouse is not in the band between windows
                    x %= (main_window->getgame().getform_size()+1)*2;
                    if(x < main_window->getgame().getform_size()*2) {
                        if(event.bstate & BUTTON1_PRESSED) selected_form = n;
                    }
                }
            }
        }
    default:
        break;
    }

    cursor_bounds();

    if( !main_window->getgame().move_available() ) return RETURN_NO_MOVE;
    else return RETURN_NONE;
}

void gameWindow::cursor_bounds()
{
    int minx = - main_window->getgame().getform(selected_form).getboxmin().x;
    int miny = - main_window->getgame().getform(selected_form).getboxmin().y;
    int maxx = main_window->getgame().getwidth()
               -main_window->getgame().getform(selected_form).getboxmax().x - 1;
    int maxy = main_window->getgame().getheight()
               -main_window->getgame().getform(selected_form).getboxmax().y - 1;
    if(cursor_x < minx) cursor_x = minx;
    if(cursor_y < miny) cursor_y = miny;
    if(cursor_x > maxx) cursor_x = maxx;
    if(cursor_y > maxy) cursor_y = maxy;
}


void gameWindow::print()
{
    wbkgd(borderWindow, A_REVERSE);
    print_score();
    print_board();
    for(size_t i=0; i<N_FORMS; i++) {
        print_form(i);
    }

    // border window is filled with background color, other windows are
    // printed over it
    wnoutrefresh(borderWindow);

    wnoutrefresh(scoreWindow);
    wnoutrefresh(boardWindow);
    for(size_t i=0; i<N_FORMS; i++) {
        wnoutrefresh(formWindow[i]);
    }
}

void gameWindow::print_score()
{
    int x = getmaxx(scoreWindow);
    std::string str;

    wclear(scoreWindow);
    wattron(scoreWindow, A_BOLD);
    if(has_colors()) {
        wattron(scoreWindow, COLOR_PAIR(RED_BLACK));
    }

    str = "SCORE : " + std::to_string(main_window->getgame().getscore());
    if(main_window->getgame().getcombo() >= 2) {
        str += " x" + std::to_string(main_window->getgame().getcombo());
    }

    mvwprintw(scoreWindow, 1, 1, "%s", str.c_str());

    str = "BEST : " + std::to_string(main_window->getgame().getmax_score());

    if(has_colors()) {
        wattron(scoreWindow, COLOR_PAIR(YELLOW_BLACK));
    }

    mvwprintw(scoreWindow, 1, x-str.size()-1, "%s", str.c_str());
}

void gameWindow::print_board()
{
    wclear(boardWindow);
    // fixed forms
    for(int x=0; x<main_window->getgame().getwidth(); x++) {
        for(int y=0; y<main_window->getgame().getheight(); y++) {
            int attr = get_attr_color( main_window->getgame()[x][y] );
            wattron(boardWindow, attr);
            mvwprintw(boardWindow, y, 2*x, "  ");
            wattroff(boardWindow, attr);
        }
    }

    // current selected form
    Form form = main_window->getgame().getform(selected_form);
    wattron(boardWindow, get_attr_color(main_window->getgame().getform_color(selected_form)));
    for(size_t i=0; i<form.getsize(); i++) {
        int x = cursor_x + form[i].x;
        int y = cursor_y + form[i].y;
        mvwprintw(boardWindow, y, 2*x, "  ");
    }
    wattroff(boardWindow, get_attr_color(main_window->getgame().getform_color(selected_form)));
}

void gameWindow::print_form(size_t n)
{
    Form form = main_window->getgame().getform(n);
    wclear(formWindow[n]);
    wattron(formWindow[n], get_attr_color(main_window->getgame().getform_color(n)));
    for(size_t i=0; i<form.getsize(); i++) {
        mvwprintw(formWindow[n],
                  form[i].y + main_window->getgame().getform_size()/2,
                  2*(form[i].x + main_window->getgame().getform_size()/2), "  ");
    }
    wattroff(formWindow[n], get_attr_color(main_window->getgame().getform_color(n)));
}
