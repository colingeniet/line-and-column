#include "main_game.h"

#include "config_load.h"

#include <cstdlib>
#include <iostream>
#include <exception>


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


// BAD : can select the same form twice
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

    if(form_set.size() > 0) {
        for(size_t i=0; i<N_FORMS; i++) {
            form[i] = rand() % form_set.size();
        }
    }
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


void mainGame::update_score(int lines, int columns)
{
    score +=  lines + columns;
    combo = lines + columns;
}



void mainGame::read(const std::string &str)
{
    std::string str_copy = str;
    std::string line, key, value;
    mainGame *game = NULL;
    int new_width=-1, new_height=-1, new_form_size=-1;

    while(str_copy.size() > 0)
    {
        line = getline(str_copy);
        clean_config_input(line);

        if(line.size() == 0) continue;

        if( !get_key_value(line, key, value) ) {
            std::cerr << "Invalid line in game configuration :\n"
                      << line << std::endl;
            std::terminate();
        } else if(key == "WIDTH") {
            if(new_width != -1) {
                std::cerr << "Redefinition of width in game \
configuration is illegal" << std::endl;
                std::terminate();
            }
            new_width = stoi(value);
            if(new_width < 0) {
                std::cerr << "Negative width value in game configuration !"
                          << std::endl;
                std::terminate();
            }
        } else if(key == "HEIGHT") {
            if(new_height != -1) {
                std::cerr << "Redefinition of height in game \
configuration is illegal" << std::endl;
                std::terminate();
            }
            new_height = stoi(value);
            if(new_height < 0) {
                std::cerr << "Negative height value in game configuration !"
                          << std::endl;
                std::terminate();
            }
        } else if(key == "FORM_SIZE") {
            if(new_form_size != -1) {
                std::cerr << "Redefinition of form size in game \
configuration is illegal" << std::endl;
                std::terminate();
            }
            new_form_size = stoi(value);
            if(new_form_size < 0) {
                std::cerr << "Negative form size value in game configuration !"
                          << std::endl;
                std::terminate();
            }
        } else {
            // any other entry is illegal if game is not created
            if(game == NULL) {
                std::cerr << "Game configuration require WIDTH, HEIGHT and \
FORM_SIZE befor anything else." << std::endl;
                std::terminate();
            }

            if(key == "FORM") {
                int color = word_to_color(value);
                if(color == COLOR_BLACK) {
                    std::cerr << "Forms can not be defined with color black"
                              << std::endl;
                    std::terminate();
                }
                Form new_form;
                new_form.read(getblock(str_copy));
                game->add_form_to_set(new_form, color);
            } else if(key == "BOARD") {
                game->board.read(getblock(str_copy));
            } else if(key == "SELECTED_FORM") {
                size_t index, form_index;
                index = stoul(getword(value))-1;
                form_index = stoul(getword(value))-1;
                game->form[index] = form_index;
            } else if(key == "SCORE") {
                game->score = stoi(value);
            } else if(key == "COMBO") {
                game->combo = stoi(value);
            } else {
                std::cerr << "Invalid key in game configuration : "
                          << key << std::endl;
                std::terminate();
            }
        }

        // create game if required info is given
        if(game == NULL && new_width >= 0 &&
           new_height >= 0 && new_form_size >= 0) {
            game = new mainGame(new_width, new_height, new_form_size);
        }
    }

    if(game == NULL) {
        std::cerr << "Height, width and form size definition is required \
in game configuration" << std::endl;
        std::terminate();
    } else {
        *this = *game;
        delete game;
    }
}

void mainGame::stream_write(std::ostream &os) const
{
    os << write();
}

void mainGame::stream_read(std::istream &is)
{
    std::string input, line;
    while(std::getline(is, line))
    {
        input += line.substr(0, line.find('#')) + "\n";
    }
    read(input);
}

std::ostream& operator<<(std::ostream &os, const mainGame &game)
{
    game.stream_write(os);
    return os;
}

std::istream& operator>>(std::istream &is, mainGame &game)
{
    game.stream_read(is);
    return is;
}

