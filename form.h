#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

#include <cstddef>


struct Point
{
    int x, y;
};


/* This class stores forms made of squares and keeps it's boundary box,
 * ie the smallest rectangle that contains the form */
/* Implementation a faire : /!\ tableau dynamique, faire constructeurs /
 * destructeur / operator= correctement
 * Toujours s'assurer que boxmin et boxmax sont mis a jour
 */
#define FORM_DEFAULT_SIZE 5

class Form
{
public:
    Form();
    Form(const Form&);
    Form(const Point*, size_t);

    ~Form();

    Form& operator= (const Form&);

    // recalculate the boundary box.
    void updatebox();

    // add a square (if it does not already exist)
    void add(Point);
    void add(int, int);

    // remove a square (if it exists)
    void remove(Point);
    void remove(int, int);

    // accessors
    size_t getsize() const;
    const Point& operator[](size_t) const;
    Point getboxmin() const;
    Point getboxmax() const;

private:
    size_t array_size, n_squares;
    Point *squares;
    Point boxmin, boxmax;

    // find a square, return its index, -1 if it does not exist
    size_t find(int, int) const;

    void resize();
};

#endif // FORM_H_INCLUDED
