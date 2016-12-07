#include "config_load.h"

#include "color.h"          // color definitions
#include "global_log.h"     // errors


syntax_exception::syntax_exception() :
    msg("Invalid syntax")
{}

syntax_exception::syntax_exception(const std::string &detail, size_t line) :
    msg((line == (size_t)-1 ? "" : "line " + std::to_string(line) + " : ")
        + detail)
{}

const char* syntax_exception::what() const  throw() {
    return msg.c_str();
}

size_t syntax_exception::getline() const throw() {
    return line;
}


bool blank_only(const std::string &str)
{
    return str.find_first_not_of(" \t\n") == std::string::npos;
}

size_t count_occurences(const std::string &input, const std::string &ch) {
    size_t cpt = 0;
    for(size_t pos = 0;; cpt++) {
        pos = input.find_first_of(ch, pos);
        if(pos == std::string::npos) break;
        pos++;
    }
    return cpt;
}

size_t count_occurences(const std::string &input, const char *ch) {
    size_t cpt = 0;
    for(size_t pos = 0;; cpt++) {
        pos = input.find_first_of(ch, pos);
        if(pos == std::string::npos) break;
        pos++;
    }
    return cpt;
}

size_t count_occurences(const std::string &input, const char *ch, size_t n) {
    size_t cpt = 0;
    for(size_t pos = 0;; cpt++) {
        pos = input.find_first_of(ch, pos, n);
        if(pos == std::string::npos) break;
        pos++;
    }
    return cpt;
}

size_t count_occurences(const std::string &input, char ch) {
    size_t cpt = 0;
    for(size_t pos = 0;; cpt++) {
        pos = input.find_first_of(ch, pos);
        if(pos == std::string::npos) break;
        pos++;
    }
    return cpt;
}


void clean_config_input(std::string &input)
{
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


std::string getword(std::string &input)
{
    size_t blank = input.find_first_of(" \t\n");
    std::string word = input.substr(0, blank);

    if(blank == std::string::npos)
        input = std::string();
    else
        input = input.substr(blank+1, std::string::npos);

    return word;
}

std::string getline(std::string &input)
{
    size_t blank = input.find_first_of("\n");
    std::string line = input.substr(0, blank);

    if(blank == std::string::npos)
        input = std::string();
    else
        input = input.substr(blank+1, std::string::npos);

    return line;
}

std::string getblock(std::string &input, size_t *line)
{
    std::string block;

    // find delimiters
    size_t start = input.find('{');
    if(start == std::string::npos) {
        syntax_exception excpt("missing {");
        throw excpt;
        return std::string();
    }
    size_t end = input.find('}', start);
    if(start == std::string::npos) {
        syntax_exception excpt("missing }");
        throw excpt;
        return std::string();
    }

    // check for blank only before {
    // block is temporarly assigned the input before the actual block
    block = input.substr(0, start);
    if(!blank_only(block)) {
        syntax_exception excpt("unexcepted input before {");
        throw excpt;
        return std::string();
    }

    if(line) *line = count_occurences(input.substr(0, end+1), '\n');
    block = input.substr(start+1, end-start-1);
    input = input.substr(end+1);
    return block;
}


bool get_key_value(const std::string &input,
                   std::string &key, std::string &value)
{
    size_t delimiter = input.find(" :");

    // special case : at the end of input, second space is optional
    if(delimiter == input.size()-2) {
        key = input.substr(0, delimiter);
        value = std::string();
        return true;
    } else {
        delimiter = input.find(" : ");

        if(delimiter == std::string::npos) return false;

        key = input.substr(0, delimiter);
        value = input.substr(delimiter+3, std::string::npos);
        return true;
    }
}


void set_case(std::string &str, bool lower)
{
    if(lower)
    {
        for(size_t i=0; i<str.size(); i++) {
            if('A' <= str[i] && str[i] <= 'Z')
                str[i] += 'a' - 'A';
        }
    }
    else
    {
        for(size_t i=0; i<str.size(); i++) {
            if('a' <= str[i] && str[i] <= 'z')
                str[i] += 'A' - 'a';
        }
    }
}



int word_to_color(const std::string& input)
{
    if(input == "BLACK")         return COLOR_BLACK;
    else if(input == "RED")      return COLOR_RED;
    else if(input == "GREEN")    return COLOR_GREEN;
    else if(input == "YELLOW")   return COLOR_YELLOW;
    else if(input == "BLUE")     return COLOR_BLUE;
    else if(input == "MAGENTA")  return COLOR_MAGENTA;
    else if(input == "CYAN")     return COLOR_CYAN;
    else if(input == "WHITE")    return COLOR_WHITE;
    else {
        syntax_exception excpt("invalid color name : " + input);
        throw excpt;
        return -1;
    }
}


std::string color_to_word(int color)
{
    switch(color)
    {
    case COLOR_BLACK:
        return "BLACK";
        break;
    case COLOR_RED:
        return "RED";
        break;
    case COLOR_GREEN:
        return "GREEN";
        break;
    case COLOR_YELLOW:
        return "YELLOW";
        break;
    case COLOR_BLUE:
        return "BLUE";
        break;
    case COLOR_MAGENTA:
        return "MAGENTA";
        break;
    case COLOR_CYAN:
        return "CYAN";
        break;
    case COLOR_WHITE:
        return "WHITE";
        break;
    default:
        mlog << "invalid color code : " << color << std::endl;
        return "";
        break;
    }
}
