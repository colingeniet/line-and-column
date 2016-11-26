#ifndef CONFIG_LOAD_H_INCLUDED
#define CONFIG_LOAD_H_INCLUDED


#include <iostream>
#include <fstream>
#include <string>

/* standard config input cleaning function :
 * remove blank (space, tab and newline) at the begining and the end,
 * replace any squence of blank by a single space,
 * and delete anything after 'comment' if any */
void clean_config_input(std::string &input, char comment = '#');


#endif // CONFIG_LOAD_H_INCLUDED
