/* !
 * @brief Game Window class
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Main game display
 * As its name suggests, this class contains the game window, no need to say more...
 * Because copying ncurses windows does not make sense,
 * this class is not designed to be copied.
 *
 */

#ifndef INCLUDEGUI_H_INCLUDED
// this file shall never be included, includeGUI.h must be used instead
#include "includeGUI.h"

#else

#ifndef GAME_WINDOW_H_INCLUDED
#define GAME_WINDOW_H_INCLUDED


#include "main_game.h"      // used by gameWindow
#include "color.h"          // used for printing
#include "history.h"        // game history

#include <ncurses.h>        // used by gameWindow

#include <cstddef>          // size_t



 /*!
  * @brief Main game window
  *
  * Considers forms as squares's group with a bounding box.
  * This handle interactions with the user like cursor's position, selected form, etc.
  *
  */
class gameWindow
{
public:

    /*!
    * @brief Constructor
    *
    * Create a windows attached to a main window.
    *
    * @param _main : Main window
    *
    */
    gameWindow(mainWindow* _main);

    /*!
    * @brief Destructor
    *
    */
    ~gameWindow();

    /*!
    * @brief Constructor by copying
    *
    * Copying makes no sense : ncurses windows can not be copied
    *
    */
    gameWindow(const gameWindow&) = delete;

    /*!
    * @brief Overload of affectation operator
    *
    * Copying makes no sense : ncurses windows can not be copied
    *
    */
    gameWindow& operator=(const gameWindow&) = delete;

    /*!
    * @brief Applie dimension changes
    *
    * Recreate all windows
    *
    */
    void update_dimensions();

    /*!
    * @brief Print the game to the screen
    *
    * Display each window.
    *
    */
    void print();

    /*!
    * @brief Game's inputs
    *
    * Treate inputs and act accordingly.
    *
    * @param ch : User input
    *
    */
    void input(int ch);

    // clear history and make it ready for use
    void initialize_history();


private:
    WINDOW *borderWindow;                               /*!< Boarder's window */
    WINDOW *boardWindow;                                /*!< Board's window */
    WINDOW *scoreWindow;                                /*!< Score's window */
    WINDOW *formWindow[N_FORMS];                        /*!< Available forms's window */

    mainWindow *main_window;                            /*!< Main window */

    int cursor_x;                                       /*!< Cursor X's position */
    int cursor_y;                                       /*!< Cursor Y's position */
    size_t selected_form;                               /*!< Selected form number */

    History<mainGame> history;                          /*!< Game history */

    /*!
    * @brief Windows initialisation
    *
    * Create all WINDOWS objects (size calculated).
    *
    */
    void init_windows();

    /*!
    * @brief Cursor repositioning
    *
    * Put the cursor back in the bounds.
    *
    */
    void cursor_bounds();

    // subwindows print functions

    /*!
    * @brief Score display
    *
    * Print the score informations (current, best, etc.).
    *
    */
    void print_score();

    /*!
    * @brief Board display
    *
    * Print the board to the screen.
    *
    */
    void print_board();

    /*!
    * @brief Form display
    *
    * Print a specific form.
    *
    * @param n : Form to print
    *
    */
    void print_form(size_t n);
};


#endif // GAME_WINDOW_H_INCLUDED

#endif // INCLUDEGUI_H_INCLUDED
