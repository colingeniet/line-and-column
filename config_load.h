/* !
 * @brief Configuration class
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * Customs exeptions methods and functions used to load / save the game from a configuration file.
 * Add some exeptions to treate unexpected cases.
 *
 */

#ifndef CONFIG_LOAD_H_INCLUDED
#define CONFIG_LOAD_H_INCLUDED


#include <cstddef>      // size_t
#include <string>
#include <exception>    // std::exception


/*!
 * @brief Config class
 *
 * This class defines I/O from/to a confi. file and handle differents exeptions.
 *
 * Exception class for file parsing syntax errors.
 *
 */
class syntax_exception : public std::exception {
public:
    /*!
    * @brief Default exeption constructor
    *
    */
    syntax_exception();

    /*!
     * @brief Exception constructor
     *
     * To create an exception message. A line can be specify if needed.
     *
     * @param line : Line where the exception as been lauched
     * @param detail : Exception message
     *
     */
    syntax_exception(const std::string &detail, size_t line = (size_t)-1);

    /*!
     * @brief Tell what happened
     *
     * If those functions throw an exception, something has gone horribly wrong !
     *
     * @return A C string that contain the error message
     *
     */
    const char* what() const throw();

    /*!
     * @brief Tell where it happened
     *
     * @return The line where error occurred
     *
     */
    size_t getline() const throw();

private:
    std::string msg;    /*!< Exception message */
    size_t line;        /*!< Exception line */
};

/*!
 * @brief Check if a the string contain only blanck caracters
 *
 * @return true if string contain only spaces, tabs and newlines
 *
 */
bool blank_only(const std::string&);


/*!
 * @brief Count occurences of any of the characters in a string
 *
 * Character set (second argument) is passed as in string::find_first_of()
 *
 * @param input : The string where to search
 * @param ch : The caracter to search
 *
 * @return Number of occurences
 *
 */
size_t count_occurences(const std::string& input, const std::string& ch);
/*!
 * @brief Count occurences of any of the characters in a string
 *
 * Character set (second argument) is passed as in string::find_first_of()
 *
 * @param input : The string where to search
 * @param ch : The caracter to search
 *
 * @return Number of occurences
 *
 */
size_t count_occurences(const std::string& input, const char* ch);
/*!
 * @brief Count occurences of any of the characters in a string
 *
 * Character set (second argument) is passed as in string::find_first_of()
 *
 * @param input : The string where to search
 * @param ch : The caracter to search
 * @param n : Number of character values to search for
 *
 * @return Number of occurences
 *
 */
size_t count_occurences(const std::string& input, const char* ch, size_t);
/*!
 * @brief Count occurences of any of the characters in a string
 *
 * Character set (second argument) is passed as in string::find_first_of()
 *
 * @param input : The string where to search
 * @param ch : The caracter to search
 *
 * @return Number of occurences
 *
 */
size_t count_occurences(const std::string& input, char ch);



/*!
* @brief Standard config input cleaning function
*
* Remove blank (space, tab and newline) at the begining and the end.
* Then replace any sequence of blank by a single space
*
* @param input : The string to clean
*
*/
void clean_config_input(std::string &input);


/*!
* @brief Get a word at the begining of a string then remove it
*
* A word is the group of caracters from begining to the first blank.
* The blank is removed as well, it is designed for use on string
* cleaned with clean_config_input.
*
* @param input : The string where extract the 1st word
*
* @return The extracted word
*
*/
std::string getword(std::string& input);


/*!
* @brief Get a line at the begining of a string then remove it
*
* @param input : The string where extract the 1st line
*
* @return The extracted line
*
*/
std::string getline(std::string&);


/*!
* @brief Get a block between '{' and '}'
*
* Before first '{' shall only be blank. Return the block and
* remove it as well as { } from input.
* Line is set to the number of lines removed from input
*
* @param input : The string where extract the block
* @param line : The number of line extracted (ie. block's size)
*
* @return The block extracted
*
*/
std::string getblock(std::string &input, size_t *line = nullptr);

/*!
* @brief Search a title
*
* Look for the sequence " : " in a string
* If the sequence is found, set key to the first part (before : )
* and value to the second (after : ) and return true.
* If not, return false. If value is empty, second space is optional.
* Only the first " : " is considered.
*
* @param input : The string where search for the sequence ':'
* @param line : The keyword that describe the sequence find
* @param value : The sequence value
*
* @return True is the sequence has been found
*
*/
bool get_key_value(const std::string &input,
                   std::string &key,  std::string &value);


/*!
* @brief Convert a string to all UPPER / lower case
*
* By default it convert to lower.
*
* @param str : The string to convert
* @param lower : Case wanted
*
*/
void set_case(std::string &str, bool lower = false);

/*!
* @brief Convert a color name to its corresponding code
*
* Color names are following : BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.
*
* @param color : The color name
*
* @return The color's corresponding code
*
*/
int word_to_color(const std::string& color);


/*!
* @brief Convert a color code to its corresponding name
*
* Color names will be one following : BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE.
*
* @param code : The color's code
*
* @return The color's corresponding name
*
*/
std::string color_to_word(int code);


#endif // CONFIG_LOAD_H_INCLUDED
