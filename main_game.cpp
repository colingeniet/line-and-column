#include "main_game.h"

#include <cstdlib>

mainGame::mainGame(size_t _width, size_t _height, size_t _form_size) :
    board(_width, _height),
    form_size(_form_size),
    form1( (size_t) -1 ),
    form2( (size_t) -1 ),
    form3( (size_t) -1 ),
    score(0),
    combo(0)
{}



size_t mainGame::getform_size() const {
    return form_size;
}

size_t mainGame::getwidth() const {
    return board.getwidth();
}

size_t mainGame::getheight() const {
    return board.getheight();
}

const int* mainGame::operator[](size_t n) const {
    return board[n];
}

Form mainGame::getform1() const {
    return form1 == (size_t) -1 ? Form() : form_set[form1];
}

Form mainGame::getform2() const {
    return form2 == (size_t) -1 ? Form() : form_set[form2];
}

Form mainGame::getform3() const {
    return form3 == (size_t) -1 ? Form() : form_set[form3];
}


bool mainGame::add_form(uint8_t n, int x, int y)
{
    // n designate one of the 3 selected forms, so get the index in form_set
    size_t i;
    switch(n) {
    case 1:
        i =form1;
        break;
    case 2:
        i = form2;
        break;
    case 3:
        i = form3;
        break;
    default:
        return false;
    }
    // check validity
    if(i == (size_t)-1) return false;
    // check that it can be added
    if(board.formCollide(form_set[i], x, y)) return false;

    // add
    board.addForm(form_set[i], x, y, COLOR_WHITE);  // ajouter couleur
    // clean updating score
    int lines=0, columns=0;
    board.clean(lines, columns);
    update_score(lines, columns);

    // remove the added form
    switch(n) {
    case 1:
        form1 = (size_t) -1;
        break;
    case 2:
        form2 = (size_t) -1;
        break;
    case 3:
        form3 = (size_t) -1;
        break;
    }
    if(form1 == (size_t) -1 &&
       form2 == (size_t) -1 &&
       form3 == (size_t) -1) {
        random_select_forms();
    }
    return true;
}

bool mainGame::move_available() const
{
    if(form1 != (size_t) -1)
    {
        for(size_t x=0; x<board.getwidth(); x++) {
            for(size_t y=0; y<board.getheight(); y++) {
                if( !board.formCollide(form_set[form1], x, y) ) {
                    return true;
                }
            }
        }
    }

    if(form2 != (size_t) -1)
    {
        for(size_t x=0; x<board.getwidth(); x++) {
            for(size_t y=0; y<board.getheight(); y++) {
                if( !board.formCollide(form_set[form2], x, y) ) {
                    return true;
                }
            }
        }
    }

    if(form3 != (size_t) -1)
    {
        for(size_t x=0; x<board.getwidth(); x++) {
            for(size_t y=0; y<board.getheight(); y++) {
                if( !board.formCollide(form_set[form3], x, y) ) {
                    return true;
                }
            }
        }
    }

    return false;
}

bool mainGame::add_form_to_set(const Form &F)
{
    form_set.push_back(F);   // ajouter test de taille ici, a voir
    return true;
}


void mainGame::random_select_forms()
{
    form1 = random() % form_set.size();
    do {
        form2 = random() % form_set.size();
    } while(form2 == form1);
    do {
        form3 = random() % form_set.size();
    } while(form3 == form1 || form3 == form2);
}



void mainGame::update_score(int lines, int columns)
{
    score +=  lines + columns;
    combo = lines + columns;
}

