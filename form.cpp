#include "form.h"


Form::Form() :
    array_size(FORM_DEFAULT_SIZE),
    n_squares(0),
    squares(new Point[array_size]) {}

Form::Form(const Form& f) :
    array_size(f.n_squares),
    n_squares(f.n_squares),
    squares(new Point[array_size]),
    boxmin(f.boxmin),
    boxmax(f.boxmax)
{
    for(size_t i=0; i<n_squares; i++) {
        squares[i] = f.squares[i];
    }
}

Form::Form(const Point* T, size_t n) :
    array_size(n),
    n_squares(n),
    squares(new Point[array_size])
{
    for(size_t i=0; i<n_squares; i++) {
        squares[i] = T[i];
    }
    updatebox();
}


Form::~Form()
{
    delete[] squares;
}


Form& Form::operator=(const Form& f)
{
    if(&f != this) {
        if(array_size < f.n_squares) {
            delete[] squares;
            array_size = f.n_squares;
            squares = new Point[array_size];
        }
        n_squares = f.n_squares;

        for(size_t i=0; i<n_squares; i++) {
            squares[i] = f.squares[i];
        }
        boxmin = f.boxmin;
        boxmax = f.boxmax;
    }
    return *this;
}



void Form::updatebox()
{
    if(n_squares == 0) {
        boxmin.x = 0; boxmin.y = -1;
        boxmax.x = 0; boxmax.y = -1;
    } else {
        boxmin.x = squares[0].x, boxmax.x = squares[0].x;
        boxmin.y = squares[0].y, boxmax.y = squares[0].y;

        for(size_t i=1; i<n_squares; i++) {
            if(squares[i].x < boxmin.x) boxmin.x = squares[i].x;
            if(squares[i].x > boxmax.x) boxmax.x = squares[i].x;
            if(squares[i].y < boxmin.y) boxmin.y = squares[i].y;
            if(squares[i].y > boxmax.y) boxmax.y = squares[i].y;
        }
    }
}


void Form::add(Point p)
{
    add(p.x, p.y);
}

void Form::add(int x, int y) {
    if(find(x, y) == (size_t) -1) {
        if(n_squares == array_size) {
            resize();
        }
        squares[n_squares].x = x;
        squares[n_squares].y = y;
        n_squares++;

        if(n_squares == 1) {
            boxmin.x = boxmax.x = x;
            boxmin.y = boxmax.y = y;
        } else {
            if(x < boxmin.x) boxmin.x = x;
            if(x > boxmax.x) boxmax.x = x;
            if(y < boxmin.y) boxmin.y = y;
            if(y > boxmax.y) boxmax.y = y;
        }
    }
}


void Form::remove(Point p)
{
    remove(p.x, p.y);
}

void Form::remove(int x, int y)
{
    size_t i = find(x, y);
    if(i != (size_t) -1) {
        squares[i] = squares[--n_squares];
        updatebox();
    }
}


size_t Form::getsize() const
{
    return n_squares;
}

const Point& Form::operator[](size_t n) const
{
    return squares[n];
}

Point Form::getboxmin() const
{
    return boxmin;
}

Point Form::getboxmax() const
{
    return boxmax;
}



size_t Form::find(int x, int y) const
{
    for(size_t i=0; i<n_squares; i++) {
        if(squares[i].x == x && squares[i].y == y) {
            return i;
        }
    }
    return (size_t) -1;
}

void Form::resize()
{
    array_size = array_size == 0 ? FORM_DEFAULT_SIZE : array_size*2;
    Point *tmp = new Point[array_size];

    for(size_t i=0; i<n_squares; i++) {
        tmp[i] = squares[i];
    }

    delete[] squares;
    squares = tmp;
}
