#ifndef CONFIG_LOAD_H_INCLUDED
#define CONFIG_LOAD_H_INCLUDED


#include <cstddef>      // size_t
#include <string>
#include <exception>    // std::exception


class syntax_exception : public std::exception {
public:
    syntax_exception();
    syntax_exception(const std::string &detail, size_t line = (size_t)-1);

    const char* what() const throw();
    size_t getline() const;

private:
    std::string msg;
    size_t line;
};


/* return true if string contain only spaces, tabs and newlines */
bool blank_only(const std::string&);

// count occurences of any of the characters in a string
// character set (second argument) is passed as in string::find_first_of()
size_t count_occurences(const std::string&, const std::string&);
size_t count_occurences(const std::string&, const char*);
size_t count_occurences(const std::string&, const char*, size_t);
size_t count_occurences(const std::string&, char);



/* standard config input cleaning function :
 * remove blank (space, tab and newline) at the begining and the end and
 * replace any squence of blank by a single space */
void clean_config_input(std::string &input);

/* get a word at the begining of a string and remove it from the string
 * a word is from begining to the first blank. blank is removed as well
 * it is designed for use on string cleaned with clean_config_input */
std::string getword(std::string&);

/* get a line at the begining of a string and remove it.
 * newline is removed as well */
std::string getline(std::string&);

/* get a block between '{' and '}' at the begining of input.
 * before first '{' shall only be blank. return the block and
 * remove it as well as { } from input. line is set to the
 * number of lines removed from input */
std::string getblock(std::string &input, size_t *line = nullptr);

/* look for the sequence " : " in a string. If found, set key to the first part
 * (before : ) and value to the second (after : ) and return true.
 * If not, return false. If value is empty, second space is optional.
 * Only the first " : " is considered */
bool get_key_value(const std::string &input,
                   std::string &key,  std::string &value);

/* convert a string to all upper(lower = false) / lower (lower = true) case.
 * default is upper */
void set_case(std::string &str, bool lower = false);

/* convert a color name to its corresponding code
 * color names are BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE */
int word_to_color(const std::string&);

/* convert a color code to its corresponding name */
std::string color_to_word(int);


#endif // CONFIG_LOAD_H_INCLUDED
