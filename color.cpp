#include "color.h"

void init_color_pairs()
{
    init_pair(BLACK_RED, COLOR_BLACK, COLOR_RED);
    init_pair(BLACK_GREEN, COLOR_BLACK, COLOR_GREEN);
    init_pair(BLACK_YELLOW, COLOR_BLACK, COLOR_YELLOW);
    init_pair(BLACK_BLUE, COLOR_BLACK, COLOR_BLUE);
    init_pair(BLACK_MAGENTA, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(BLACK_CYAN, COLOR_BLACK, COLOR_CYAN);
    init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);

    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
}


int get_attr_color(int color)
{
    // if colors are disabled, COLOR_BLACK -> black, everything else -> white
    if( !has_colors() )
    {
        return color ? A_REVERSE : A_NORMAL;
    }
    else
    {
        switch(color)
        {
        case COLOR_BLACK:
            return A_NORMAL;
            break;
        case COLOR_RED:
            return COLOR_PAIR(BLACK_RED);
            break;
        case COLOR_GREEN:
            return COLOR_PAIR(BLACK_GREEN);
            break;
        case COLOR_YELLOW:
            return COLOR_PAIR(BLACK_YELLOW);
            break;
        case COLOR_BLUE:
            return COLOR_PAIR(BLACK_BLUE);
            break;
        case COLOR_MAGENTA:
            return COLOR_PAIR(BLACK_MAGENTA);
            break;
        case COLOR_CYAN:
            return COLOR_PAIR(BLACK_CYAN);
            break;
        case COLOR_WHITE:
            return COLOR_PAIR(BLACK_WHITE);
            break;
        default:
            return A_NORMAL;
            break;
        }
    }
}
