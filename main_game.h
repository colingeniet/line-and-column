/* !
 * @brief Main Game class
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * This class contain all information about the current game state.
 * It is somehow the 1010 game's engine !
 *
 */

#ifndef MAIN_GAME_H_INCLUDED
#define MAIN_GAME_H_INCLUDED

#include "board.h"      // used by mainGame
#include "form.h"       // used by mainGame

#include <cstddef>      // size_t
#include <vector>       // used by mainGame
#include <string>       // i/o
#include <iostream>     // stream i/o


#define N_FORMS 3


/*!
 * @brief Main game class
 *
 * This class keeps all informations about the current game state.
 * Those informations can be the number of shape propose, the shape's set used
 * in the current game, the shape apparition's probalitity, etc.
 *
 */
class mainGame
{
public:
    /*!
    * @brief form_set entries
    *
    * entries used in the set of forms
    */
    struct formEntry
    {
        Form form;              /*!< the form */
        unsigned int weight;    /*!< weight used in random selection */
        int color;              /*!< form color */
    };

    /*!
    * @brief Default constructor
    *
    * Create a game instance with default values.
    *
    */
    mainGame();

    /*!
    * @brief Default constructor
    *
    * Create a game instance.
    *
    * @param width : Number of squares in width
    * @param height : Number of squares in height
    *
    */
    mainGame(int width, int height);

    // accessors

    /*!
    * @brief Accessors for size
    *
    * @return Form size
    *
    */
    int getform_size() const;
    /*!
    * @brief Accessors for height
    *
    * @return Height
    *
    */
    int getheight() const ;
    /*!
    * @brief Accessors for width
    *
    * @return Width
    *
    */
    int getwidth() const;

    /*!
    * @brief Accessors for score
    *
    * @return Current score
    *
    */
    int getscore() const;
    /*!
    * @brief Accessors for combos
    *
    * @return Current combo
    *
    */
    int getcombo() const;
    /*!
    * @brief Accessors for best score (read)
    *
    * @return Hightest score
    *
    */
    int getmax_score() const;

    /*!
    * @brief Accessors for best score (write)
    *
    * @param n_score : New best score
    *
    */
    void setmax_score(int n_score);

    /*!
    * @brief Accessors for a specific form entry
    *
    * @return Form entry wanted in the form set
    *
    */
    formEntry getform(size_t) const;

    // coordonates are x, y
    /*!
    * @brief Accessors for specific form on the board
    *
    * @return Form wanted
    *
    */
    const int *operator[](int) const;


    /*!
    * @brief Move given form on the board
    *
    * Perform a move, return true if valid, false if not
    * Add one of the 3 selected forms at given coordonates
    * and perform all required action
    *
    * @param n : Form to move
    * @param x : X delta
    * @param y : Y delta
    *
    * @return True if move is valid false otherwise
    *
    */
    bool add_form(size_t n, int x, int y);

    /*!
    * @brief Check if there is move available
    *
    * For each form available, check if it can be placed on the board untill one of those can.
    *
    * @return True if a form can be placed, else otherwise
    *
    */
    bool move_available() const;


    /*!
    * @brief Add a form to the form set
    *
    * Add a new form which can appear in the game.
    *
    * @param form : Form to add
    * @param color : Form's color
    * @param weight : Weight (ie. probability to spawn)
    *
    */
    void add_form_to_set(const Form &form, int color, unsigned int weight=1);


    /*!
    * @brief Select 3 form for the available form list if needed
    *
    * Choose 3 forms from the form set if none are currently selected.
    * If force is true, always reselect.
    * If the form set is empty, reset all 3 forms to unselected.
    *
    * @param force : force new selection ?
    *
    */
    void random_select_forms(bool force=false);


    /*!
    * @brief Restart a game with the same form set
    *
    * Clean the board and redo random selection (keep the form set)
    *
    */
    void restart();

    /*!
    * @brief Restart a game from zero (without keeping anything) !
    *
    * Reset everything (include form set).
    *
    */
    void reset();

    /*!
    * @brief Game saving
    *
    * Save the game state in a string.
    *
    * @return The current game state inside a string
    *
    */
    std::string write() const;
    /*!
    * @brief Game loading
    *
    * Load a game from a string.
    *
    * @param str : game state to load - saved inside a string
    * @return Current game
    *
    */
    static mainGame read(const std::string& str);

    /*!
    * @brief Game saving (stream)
    *
    * Save the game state in a stream.
    *
    * @param stream : The stream where write the game
    *
    */
    void stream_write(std::ostream& stream) const;
    /*!
    * @brief Game loading (stream)
    *
    * Load a game throw a stream.
    *
    * @return Current game
    *
    */
    static mainGame stream_read(std::istream&);

private:
    Board board;                                /*!< The board */
    int form_size;                              /*!< Maximal size for forms */

    std::vector<formEntry> form_set;            /*!< Form set (each entry has a form, a weight and a color). see formEntry*/
    int total_weight;                           /*!< Sum of all individual weight for each form in the form set */

    size_t form[N_FORMS];                       /*!< Current forms available for the user */

    int score;                                  /*!< Current score */
    int combo;                                  /*!< Current combo state (score multiplier) */
    int max_score;                              /*!< Best score (record) */

    /*!
    * @brief Score updating
    *
    * Update score in fuction of number of lines and columns cleaned.
    *
    * @param lines : number of lines
    * @param columns : number of columns
    *
    */
    void update_score(int lines, int columns);
};


#endif // MAIN_GAME_H_INCLUDED
