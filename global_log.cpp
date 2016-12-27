#include "global_log.h"


globalLog mlog;


globalLog::globalLog(const char *file) {
    if(file) log_file.open(file);
}

void globalLog::setfile(const char *file) {
    if(log_file.is_open()) log_file.close();
    if(file) log_file.open(file);
}

void globalLog::flush() {
    if(log_file.is_open()) log_file.flush();
}

void globalLog::close() {
    if(log_file.is_open()) log_file.close();
}

bool globalLog::is_open() const {
    return log_file.is_open();
}


globalLog& globalLog::operator<<(std::ostream& (*pf)(std::ostream&))
{
    std::cerr << pf;
    if(log_file.is_open()) log_file << pf;
    return *this;
}

globalLog& globalLog::operator<<(std::ios& (*pf)(std::ios&))
{
    std::cerr << pf;
    if(log_file.is_open()) log_file << pf;
    return *this;
}

globalLog& globalLog::operator<<(std::ios_base& (*pf)(std::ios_base&))
{
    std::cerr << pf;
    if(log_file.is_open()) log_file << pf;
    return *this;
}
