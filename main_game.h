#ifndef MAIN_GAME_H_INCLUDED
#define MAIN_GAME_H_INCLUDED

#include "board.h"
#include "form.h"

#include <vector>


#define N_FORMS 3


/* main game class, keep all information about game state */
class mainGame
{
public:
    /* parameters : width, height (main board), max form size */
    mainGame(size_t, size_t, size_t);

    // accessors
    size_t getform_size() const;
    size_t getheight() const ;
    size_t getwidth() const;

    int getscore() const;
    int getcombo() const;

    Form getform(size_t) const;
    int getform_color(size_t) const;

    // coordonates are x, y
    const int *operator[](size_t) const;


    /* perform a move, return true if valid, false if not
     * add one of the 3 selected forms at given coordonates
     * and perform all required action */
    bool add_form(size_t, int, int);

    bool move_available() const;

    // add a form to the set of forms used
    bool add_form_to_set(const Form &form, int color = COLOR_WHITE);

    // choose 3 differents forms from the forms set
    void random_select_forms();


private:
    Board board;

    size_t form_size;
    std::vector<Form> form_set;
    std::vector<int> form_color;
    size_t form[N_FORMS];

    void update_score(int, int);

    int score, combo;
};


#endif // MAIN_GAME_H_INCLUDED
