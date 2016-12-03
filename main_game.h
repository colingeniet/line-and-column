#ifndef MAIN_GAME_H_INCLUDED
#define MAIN_GAME_H_INCLUDED

#include "board.h"
#include "form.h"

#include <cstddef>
#include <vector>
#include <string>
#include <iostream>


#define N_FORMS 3


/* main game class, keep all information about game state */
class mainGame
{
public:
    /* parameters : width, height (main board), max form size */
    mainGame();
    mainGame(int, int, int);

    // accessors
    int getform_size() const;
    int getheight() const ;
    int getwidth() const;

    int getscore() const;
    int getcombo() const;

    Form getform(size_t) const;
    int getform_color(size_t) const;

    // coordonates are x, y
    const int *operator[](int) const;


    /* perform a move, return true if valid, false if not
     * add one of the 3 selected forms at given coordonates
     * and perform all required action */
    bool add_form(size_t, int, int);

    bool move_available() const;

    // add a form to the set of forms used
    bool add_form_to_set(const Form&, int);

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
    std::vector<Form> form_set;
    std::vector<int> form_color;
    size_t form[N_FORMS];

    void update_score(int, int);

    int score, combo;
};


#endif // MAIN_GAME_H_INCLUDED
