#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED


/* Terminal colors enumeration
 * It is likely to be used in various unrelated classes, so I define it globally
 */
enum Color
{
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_MAX
};

/* generally, no color will be black. As it is defined as 0 in the enum, boolean
 * tests will work. This defines a more natural name for this purpose
 */
#define COLOR_NONE COLOR_BLACK


#endif // COLOR_H_INCLUDED
