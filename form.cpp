#include "form.h"

#include "config_load.h"    // config file i/o

#include <exception>        // std::exception


Form::Form() :
    size(0),
    capacity(FORM_DEFAULT_SIZE),
    squares(new Point[capacity])
{
    boxmin.x = 0;
    boxmin.y = 0;
    boxmax.x = 0;
    boxmax.y = 0;
}

Form::Form(const Form& f) :
    size(f.size),
    capacity(f.size),
    squares(new Point[capacity]),
    boxmin(f.boxmin),
    boxmax(f.boxmax)
{
    for(size_t i=0; i<size; i++) {
        squares[i] = f.squares[i];
    }
}


Form::~Form()
{
    delete[] squares;
}


Form& Form::operator=(const Form& f)
{
    if(&f != this) {
        if(capacity < f.size) {
            delete[] squares;
            capacity = f.size;
            squares = new Point[capacity];
        }
        size = f.size;

        for(size_t i=0; i<size; i++) {
            squares[i] = f.squares[i];
        }
        boxmin = f.boxmin;
        boxmax = f.boxmax;
    }
    return *this;
}



void Form::clear()
{
    size = 0;
    boxmin.x = 0;
    boxmin.y = 0;
    boxmax.x = 0;
    boxmax.y = 0;
}

void Form::add(int x, int y) {
    if(size == capacity) {
        resize();
    }
    squares[size].x = x;
    squares[size].y = y;
    size++;

    if(size == 1) {
        boxmin.x = boxmax.x = x;
        boxmin.y = boxmax.y = y;
    } else {
        if(x < boxmin.x) boxmin.x = x;
        if(x > boxmax.x) boxmax.x = x;
        if(y < boxmin.y) boxmin.y = y;
        if(y > boxmax.y) boxmax.y = y;
    }
}


size_t Form::getsize() const
{
    return size;
}

Form::Point Form::operator[](size_t n) const
{
    return squares[n];
}

Form::Point Form::getboxmin() const
{
    return boxmin;
}

Form::Point Form::getboxmax() const
{
    return boxmax;
}


std::string Form::write() const
{
    std::string str;
    for(size_t i=0; i<size; i++) {
        str += std::to_string(squares[i].x) + " " +
               std::to_string(squares[i].y) + "\n";
    }
    return str;
}

void Form::read(const std::string &str)
{
    std::string str_copy = str;
    std::string word;
    size_t pos;
    int x, y;
    clean_config_input(str_copy);
    while(str_copy.size() > 0) {
        word = getword(str_copy);
        try {
            x = std::stoi(word, &pos);
        }
        catch(std::exception &e) {
            syntax_exception excpt("invalid input : " + word);
            throw excpt;
        }
        if(!blank_only(word.substr(pos))) {
            syntax_exception excpt("invalid input : " + word);
            throw excpt;
        }
        word = getword(str_copy);
        try {
            y = std::stoi(word, &pos);
        }
        catch(std::exception &e) {
            syntax_exception excpt("invalid input : " + word);
            throw excpt;
        }
        if(!blank_only(word.substr(pos))) {
            syntax_exception excpt("invalid input : " + word);
            throw excpt;
        }
        add(x, y);
    }
}


void Form::resize()
{
    capacity = capacity == 0 ? FORM_DEFAULT_SIZE : capacity*2;
    Point *tmp = new Point[capacity];

    for(size_t i=0; i<size; i++) {
        tmp[i] = squares[i];
    }

    delete[] squares;
    squares = tmp;
}
