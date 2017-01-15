/* !
 * @brief Main window
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Main window - the main GUI class that interact
 * with all other specifics GUI's classes.
 * This class handle interaction between all GUI parts.
 * Because copying ncurses windows does not make sense,
 * this class is not designed to be copied.
 *
 */

#ifndef INCLUDEGUI_H_INCLUDED
// this file shall never be included, includeGUI.h must be used instead
#include "includeGUI.h"

#else

#ifndef MAIN_WINDOW_H_INCLUDED
#define MAIN_WINDOW_H_INCLUDED

#include "main_game.h"


 /*!
  * @brief Main window class
  *
  * This class contains a game class instance which is displayed
  * but also handle interaction between all GUI parts.
  *
  */
class mainWindow
{
public:
    /*!
     * @brief Different windows
     *
     * Macro for different type of window.
     * Indicate which window is it.
     *
     */
    enum Window
    {
        WINDOW_GAME,        /*!< Game window. */
        WINDOW_MENU,        /*!< Menu window. */
        WINDOW_MAX          /*!< Number of windows defined. */
    };

    /*!
    * @brief Default constructor
    *
    * Create the main windows which has attached differents other windows.
    *
    */
    mainWindow();
    /*!
    * @brief Constructor from a file
    *
    * Create the main windows which has attached differents other windows.
    * Load those windows and itself from a file.
    *
    * @param file : File to load
    *
    */
    mainWindow(const char *file);
    /*!
    * @brief Constructor from a game
    *
    * Create the main windows which has attached differents other windows.
    * Create the game window with an existing game.
    *
    * @param new_game : Game to load
    *
    */
    mainWindow(const mainGame& new_game);

    /*!
    * @brief Destructor
    *
    * Kill the main window.
    *
    */
    ~mainWindow();

    /*!
    * @brief Constructor by copying
    *
    * copying makes no sense : ncurses windows can not be copied
    *
    */
    mainWindow(const mainWindow&) = delete;

    /*!
    * @brief Affectation Operator overloading
    *
    * Copying makes no sense : ncurses windows can not be copied
    *
    */
    mainWindow& operator=(const mainWindow&) = delete;

    /*!
    * @brief Change game used in the window
    *
    * Change the mainGame.
    *
    * @param new_game : Game affect instead of current
    *
    */
    void setgame(const mainGame& new_game);

    /*!
    * @brief Change game used in the window
    *
    * Unlike setgame(), it is required that board dimension are not changed
    * it does not reinitialize everything.
    *
    * @param new_game : Game to load
    *
    * @return True if the gmae as been correctly changed, else otherwise
    *
    */
    bool changegame(const mainGame& new_game);

    /*!
    * @brief Get the game
    *
    * @return The game
    *
    */
    const mainGame& getgame() const;


    /*!
    * @brief Apply user decision
    *
    * Take a getch() input.
    *
    * @param ch : User input
    *
    * @return False if the game shall quit
    *
    */
    bool input(int ch);

    /*!
    * @brief Display the window
    *
    * Print the current active window.
    *
    */
    void print();

    /*!
    * @brief Change active window
    *
    */
    void setwindow(Window);


    /*!
    * @brief Add a new highscore
    *
    * Prompt a name to save user's score in the wall of fame.
    *
    * @param score : Score
    *
    * @return True if the score is an highscore
    *
    */
    bool add_score(int);

    /*!
    * @brief Display scores
    *
    */
    void print_score();

    /*!
    * @brief Save main window
    *
    * @param file : File where save
    * @param verbose : Printing control
    *
    * @return True if successfull
    *
    */
    bool save(const char *file, menuWindow::messageLevel verbose) const;
    /*!
    * @brief Load main window
    *
    * @param file : File where load
    * @param verbose : Printing control
    *
    * @return True if successfull
    *
    */
    bool load(const char *file, menuWindow::messageLevel verbose);

    /*!
    * @brief Save scores
    *
    * @param file : File where save
    *
    * @return True if successfull
    *
    */
    bool save_scores(const char *file = SCORE_FILE) const;
    /*!
    * @brief Load scores
    *
    * @param file : File where load
    *
    * @return True if successfull
    *
    */
    bool load_scores(const char *file = SCORE_FILE);

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
    bool add_form(size_t n, int x , int y);

private:
    mainGame *game;             /*!< Game instance */

    Window current_window;      /*!< Display window */

    gameWindow *game_window;    /*!< Game window */
    menuWindow *menu_window;    /*!< Menu window */

    /*!
    * @brief Game initialisation
    *
    * Perform required action to make the game playable after
    * modification via setgame.
    *
    */
    void initialize_game();
};

#endif // MAIN_WINDOW_H_INCLUDED

#endif // INCLUDEGUI_H_INCLUDED
