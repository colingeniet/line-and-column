#ifndef MAIN_GAME_H_INCLUDED
#define MAIN_GAME_H_INCLUDED

#include "board.h"
#include "form.h"

#include <cstddef>
#include <vector>


#define N_FORMS 3


/* main game class, keep all information about game state */
class mainGame
{
public:
    /* parameters : width, height (main board), max form size */
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

    // choose 3 differents forms from the forms set
    void random_select_forms();


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
