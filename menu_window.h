/* !
 * @brief Menu window
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Menu window - the menu GUI class
 * This class contain all informations of every menu in the game
 * like start menu, pause menu, death menu, etc.
 *
 * Because copying ncurses windows does not make sense,
 * this class is not designed to be copied.
 *
 */

#ifndef INCLUDEGUI_H_INCLUDED
// this file shall never be included, includeGUI.h must be used instead
#include "includeGUI.h"

#else

#ifndef MENU_WINDOW_H_INCLUDED
#define MENU_WINDOW_H_INCLUDED


#define DEFAULT_BOARD "default_board"
#define AUTOSAVE_FILE "autosave"
#define SCORE_FILE ".highscores"


#include "main_game.h"      // used by menuWindow
#include "config_load.h"    // used for highscore file

#include <ncurses.h>        // used by menuWindow

#include <string>           // used by menuWindow
#include <cstddef>          // size_t


#define SCORE_NUMBER 5


 /*!
  * @brief Menu window class
  *
  * This class is used to display differents menus like the death menu,
  * the victory menu, the main menu, etc. So it saves scores and handle
  * interaction with the user who can select a entry.
  *
  */
class menuWindow
{
public:
    /*!
     * @brief Different message level
     *
     * Macro for different type level of message.
     *
     */
    enum messageLevel
    {
        MESSAGE_NONE,       /*!< No message. */
        MESSAGE_ERROR,      /*!< Error message. */
        MESSAGE_ALL,        /*!< Highest priority message. */
        MESSAGE_MAX         /*!< Number of available messages. */
    };

    /*!
    * @brief Constructor
    *
    * Create a windows attached to a main window.
    *
    * @param _main : Main window
    *
    */
    menuWindow(mainWindow*);
    /*!
    * @brief Destructor
    *
    */
    ~menuWindow();

    /*!
    * @brief Constructor by copying
    *
    * Copying makes no sense : ncurses windows can not be copied
    *
    */
    menuWindow(const menuWindow&) = delete;
    /*!
    * @brief Overload of affectation operator
    *
    * Copying makes no sense : ncurses windows can not be copied
    *
    */
    menuWindow& operator=(const menuWindow&) = delete;

    /*!
    * @brief Print the menu on the screen
    *
    */
    void print();
    /*!
    * @brief Print scores on the screen
    *
    */
    void print_score();

    /*!
    * @brief Menu's inputs
    *
    * Treate inputs and act accordingly.
    *
    * @param ch : User input
    *
    */
    bool input(int);



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
    * @brief Save menu window
    *
    * @param file : File where save
    * @param verbose : Printing control
    *
    * @return True if successfull
    *
    */
    bool save(const char *file, messageLevel verbose) const;
    /*!
    * @brief Load menu window
    *
    * @param file : File where load
    * @param verbose : Printing control
    *
    * @return True if successfull
    *
    */
    bool load(const char *file, messageLevel verbose);

    /*!
    * @brief Save scores
    *
    * @param file : File where save
    *
    * @return True if successfull
    *
    */
    bool save_score(const char*) const;
    /*!
    * @brief Load scores
    *
    * @param file : File where load
    *
    * @return True if successfull
    *
    */
    bool load_score(const char*);

    // update maxscore in mainGame according to the scores in menuWindow
    void updatemax_score();

private:
    WINDOW *window;                     /*!< NCurse's window */

    mainWindow *main_window;            /*!< Main window */

    /*!
     * @brief Different entries
     *
     * Macro for different type entries.
     *
     */
    enum menuEntry
    {
        ENTRY_RESUME,               /*!< Game resume. */
        ENTRY_RESTART,              /*!< Game restart. */
        ENTRY_SAVE,                 /*!< Save the game. */
        ENTRY_LOAD,                 /*!< Load a game. */
        ENTRY_LAST_SAVE,            /*!< Load last game saved. */
        ENTRY_DEFAULT_SETTING,      /*!< Load default setting. */
        ENTRY_SCORES,               /*!< Display score. */
        ENTRY_QUIT,                 /*!< Quit the game. */
        ENTRY_MAX                   /*!< Number of entries available. */
    };

    std::string entry[ENTRY_MAX];       /*!< Entries array */

    size_t selected_entry;              /*!< Selected entry */

    std::string names[SCORE_NUMBER];    /*!< Hightscores names */
    int scores[SCORE_NUMBER];           /*!< Hightscores */

    /*!
    * @brief Entry excecution
    *
    * Apply entry consequenceses.
    * Perform actions corresponding to an entry and return the appropriate code.
    *
    * @param entry : Entry selected
    *
    * @return True if the game continue, false if quit has been selected
    *
    */
    bool excecute_entry(int entry);

    /*!
    * @brief Entry prompt
    *
    * Prompt entry to user.
    *
    * @param prompt : Entry prompt
    *
    * @return Entry validated
    *
    */
    std::string prompt(const std::string& prompt) const;

    /*!
    * @brief Wait for an input
    *
    */

    void hang() const;
};


#endif // MENU_WINDOW_H_INCLUDED

#endif // INCLUDEGUI_H_INCLUDED
