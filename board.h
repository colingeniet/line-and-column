#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#include "color.h"
#include "form.h"

/* Tihs class defines the main 1010 board. It mostly is the array of squares
 * with all method required to manipulate it */
/* Implementation a faire : /!\ C'est un tableau dynamique -> faire les
 * constructeurs / destructeurs / operator= correctement
 */
class Board
{
public:
    Board(size_t, size_t);
    Board(const Board&);

    ~Board();

    Board& operator=(const Board&);

    void setSquare(size_t, size_t, int);
    void addForm(const Form&, int, int, int);

    bool formCollide(const Form&, int, int) const;

    // delete full lines / columns
    void clean(int&, int&);

    const int *operator[](size_t) const;
    size_t height() const;
    size_t width() const;

private:
    size_t height, width;
    int **board;
};

#endif // BOARD_H_INCLUDED
