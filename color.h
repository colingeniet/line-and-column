#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <ncurses.h>

/* standard terminal colors (black, red, green, yellow, blue, magenta, cyan
 * and white) are defined by ncurses as COLOR_'color'.
 * black is defined as 0 so it can be used as false, other being true
 * COLOR_NONE is defined as black to be more explicit for boolean use */
#define COLOR_NONE COLOR_BLACK

// color pairs
#define BLACK_RED 1
#define BLACK_GREEN 2
#define BLACK_YELLOW 3
#define BLACK_BLUE 4
#define BLACK_MAGENTA 5
#define BLACK_CYAN 6
#define BLACK_WHITE 7

#define RED_BLACK 9
#define BLUE_BLACK 12

void init_color_pairs();

#endif // COLOR_H_INCLUDED
