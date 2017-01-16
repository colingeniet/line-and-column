/* !
 * @brief Include Graphique User Interface
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Due to cross declaration and inter-dependencie,
 * classes mainWindow, menuWindow and gameWindow
 * shall always be included using this header,
 * and not the separate main_window.h ...
 *
 * For more informations about thoses classes,
 * please refer to their respective documentation.
 *
 */

#ifndef INCLUDEGUI_H_INCLUDED
#define INCLUDEGUI_H_INCLUDED


/* forward declaration of the GUI classes */
class mainWindow;
class menuWindow;
class gameWindow;

#include "game_window.h"
#include "menu_window.h"
// mainWindow uses some nested enums from menuWindow and must therefore be
// included after menu_window.h
#include "main_window.h"


#endif // INCLUDEGUI_H_INCLUDED
