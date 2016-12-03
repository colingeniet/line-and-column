#ifndef MENU_WINDOW_H_INCLUDED
#define MENU_WINDOW_H_INCLUDED

#include <ncurses.h>

#include <string>
#include <cstddef>


/* Because copying ncurses windows does not make sense, this class
 * is not designed to be copied. */
class menuWindow
{
public:
    // input() return status
    enum returnValue
    {
        RETURN_NONE,
        RETURN_RESUME,
        RETURN_RESTART,
        RETURN_QUIT,
        RETURN_MAX
    };

    menuWindow();
    ~menuWindow();

    void print();

    returnValue input(int);


private:
    WINDOW *window;

    enum menuEntry
    {
        ENTRY_RESUME,
        ENTRY_RESTART,
        ENTRY_QUIT,
        ENTRY_MAX
    };
    std::string entry[ENTRY_MAX];

    size_t selected_entry;
};

#endif // MENU_WINDOW_H_INCLUDED
