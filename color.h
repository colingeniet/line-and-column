/* !
 * @brief Colors's pair enumeration
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Standard terminal colors (black, red, green, yellow, blue, magenta, cyan and white) are defined by ncurses as COLOR_'color'.
 * Black is defined as 0 so it can be used as false, other being true.
 * COLOR_NONE is defined as black to be more explicit for boolean use.
 *
 */

#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <ncurses.h>


#define COLOR_NONE COLOR_BLACK

/*!
 * @brief Colors pairs
 *
 * Create all macro required by ncurse to describe colors.
 * Every square's color in the grid is define by a pair with blanck caracter writed on a colord backfont.
 * Color pair 0 is reserved by ncurses as default color pair
 * it is initialized by start_colors() and should not be modified.
 *
 */
enum colorPair
{
  DEFAULT_PAIR,      /*!< Default pair. */
    BLACK_RED,         /*!< Red square. */
    BLACK_GREEN,       /*!< Green square. */
    BLACK_YELLOW,      /*!< Yellow square. */
    BLACK_BLUE,        /*!< Blue square. */
    BLACK_MAGENTA,     /*!< Magenta square. */
    BLACK_CYAN,        /*!< Cyan square. */
    BLACK_WHITE,       /*!< White square. */
    RED_BLACK,         /*!< Red font. */
    BLUE_BLACK,        /*!< Blue font. */
    YELLOW_BLACK,      /*!< Yellow font. */
    MAX_PAIR           /*!< Number of pairs defined. */
};

/*!
 * @brief required by ncurse
 */
void init_color_pairs();

int get_attr_color(int);

#endif // COLOR_H_INCLUDED
