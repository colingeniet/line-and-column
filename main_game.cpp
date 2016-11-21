#include "main_game.h"

#include <cstdlib>


mainGame::mainGame(int _width, int _height, int _form_size) :
    board(_width, _height),
    form_size(_form_size),
    score(0),
    combo(0)
{
    for(size_t i=0; i<N_FORMS; i++) form[i] = (size_t)-1;
}



int mainGame::getform_size() const {
    return form_size;
}

int mainGame::getwidth() const {
    return board.getwidth();
}

int mainGame::getheight() const {
    return board.getheight();
}

int mainGame::getscore() const {
    return score;
}

int mainGame::getcombo() const {
    return combo;
}

const int* mainGame::operator[](int n) const {
    return board[n];
}

Form mainGame::getform(size_t n) const {
    return form[n] == (size_t) -1 ? Form() : form_set[form[n]];
}

int mainGame::getform_color(size_t n) const {
    return form[n] == (size_t) -1 ? COLOR_NONE : form_color[form[n]];
}


bool mainGame::add_form(size_t n, int x, int y)
{
    // check validity
    if(form[n] == (size_t)-1) return false;
    // check that it can be added
    if(board.formCollide(form_set[form[n]], x, y)) return false;

    // add
    board.addForm(form_set[form[n]], x, y, form_color[form[n]]);
    // clean updating score
    int lines=0, columns=0;
    board.clean(lines, columns);
    update_score(lines, columns);

    // remove the added form
    form[n] = (size_t) -1;
    // select new ones if needed
    bool empty = true;
    for(size_t i=0; i<N_FORMS && empty; i++) {
        if(form[i] != (size_t)-1) empty = false;
    }
    if(empty) {
        random_select_forms();
    }

    return true;
}

bool mainGame::move_available() const
{
    for(size_t i=0; i<N_FORMS; i++)
    {
        if(form[i] != (size_t) -1)
        {
            for(int x=0; x<board.getwidth(); x++) {
                for(int y=0; y<board.getheight(); y++) {
                    if( !board.formCollide(form_set[form[i]], x, y) ) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool mainGame::add_form_to_set(const Form &form, int color)
{
    // (x+1)/2 and (x/2) always sum up to x (unlike (x/2)*2)
    if(form.getboxmax().x > (form_size+1)/2 ||
       form.getboxmax().y > (form_size+1)/2 ||
       form.getboxmin().x < -(form_size/2) ||
       form.getboxmin().y < -(form_size/2) ) {
        return false;
    }

    form_set.push_back(form);
    form_color.push_back(color);
    return true;
}


// BAD : can select the same form twice
void mainGame::random_select_forms()
{
    if(form_set.size() > 0) {
        for(size_t i=0; i<N_FORMS; i++) {
            form[i] = rand() % form_set.size();
        }
    }
}


void mainGame::update_score(int lines, int columns)
{
    score +=  lines + columns;
    combo = lines + columns;
}

