#ifndef FORM_H_INCLUDED
#define FORM_H_INCLUDED

// No point (pun intended) in making it a class
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
class Form
{
public:
    Form();
    Form(const Form&);
    Form(const Point *const, size_t);

    ~Form();

    Form& operator= (const Form&);

    // recalculate the boundary box.
    void updatebox();

    // add a square (if it does not already exist)
    void add(const Point&);
    void add(size_t, size_t);

    // remove a square (if it exists)
    void remove(const Point&);
    void remove(size_t, size_t);

    // accessors
    const Point* getsquares() const;
    size_t getsize() const;

private:
    size_t array_size, n_squares;
    Point *squares;
    Point boxmin, boxmax;

    // find a square, return it's index, -1 if it does not exist
    size_t find(const Point&);
    size_t find();

    void resize();
};

#endif // FORM_H_INCLUDED
