#include "main_game.h"

#include "config_load.h"    // config file read

#include <cstdlib>          // rand()
#include <iostream>         // errors
#include <exception>        // terminate


mainGame::mainGame() :
    board(0, 0),
    form_size(0),
    score(0),
    combo(0)
{
    for(size_t i=0; i<N_FORMS; i++) form[i] = (size_t)-1;
}

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
    score += form_set[form[n]].getsize();
    // clean updating score
    int lines=0, columns=0;
    board.clean(lines, columns);
    update_score(lines, columns);

    // remove the added form
    form[n] = (size_t) -1;
    // select new ones if needed
    random_select_forms(false);

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


void mainGame::random_select_forms(bool force)
{
    // test if forms must be selected
    if(!force) {
        bool empty = true;
        for(size_t i=0; i<N_FORMS && empty; i++) {
            if(form[i] != (size_t)-1) empty = false;
        }
        if(!empty) return;
    }

    if(form_set.size() == 0) {
        // empty set
        for(size_t i=0; i<N_FORMS; i++) {
            form[i] = (size_t) -1;
        }
    } else if(form_set.size() < N_FORMS) {
        // set is too small to have no identic selected forms
        for(size_t i=0; i<N_FORMS; i++) {
            form[i] = rand() % form_set.size();
        }
    } else {
        // set is big enough : never select the same form twice

        /* algorithm : form_sorted contain the same values as form, sorted.
         * each form slot is selected smaller than  max - i, which is exactly
         * the number of value it can take (as 'i' are already taken).
         * the inner loop transform  n -> the nth not taken value  while
         * inserting it. */
        size_t form_sorted[N_FORMS];
        for(size_t i=0; i<N_FORMS; i++) {
            form[i] = rand() % (form_set.size() - i);
            size_t j=i;
            while(j>0 && form[i] >= form_sorted[j-1]) {
                form_sorted[j] = form_sorted[j-1];
                form[i]++;
                j--;
            }
            form_sorted[j] = form[i];
        }
    }
}

void mainGame::restart()
{
    board = Board(board.getwidth(), board.getheight());
    random_select_forms(true);
    score = 0; combo = 0;
}

void mainGame::reset()
{
    board = Board(board.getwidth(), board.getheight());
    form_set.clear();
    form_color.clear();
    random_select_forms(true);
    score = 0; combo = 0;
}

void mainGame::update_score(int lines, int columns)
{
    score +=  board.getwidth()*lines + board.getheight()*columns;
    combo = lines + columns;
}



std::string mainGame::write() const
{
    std::string str;
    // header
    str += "WIDTH : " + std::to_string(board.getwidth()) + "\n";
    str += "HEIGHT : " + std::to_string(board.getheight()) + "\n";
    str += "FORM_SIZE : " + std::to_string(form_size) + "\n";
    str += "\n\n";

    // form set
    for(size_t i=0; i<form_set.size(); i++) {
        str += "FORM : " + color_to_word(form_color[i]) + "\n{\n";
        str += form_set[i].write();
        str += "}\n\n";
    }

    str += "\n";

    // save
    for(size_t i=0; i<N_FORMS; i++) {
        if(form[i] != (size_t)-1) {
            str += "SELECTED_FORM : " + std::to_string(i+1)
                    + " " + std::to_string(form[i]+1) + "\n";
        }
    }

    str += "\n\n";

    str += "BOARD :\n{\n" + board.write() + "}\n\n\n";
    str += "SCORE : " + std::to_string(score) + "\n";
    str += "COMBO : " + std::to_string(combo) + "\n";

    return str;
}

mainGame mainGame::read(const std::string &str)
{
    std::string str_copy = str;
    std::string line, key, value;
    mainGame game;
    bool initialized = false;
    int new_width=-1, new_height=-1, new_form_size=-1;

    while(str_copy.size() > 0)
    {
        line = getline(str_copy);
        clean_config_input(line);

        if(line.size() == 0) continue;

        if( !get_key_value(line, key, value) ) {
            syntax_exception excpt("invalid line in save file");
            throw excpt;
        } else if(key == "WIDTH") {
            if(new_width != -1) {
                syntax_exception excpt("illegal redefinition of width");
                throw excpt;
            }
            new_width = std::stoi(value);
            if(new_width < 0) {
                syntax_exception excpt("negative width value");
                throw excpt;
            }
        } else if(key == "HEIGHT") {
            if(new_height != -1) {
                syntax_exception excpt("illegal redefinition of height");
                throw excpt;
            }
            new_height = std::stoi(value);
            if(new_height < 0) {
                syntax_exception excpt("negative height value");
                throw excpt;
            }
        } else if(key == "FORM_SIZE") {
            if(new_form_size != -1) {
                syntax_exception excpt("illegal redefinition of form size");
                throw excpt;
            }
            new_form_size = std::stoi(value);
            if(new_form_size < 0) {
                syntax_exception excpt("negative form_size value");
                throw excpt;
            }
        } else {
            // any other entry is illegal if game is not initialized
            if(!initialized) {
                syntax_exception excpt("width, height and form size must be defined before any other input");
                throw excpt;
            }

            if(key == "FORM") {
                int color = word_to_color(value);
                if(color == COLOR_BLACK) {
                    syntax_exception excpt("Forms can not be defined with color black");
                    throw excpt;
                }
                Form new_form;
                new_form.read(getblock(str_copy));
                game.add_form_to_set(new_form, color);
            } else if(key == "BOARD") {
                game.board.read(getblock(str_copy));
            } else if(key == "SELECTED_FORM") {
                size_t index, form_index;
                index = std::stoul(getword(value))-1;
                form_index = std::stoul(getword(value))-1;
                game.form[index] = form_index;
            } else if(key == "SCORE") {
                game.score = std::stoi(value);
            } else if(key == "COMBO") {
                game.combo = std::stoi(value);
            } else {
                syntax_exception excpt("invalid key name");
                throw excpt;
            }
        }

        // create game if required info is given
        if(!initialized && new_width >= 0 &&
           new_height >= 0 && new_form_size >= 0) {
            game = mainGame(new_width, new_height, new_form_size);
            initialized = true;
        }
    }

    if(!initialized) {
        syntax_exception excpt("width, height and form size must be defined");
        throw excpt;
    }

    return game;
}

void mainGame::stream_write(std::ostream &os) const
{
    os << write();
}

mainGame mainGame::stream_read(std::istream &is)
{
    std::string input, line;
    while(std::getline(is, line))
    {
        input += line.substr(0, line.find('#')) + "\n";
    }
    return read(input);
}

