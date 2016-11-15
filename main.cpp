#include "main_window.h"
#include "color.h"

int main(int argc, char** argv)
{
    initscr();
    cbreak();
    // refresh of is required after initialization or windows won't display
    refresh();
    if(has_colors())
    {
        start_color();
        init_color_pairs();
    }

    mainWindow win(10, 10, 5);
    win.print();

    getch();

    endwin();

    return 0;
}
