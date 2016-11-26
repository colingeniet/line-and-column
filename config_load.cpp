#include "config_load.h"


void clean_config_input(std::string &input, char comment)
{
    // delete comment
    input = input.substr(0, input.find(comment));

    // begining / end blanks
    size_t start, end;
    start = input.find_first_not_of(" \n\t");
    end = input.find_last_not_of(" \n\t");
    if(start == std::string::npos) {
        input = std::string();
        return;
    } else {
        input = input.substr(start, end-start+1);
    }

    // cleaning
    start = end = 0;
    start = input.find_first_of(" \n\t", start+1);
    while(start != std::string::npos)
    {
        end = input.find_first_not_of(" \n\t", start);
        input = input.substr(0, start) + " "
                + input.substr(end, std::string::npos);
        start = input.find_first_of(" \n\t", start+1);
    }
}
