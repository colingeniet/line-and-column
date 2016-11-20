#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

#include <cstddef>


struct Point
{
    int x, y;
};


/* This class stores forms made of squares and keeps it's boundary box,
 * ie the smallest rectangle that contains the form */

#define FORM_DEFAULT_SIZE 5

class Form
{
public:
    Form();
    Form(const Form&);

    ~Form();

    Form& operator= (const Form&);

    void clear();

    // add a square
    void add(Point);
    void add(int, int);

    // accessors
    size_t getsize() const;
    Point operator[](size_t) const;
    Point getboxmin() const;
    Point getboxmax() const;

private:
    size_t size, capacity;
    Point *squares;
    Point boxmin, boxmax;

    void resize();
};

#endif // FORM_H_INCLUDED
