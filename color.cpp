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
