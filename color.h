#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

#include <ncurses.h>

/* standard terminal colors (black, red, green, yellow, blue, magenta, cyan
 * and white) are defined by ncurses as COLOR_'color'.
 * black is defined as 0 so it can be used as false, other being true
 * COLOR_NONE is defined as black to be more explicit for boolean use */
#define COLOR_NONE COLOR_BLACK

// color pairs
enum colorPair
{
    /* color pair 0 is reserved by ncurses as default color pair
     * it is initialized by start_colors() and should not be modified */
    DEFAULT_PAIR,
    BLACK_RED,
    BLACK_GREEN,
    BLACK_YELLOW,
    BLACK_BLUE,
    BLACK_MAGENTA,
    BLACK_CYAN,
    BLACK_WHITE,
    RED_BLACK,
    BLUE_BLACK,
    YELLOW_BLACK,
    MAX_PAIR
};

void init_color_pairs();

/* return a color pair attribute with color as background, black as foreground
 * use black and white if colors are unavailable */
int get_attr_color(int);

#endif // COLOR_H_INCLUDED
