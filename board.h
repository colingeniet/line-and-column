#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#include "color.h"  // for color definitions
#include "form.h"   // add / collide

#include <cstddef>  // size_t
#include <string>   // i/o


/* This class defines the main 1010 board. It mostly is the array of squares
 * with all method required to manipulate it */
class Board
{
public:
    // width / height
    Board(int, int);
    Board(const Board&);

    ~Board();

    Board& operator=(const Board&);

    // last parameter is the color
    void setSquare(int, int, int);
    // write a form on the board at any coordonates (including outside)
    void addForm(const Form&, int, int, int);

    // true if the form at these coordonate would collide with existing squares
    bool formCollide(const Form&, int, int) const;

    // delete full lines / columns, return number of each deleted
    void clean(int&, int&);

    // accessors
    // coordonates are x, y
    const int *operator[](int) const;
    int getwidth() const;
    int getheight() const;

    // I/O
    std::string write() const;
    void read(const std::string&);

private:
    int width, height;
    int **board;
};

#endif // BOARD_H_INCLUDED
