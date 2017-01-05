#ifndef INCLUDEGUI_H_INCLUDED
#define INCLUDEGUI_H_INCLUDED

/* due to cross declaration and inter-dependencie (I can't believe I just wrote that),
 * classes mainWindow, menuWindow and gameWindow shall always be included using
 * this header, and not the separate main_window.h ... */


class mainWindow;
class menuWindow;
class gameWindow;

#include "game_window.h"
#include "menu_window.h"
// mainWindow uses some nested enums from menuWindow and must therefore be
// included after menu_window.h
#include "main_window.h"


#endif // INCLUDEGUI_H_INCLUDED
