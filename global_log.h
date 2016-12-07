#ifndef GLOBAL_LOG_H_INCLUDED
#define GLOBAL_LOG_H_INCLUDED


#include <iostream>
#include <fstream>


/* this class can be used as an output stream that both print to
 * cerr and to a log file */
class globalLog
{
public:
    globalLog(const char *file = nullptr);

    void setfile(const char*);  // value of null is equivalent to close()

    void flush();               // call flush on log_file
    void close();               // flush and close log_file

    bool is_open() const;


    // operator << can be used just like with std::ostream
    // general template
    template<typename Type>
    globalLog& operator<<(const Type&);

    // manipulators
    globalLog& operator<<(std::ostream& (*pf)(std::ostream&));
    globalLog& operator<<(std::ios& (*pf)(std::ios&));
    globalLog& operator<<(std::ios_base& (*pf)(std::ios_base&));

private:
    std::ofstream log_file;
};

template<typename Type>
globalLog& globalLog::operator<<(const Type &obj)
{
    std::cerr << obj;
    if(log_file.is_open()) log_file << obj;
    return *this;
}

// and a global instance to use
extern globalLog mlog;


#endif // GLOBAL_LOG_H_INCLUDED
