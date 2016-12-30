#ifndef MAIN_GAME_H_INCLUDED
#define MAIN_GAME_H_INCLUDED

#include "board.h"      // used by mainGame
#include "form.h"       // used by mainGame

#include <cstddef>      // size_t
#include <vector>       // used by mainGame
#include <string>       // i/o
#include <iostream>     // stream i/o


#define N_FORMS 3


/* main game class, keep all information about game state */
class mainGame
{
public:
    struct formEntry
    {
        Form form;
        unsigned int weight;
        int color;
    };


    /* parameters : width, height (main board) */
    mainGame();
    mainGame(int, int);

    // accessors
    int getform_size() const;
    int getheight() const ;
    int getwidth() const;

    int getscore() const;
    int getcombo() const;
    int getmax_score() const;

    void setmax_score(int);

    formEntry getform(size_t) const;

    // coordonates are x, y
    const int *operator[](int) const;


    /* perform a move, return true if valid, false if not
     * add one of the 3 selected forms at given coordonates
     * and perform all required action */
    bool add_form(size_t, int, int);

    bool move_available() const;

    // add a form to the set of forms used
    void add_form_to_set(const Form &form, int color, unsigned int weight=1);

    /* choose 3 forms from the form set if none are currently selected
     * if force is true, always reselect. If the form set is empty, reset
     * all 3 forms to unselected */
    void random_select_forms(bool force=false);


    // clean the board and redo random selection (keep the form set)
    void restart();
    // reset everything
    void reset();


    std::string write() const;
    static mainGame read(const std::string&);

    void stream_write(std::ostream&) const;
    static mainGame stream_read(std::istream&);

private:
    Board board;

    int form_size;

    std::vector<formEntry> form_set;
    int total_weight;

    size_t form[N_FORMS];

    int score, combo, max_score;

    void update_score(int, int);
};


#endif // MAIN_GAME_H_INCLUDED
