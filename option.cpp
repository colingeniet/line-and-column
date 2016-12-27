#include "option.h"

Option::Option(std::string _name, char _shortcut, bool _value) :
    name(_name),
    shortcut(_shortcut),
    value(_value)
{}

std::string Option::getname() const
{
    return name;
}

char Option::getshortcut() const
{
    return shortcut;
}

bool Option::value_required() const
{
    return value;
}

void Option::setname(std::string _name)
{
    name = _name;
}

void Option::setshortcut(char _shortcut)
{
    shortcut = _shortcut;
}

void Option::require_value(bool _value)
{
    value = _value;
}

bool Option::match(const std::string &argument, std::string *value_str)
{
    if(argument.size() <= 1) return false;
    if(argument[0] != '-') return false;

    if(argument[1] != '-')  // short options
    {
        if(argument[1] == shortcut &&
           argument.size() == 2 && !value) return true;
        else return false;
    }
    else                    // long options
    {
        if(!value) {
            if(argument.substr(2) == name) return true;
            else return false;
        } else {
            size_t pos = argument.find_first_of('=');

            if(pos == std::string::npos) return false;
            else if(argument.substr(2, pos-2) == name)
            {
                if(value_str) *value_str = argument.substr(pos+1);
                return true;
            }
            else return false;
        }
    }
}





void OptionSet::add_option(const Option &opt)
{
    options.push_back(opt);
}

bool OptionSet::find(const std::string &argument, std::string *name_str,
                     std::string *value_str)
{
    for(size_t i=0; i<options.size(); i++) {
        if(options[i].match(argument, value_str)) {
            if(name_str) *name_str = options[i].getname();
            return true;
        }
    }
    return false;
}
