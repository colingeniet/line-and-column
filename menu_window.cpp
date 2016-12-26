#include "includeGUI.h"

#include "global_log.h"     // errors
#include "config_load.h"    // syntax_exception

#include <fstream>          // save / load
#include <exception>        // terminate / std::exception


menuWindow::menuWindow(mainWindow *_main_window) :
    window(newwin(0,0,0,0)),    // full screen window
    main_window(_main_window),
    selected_entry(0)
{
    entry[ENTRY_RESUME] = "resume";
    entry[ENTRY_RESTART] = "restart";
    entry[ENTRY_SAVE] = "save game";
    entry[ENTRY_LOAD] = "load game";
    entry[ENTRY_LAST_SAVE] = "load autosave";
    entry[ENTRY_DEFAULT_SETTING] = "default rules";
    entry[ENTRY_SCORES] = "highscores";
    entry[ENTRY_QUIT] = "quit";

    for(size_t i=0; i<SCORE_NUMBER; i++) {
        scores[i] = 0;
    }

    wattrset(window, A_BOLD);
}

menuWindow::~menuWindow()
{
    if(window) delwin(window);
}


void menuWindow::print()
{
    wclear(window);

    int maxx, maxy, x, y;
    getmaxyx(window, maxy, maxx);

    y = (maxy - ENTRY_MAX + 1)/2;

    for(size_t i=0; i<ENTRY_MAX; i++) {
        x = (maxx - entry[i].size() + 1)/2;
        if(i == selected_entry) wattron(window, A_REVERSE);
        mvwprintw(window, y+i, x, "%s", entry[i].c_str());
        if(i == selected_entry) wattroff(window, A_REVERSE);
    }

    wnoutrefresh(window);
}

void menuWindow::print_score()
{
    wclear(window);
    int maxx, x, y;
    getmaxyx(window, y, maxx);

    y = 1;

    std::string score_title("HIGH SCORES");
    x = (maxx - score_title.size() + 1)/2;
    mvwprintw(window, y, x, "%s", score_title.c_str());

    y += 2;

    // score of 0 is an empty entry, and scores are sorted so
    // if one is null, the following do to
    for(size_t i=0; i<SCORE_NUMBER && scores[i] > 0; i++) {
        x = maxx/2 - names[i].size();
        mvwprintw(window, y, x, "%s %i", names[i].c_str(), scores[i]);
        y++;
    }

    wrefresh(window);
    hang();
    wclear(window);
    wrefresh(window);
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
    case '\n':  // different codes enter may produce
    case '\r':
    case KEY_ENTER:
        return excecute_entry(selected_entry);
        break;
    case KEY_MOUSE:
        if(getmouse(&event) == OK)
        {
            if(wenclose(window, event.y, event.x))
            {
                wmouse_trafo(window, &event.y, &event.x, false);
                // go through entries testing if cursor is on them
                int x, y, maxx, maxy;
                getmaxyx(window, maxy, maxx);
                // test if cursor height is in the menu
                y = (maxy - ENTRY_MAX + 1)/2;
                if(y <= event.y && event.y < y + ENTRY_MAX) {
                    y = event.y - y;    // y is now the entry number
                    // test if cursor width is in the entry
                    x = (maxx - entry[y].size() + 1)/2;
                    if(x <= event.x && event.x < x + (int)entry[y].size()) {
                        // change current entry
                        selected_entry = y;
                        // select it if button is pressed
                        if(event.bstate & BUTTON1_PRESSED) {
                            return excecute_entry(selected_entry);
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
    // every action will leave the menu, so reset selection for next time
    selected_entry = 0;
    switch(entry)
    {
    case ENTRY_RESUME:
        return RETURN_RESUME;
        break;
    case ENTRY_RESTART:
        {
            mainGame tmp = main_window->getgame();
            tmp.restart();
            main_window->setgame(tmp);
        }
        return RETURN_RESUME;
        break;
    case ENTRY_SAVE:
        save( prompt("Save as :").c_str(), MESSAGE_ALL);
        break;
    case ENTRY_LOAD:
        load( prompt("Load file :").c_str(), MESSAGE_ALL );
        return RETURN_RESUME;
        break;
    case ENTRY_LAST_SAVE:
        load(AUTOSAVE_FILE, MESSAGE_ERROR);
        return RETURN_RESUME;
        break;
    case ENTRY_DEFAULT_SETTING:
        load(DEFAULT_BOARD, MESSAGE_ERROR);
        return RETURN_RESUME;
        break;
    case ENTRY_SCORES:
        print_score();
        break;
    case ENTRY_QUIT:
        return RETURN_QUIT;
        break;
    default:
        mlog << "Incorrect menu code" << std::endl;
        std::terminate();
        break;
    }
    return RETURN_NONE;
}


void menuWindow::add_score(int score)
{
    if(score > scores[SCORE_NUMBER-1]) {
        std::string name;
        std::string game_over = "GAME OVER";
        std::string score_disp = "score :";
        std::string prompt = "Enter name :";
        int maxx, maxy, x, y;
        getmaxyx(window, maxy, maxx);

        curs_set(1);

        for(;;) {
            wclear(window);
            x = (maxx - game_over.size())/2;
            y = maxy/2 - 1;
            mvwprintw(window, y, x, "%s", game_over.c_str());
            x = maxx/2 - score_disp.size();
            y = maxy/2;
            mvwprintw(window, y, x, "%s %i", score_disp.c_str(), score);
            x = maxx/2 - prompt.size();
            y = maxy/2 + 1;
            mvwprintw(window, y, x, "%s %s", prompt.c_str(), name.c_str());
            wrefresh(window);

            int ch = getch();
            if(ch == '\n' || ch == '\r' || ch == KEY_ENTER) {
                if(name.size() > 0) break;
            } else if(ch == '\b' || ch == 127 ||    // 127 is delete
                      ch == KEY_BACKSPACE || ch == KEY_DC) {
                if(name.size() > 0) name.pop_back();
            } else if('A' <= ch && ch <= 'Z') {     // name is caps only
                name += ch;
            } else if('a' <= ch && ch <= 'z') {
                name += ch - 'a' + 'A';
            }
        }

        curs_set(0);
        wclear(window);
        wrefresh(window);

        // insert in proper position
        size_t i=SCORE_NUMBER-1;
        while(i>0 && scores[i-1] < score) {
            scores[i] = scores[i-1];
            names[i] = names[i-1];
            i--;
        }
        scores[i] = score;
        names[i] = name;

        updatemax_score();
    }
}


std::string menuWindow::prompt(const std::string &prompt) const
{
    std::string name;

    // reactivate cursor visibility
    curs_set(1);

    for(;;) {
        wclear(window);
        mvwprintw(window, 1, 1, "%s %s", prompt.c_str(), name.c_str());
        wrefresh(window);

        int ch = getch();
        if(ch == 24) {  // cancel - ^X : return empty string
            name = "";
            break;
        } else if(ch == '\n' || ch == '\r' || ch == KEY_ENTER) {
            break;
        } else if(ch == '\b' || ch == 127 ||    // 127 is delete
                  ch == KEY_BACKSPACE || ch == KEY_DC) {
            if(name.size() > 0) name.pop_back();
        } else if(ch < 256) {   // only accept proper characters
            name += ch;
        }
    }

    // deactivate cursor
    curs_set(0);

    wclear(window);
    wrefresh(window);

    return name;
}



bool menuWindow::save(const char *file, messageLevel verbose) const
{
    // empty path is considered as cancel
    if(!file[0]) return false;

    bool success = false;
    bool wait = false;
    std::string success_msg = "Save successfull - press any key";
    std::string error_msg = "Save failed - press any key";
    int maxx, maxy;
    getmaxyx(window, maxy, maxx);

    if(verbose) {
        wclear(window);
    }

    std::ofstream output(file);
    if(!output.is_open()) {
        if(verbose) {
            mvwprintw(window, maxy/2, (maxx-error_msg.size())/2,
                      "%s", error_msg.c_str());
            wait = true;
        }
        mlog << "Unable to open file " << file
             << " for writing" << std::endl;
    } else {
        main_window->getgame().stream_write(output);
        success = true;
        if(verbose == MESSAGE_ALL) {
            mvwprintw(window, maxy/2, (maxx-success_msg.size())/2,
                      "%s", success_msg.c_str());
            wait = true;
        }
    }
    output.close();

    // wait after message
    if(wait)
    {
        wrefresh(window);
        hang();
        wclear(window);
        wrefresh(window);
    }

    return success;
}

bool menuWindow::load(const char *file, messageLevel verbose)
{
    // empty path is considered as cancel
    if(!file[0]) return false;

    bool success = false;
    bool wait = false;
    std::string success_msg = "Save successfully loaded - press any key";
    std::string error_open_msg = "Failed to open save - press any key";
    std::string error_read_msg = "Save invalid - press any key";
    int maxx, maxy;
    getmaxyx(window, maxy, maxx);

    if(verbose) {
        wclear(window);
    }

    std::ifstream input(file);
    if(!input.is_open()) {
        if(verbose) {
            mvwprintw(window, maxy/2, (maxx-error_open_msg.size())/2,
                      "%s", error_open_msg.c_str());
            wait = true;
        }
        mlog << "Unable to open file " << file
             << " for reading" << std::endl;
    } else {
        mainGame tmp;
        try {
            tmp = mainGame::stream_read(input);
            main_window->setgame(tmp);
            success = true;

            if(verbose == MESSAGE_ALL) {
                mvwprintw(window, maxy/2, (maxx-success_msg.size())/2,
                          "%s", success_msg.c_str());
                wait = true;
            }
        }
        catch(syntax_exception &excpt) {
            if(verbose) {
                std::string error(excpt.what());
                mvwprintw(window, maxy/2, (maxx-error.size())/2,
                          "%s", error.c_str());
                mvwprintw(window, maxy/2 + 1, (maxx-error_read_msg.size())/2,
                          "%s", error_read_msg.c_str());
                wait = true;
            }
            mlog << "In file " << file << " :\n"
                 << excpt.what() << std::endl;
        }
    }

    input.close();

    // wait after message
    if(wait)
    {
        wrefresh(window);
        hang();
        wclear(window);
        wrefresh(window);
    }

    return success;
}


bool menuWindow::save_score(const char *file) const
{
    std::ofstream output(file);

    if(!output.is_open()) {
        mlog << "Unable to open file " << file
             << " for writing" << std::endl;
        output.close();
        return false;
    } else {
        // score of 0 is an empty entry, and scores are sorted so
        // if one is null, the following do to
        for(size_t i=0; i<SCORE_NUMBER && scores[i] > 0; i++) {
            if(scores[i] > 0) {
                output << names[i] << " : " << scores[i] << std::endl;
            }
        }
        output.close();
        return true;
    }
}

bool menuWindow::load_score(const char *file)
{
    // load scores from file
    std::ifstream input(file);

    if(!input.is_open()) {
        mlog << "Unable to open file " << file
             << " for reading" << std::endl;
        input.close();
        return false;
    } else {
        std::string input_str, line;

        while(!input.eof()) {
            std::getline(input, line);
            input_str += line + '\n';
        }
        input.close();

        for(size_t i=0; i<SCORE_NUMBER && !blank_only(input_str); i++) {
            std::string name, score_str;
            size_t pos;
            int score;

            line = getline(input_str);
            clean_config_input(line);

            if(!get_key_value(line, name, score_str)) {
                mlog << "Invalid line in highscore file : " << line << std::endl;
                return false;
            }

            try {
                score = std::stoi(score_str, &pos);
            }
            catch(std::exception &e) {
                mlog << "Invalid line in highscore file : " << line << std::endl;
                return false;
            }
            if(!blank_only(score_str.substr(pos))) {
                mlog << "Invalid line in highscore file : " << line << std::endl;
                return false;
            }

            // insert in proper position
            if(score > scores[SCORE_NUMBER-1]) {
                size_t i=SCORE_NUMBER-1;
                while(i>0 && scores[i-1] < score) {
                    scores[i] = scores[i-1];
                    names[i] = names[i-1];
                    i--;
                }
                scores[i] = score;
                names[i] = name;
            }
        }

        updatemax_score();

        return true;
    }
}



void menuWindow::updatemax_score()
{
    if(scores[0] > main_window->getgame().getmax_score()) {
        mainGame tmp = main_window->getgame();
        tmp.setmax_score(scores[0]);
        main_window->changegame(tmp);
    }
}


void menuWindow::hang() const
{
    int ch;
    do {
        ch = getch();
    } while(ch == KEY_MOUSE);
}
