#ifndef CONFIG_LOAD_H_INCLUDED
#define CONFIG_LOAD_H_INCLUDED


#include <string>


/* standard config input cleaning function :
 * remove blank (space, tab and newline) at the begining and the end,
 * replace any squence of blank by a single space,
 * and delete anything after 'comment' if any */
void clean_config_input(std::string &input, char comment = '#');

/* get a word at the begining of a string and remove it from the string
 * a word is from begining to the first blank. blank is removed as well
 * it is designed for use on string cleaned with clean_config_input */
std::string getword(std::string &input);

/* look for the sequence " : " in a string. If found, set key to the first part
 * (before : ) and value to the second (after : ) and return true.
 * If not, return false.
 * Only the first " : " is considered */
bool get_key_value(const std::string &input,
                   std::string &key,  std::string &value);

/* convert a string to all upper(lower = false) / lower (lower = true) case.
 * default is upper */
void set_case(std::string &str, bool lower = false);

/* convert a color name to its corresponding code, case insensitive
 * color names are black, red, green, yellow, blue, magenta, cyan, white */
int word_to_color(const std::string&);

/* convert a color code to its corresponding name (upper case) */
std::string color_to_word(int);


#endif // CONFIG_LOAD_H_INCLUDED
