#ifndef MAIN_GAME_H_INCLUDED
#define MAIN_GAME_H_INCLUDED

#include "board.h"
#include "form.h"

#include <vector>


/* main game class, keep all information about game state */
class mainGame
{
public:
    /* parameters : width, height (main board), max form size */
    mainGame(size_t, size_t, size_t);
    ~mainGame();

    size_t form_size();
    size_t height();
    size_t width();

    const int *operator[](size_t) const;
    const Form* form1() const;
    const Form* form2() const;
    const Form* form3() const;

private:
    Board board;

    size_t form_size;
    std::vector<Form> forms;
    size_t form1, form2, form3;

    int score, combo;
};


#endif // MAIN_GAME_H_INCLUDED
