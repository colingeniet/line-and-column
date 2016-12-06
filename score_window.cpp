#include "score_window.h"

#include "config_load.h"    // file i/o

#include <cstddef>          // size_t
#include <iostream>         // errors
#include <fstream>          // file i/o


scoreWindow::scoreWindow() :
    window(newwin(0,0,0,0))
{
    wattrset(window, A_BOLD);

    for(size_t i=0; i<SCORE_NUMBER; i++) {
        scores[i] = 0;
    }
}

scoreWindow::~scoreWindow()
{
    if(window) delwin(window);
}


void scoreWindow::print()
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

    wnoutrefresh(window);
}


void scoreWindow::add_score(int score)
{
    if(score > scores[SCORE_NUMBER-1]) {
        std::string name;
        std::string game_over = "GAME OVER";
        std::string score_disp = "score :";
        std::string prompt = "Enter name :";
        int maxx, maxy, x, y;
        getmaxyx(window, maxy, maxx);

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
    }
}


bool scoreWindow::save(const char *file) const
{
    std::ofstream output(file);

    if(!output.is_open()) {
        std::cerr << "Unable to open file " << file
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

bool scoreWindow::load(const char *file)
{
    // load scores from file
    std::ifstream input(file);
    if(!input.is_open()) {
        std::cerr << "Unable to open file " << file
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
            int score;
            line = getline(input_str);
            clean_config_input(line);
            get_key_value(line, name, score_str);

            score = std::stoi(score_str);

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

        return true;
    }
}
