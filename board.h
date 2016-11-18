#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#include "color.h"
#include "form.h"

/* Tihs class defines the main 1010 board. It mostly is the array of squares
 * with all method required to manipulate it */
class Board
{
public:
    // width / height
    Board(size_t, size_t);
    Board(const Board&);

    ~Board();

    Board& operator=(const Board&);

    // last parameter is the color
    void setSquare(size_t, size_t, int);
    // write a form on the board at any coordonates (including outside)
    void addForm(const Form&, int, int, int);

    // true if the form at these coordonate would collide with existing squares
    bool formCollide(const Form&, int, int) const;

    // delete full lines / columns, return number of each deleted
    void clean(int&, int&);

    // accessors
    // coordonates are x, y
    const int *operator[](size_t) const;
    size_t getwidth() const;
    size_t getheight() const;

private:
    size_t width, height;
    int **board;
};

#endif // BOARD_H_INCLUDED
