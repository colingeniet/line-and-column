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

    void setSquare(size_t, size_t, Color);
    void addForm(const Form&, size_t, size_t, Color);

    bool formCollide(const Form&, size_t, size_t) const;

    // delete full lines / columns (empty is black)
    void clean();

    // temporaire, juste pour voir rapidement le contenu (couleurs inutiles)
    void print() const;

private:
    size_t height, width;
    Color **board;
};

#endif // BOARD_H_INCLUDED
