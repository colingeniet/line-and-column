#ifndef SCORE_WINDOW_H_INCLUDED
#define SCORE_WINDOW_H_INCLUDED

#include <ncurses.h>

#include <string>

#define SCORE_NUMBER 5
#define SCORE_FILE ".highscores"

class scoreWindow
{
public:
    scoreWindow();
    ~scoreWindow();

    void print();
    // add new score with name prompt (only if it is better than current scores)
    void add_score(int);

private:
    WINDOW *window;
    std::string names[SCORE_NUMBER];
    int scores[SCORE_NUMBER];
};

#endif // SCORE_WINDOW_H_INCLUDED
