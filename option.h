/* !
 * @brief Option class
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * This class allow the game to be lauch with some command lines.
 *
 * General purpose class for command line options definition
 * desined for --long, -short and --option=value synta.x.
 *
 */

#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED


#include <string>
#include <vector>
#include <exception>


/*!
 * @brief Option class
 *
 * This class represent a unique option
 *
 */
class Option
{
public:
    /*!
    * @brief Constructor
    *
    * Create an option instance
    *
    * @param _name : Option's name
    * @param _shortcut : short character
    * @param _value : value
    *
    */
    Option(std::string _name, char _shortcut = 0, bool _value = false);

    /*!
    * @brief Accesor for the name
    *
    * @return The otpion's name
    *
    */
    std::string getname() const;
    /*!
    * @brief Accesor for the shortcut
    *
    * @return The otpion's shortcut
    *
    */
    char getshortcut() const;
    /*!
    * @brief Accesor for the value
    *
    * @return The otpion's value
    *
    */
    bool value_required() const;

    /*!
    * @brief Accesor for the name (writing)
    *
    * @param _name : Name
    *
    */
    void setname(std::string _name);
    /*!
    * @brief Accesor for the shortcut (writing)
    *
    * @param _sc : Shortcut character
    *
    */
    void setshortcut(char _sc);
    /*!
    * @brief Accesor for the value (writing)
    *
    * @param _value : Value
    *
    */
    void require_value(bool _value);

    /*!
    * @brief Check if the argument match with this option
    *
    * @param argument : Argument tested
    * @param value_str : Optional return string
    *
    * @return True if the option match with arguments
    *
    */
    bool match(const std::string &argument, std::string* value_str = nullptr);

private:
    std::string name;       /*!< Option's name */
    char shortcut;          /*!< Option's shortcut */
    bool value;             /*!< Option's value required */
};

/*!
 * @brief Option set class
 *
 * This class represent a set of options
 *
 */
class OptionSet
{
public:
    /*!
    * @brief Add an option to the set
    *
    * @param opt : Option to add
    *
    */
    void add_option(const Option& opt);

    /*!
    * @brief Check if the argument match with this option
    *
    * look for a matching option in the set.
    * If found, name_str is set to the option full name,
    * value_str to the value - if any - and it return true
    * if not found, it return false.
    *
    * @param argument : Argument tested
    * @param name_str : Option found's name
    * @param value_str : Optional found's value
    *
    * @return True if an option match
    *
    */
    bool find(const std::string &argument, std::string *name_str,
              std::string *value_str);

    /*!
    * @brief Accesor overloading
    *
    * @param n : Option n° n
    *
    * @return Option wanted
    *
    */
    const Option& operator[](size_t n);

private:
    std::vector<Option> options;        /*!< Options's array */
};

#endif // OPTION_H_INCLUDED
