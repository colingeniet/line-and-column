/* !
 * @brief Board's class definition
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 */

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED


#include "color.h"  // for color definitions
#include "form.h"   // add / collide

#include <cstddef>  // size_t
#include <string>   // i/o


/*!
 * @brief Board class
 *
 * This class defines the main 1010 board. It mostly is the array of squares
 * with all method required to manipulate it
 *
 */
class Board
{
public:
    /*!
     * @brief Constructor
     *
     * Constructor for Board
     *
     * Set size then create array and initialize it empty.
     *
     * @param _width : Board's width (number of possinble squares)
     * @param _height : Board's height (number of possible squares)
     *
     */
    Board(int _width, int _height);

    /*!
     * @brief Constructor by copy
     *
     * Constructor by copy of Baord class.
     * Allow to build a board from another already existing.
     * Set size then create the array witch is initialized with copied array's values.
     *
     * @param _board : Board to copy
     *
     */
    Board(const Board& _board);

    /*!
     * @brief Destructor
     *
     * Baord of Board instance (needed by presence of the dynamic allocation -2 dim. array- in attribute).
     * Free memory ligne by ligne then free main column.
     *
     */
    ~Board();

    /*!
     * @brief Overload of affectation operator
     *
     * Affectation operator for Board
     * Allow to fully change the board from another board.
     * Free memory ligne by ligne then free main column.
     * Set size then create the array witch is initialized with copied array's values.
     *
     * @param _board Board to be copied
     *
     * @return A board instance
     *
     */
    Board& operator=(const Board& _board);

    /*!
     * @brief Change a square's color
     *
     * Changes the colors of a square whose coordinates are passed as parameters.
     *
     * @param x : Square's abscissia
     * @param y : Squarer's ordinate
     * @param color : New color
     *
     */
    void setSquare(int x, int y, int color);

    /*!
     * @brief Put a shape on the board
     *
     * Browse all squares used by the new form the add thoses squares one by one to the board.
     *
     * @param form : New form to add
     * @param x : Abscissia where place the new form
     * @param y : Ordinate where place the new form
     * @param color : Color wished for this form
     *
     */
    void addForm(const Form& form, int x, int y, int color);

    /*!
     * @brief Check if a form can be place on the board
     *
     * Get bounding box of the shape and check if it can be placed at coordinates passed as parameter.
     * If the answer is yes then it need a more precise checking so it check squres one by one.
     *
     * @param form : Shape to verifie
     * @param x : Abscissia where check collision
     * @param y : Ordinate where check collision
     *
     * @return True if the shape can be place.
     *
     */
    bool formCollide(const Form& form, int x, int y) const;

    /*!
     * @brief Clean filled lignes and columns.
     *
     * Browe every lign and column and mark whoses are filled.
     * When it's done, delete every marked line.
     *
     * @param _ligne : Number of deleted lines
     * @param _column : Number of deleted columns
     *
     */
    void clean(int& _line, int& _column);

    // accessors

    /*!
     * @brief Access operator
     *
     * @param n : Square's index
     *
     * @return A pointer on the square
     *
     */
    // coordonates are x, y
    const int *operator[](int n) const;
    /*!
     * @brief Accessor in reading of the width.
     *
     * @return The board's width
     *
     */
    int getwidth() const;
    /*!
     * @brief Accessor in reading of the height
     *
     * @return The board's heigtht
     *
     */
    int getheight() const;

    // I/O

    /*!
     * @brief Write board
     *
     * @return A string witch represente the board
     *
     */
    std::string write() const;
    /*!
     * @brief Read a configuration form a string
     *
     * Check validity of the string passed and modify the configuration.
     *
     */
    void read(const std::string& str);

private:
    int width, height;  /*!< Board's size */
    int **board;        /*!< Array to represente the board */
};

#endif // BOARD_H_INCLUDED
