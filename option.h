#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED


#include <string>
#include <vector>
#include <exception>


/* general purpose class for command line options definition
 * desined for --long, -short and --option=value syntax */
class Option
{
public:
    Option(std::string _name, char _shortcut = 0, bool _value = false);

    std::string getname() const;
    char getshortcut() const;
    bool value_required() const;

    void setname(std::string);
    void setshortcut(char);
    void require_value(bool);

    bool match(const std::string &argument, std::string* value_str = nullptr);

private:
    std::string name;
    char shortcut;
    bool value;
};


class OptionSet
{
public:
    void add_option(const Option&);

    // look for a matching option in the set
    // if found, name_str is set to the option full name,
    // value_str to the value - if any - and it return true
    // if not found, it return false
    bool find(const std::string &argument, std::string *name_str,
              std::string *value_str);

    const Option& operator[](size_t);

private:
    std::vector<Option> options;
};

#endif // OPTION_H_INCLUDED
