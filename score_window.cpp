#include "score_window.h"

#include "config_load.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <exception>


scoreWindow::scoreWindow() :
    window(newwin(0,0,0,0))
{
    for(size_t i=0; i<SCORE_NUMBER; i++) {
        scores[i] = 0;
    }

    // load scores from file
    std::ifstream input(SCORE_FILE);
    if(!input.is_open()) {
        std::cerr << "Unable to open file " << SCORE_FILE
                  << " for reading - ignored" << std::endl;
        input.close();
    } else {
        std::string input_str, line;
        while(!input.eof()) {
            std::getline(input, line);
            input_str += line + '\n';
        }
        input.close();

        for(size_t i=0; i<SCORE_NUMBER && !blank_only(input_str); i++) {
            std::string name, score;
            line = getline(input_str);
            clean_config_input(line);
            get_key_value(line, name, score);

            names[i] = name;
            scores[i] = stoi(score);
        }
    }

    // never trust the file ! sort yourself
    for(size_t i=0; i<SCORE_NUMBER; i++) {
        int score = scores[i];
        std::string name = names[i];
        size_t j = i;
        while(j > 0 && score > scores[j-1]) {
            scores[j] = scores[j-1];
            names[j] = names[j-1];
            j--;
        }
        scores[j] = score;
        names[j] = name;
    }
}

scoreWindow::~scoreWindow()
{
    // write scores to file
    std::ofstream output(SCORE_FILE);

    if(!output.is_open()) {
        std::cerr << "Unable to open file " << SCORE_FILE
                  << " for writing - ignored" << std::endl;
        output.close();
    } else {
        for(size_t i=0; i<SCORE_NUMBER; i++) {
            if(scores[i] > 0) {
                output << names[i] << " : " << scores[i] << std::endl;
            }
        }
    }

    delwin(window);
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
        std::string prompt = "Enter name :";
        int maxx, x;
        getmaxyx(window, x, maxx);

        for(;;) {
            wclear(window);
            x = maxx/2 - prompt.size();
            mvwprintw(window, 1, x, "%s %s", prompt.c_str(), name.c_str());
            wnoutrefresh(window);
            doupdate();

            int ch = getch();
            if(ch == '\n' && name.size() > 0) {
                break;
            } else if('a' <= ch && ch <= 'z') {
                name += ch - 'a' + 'A';
            }
        }

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