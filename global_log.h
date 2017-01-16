/* !
 * @brief Game's logs class
 * @author Colin Geniet
 * @version 2.1
 * @date 2016
 *
 * This is a debugging class that can be use to fix issues by creating a log file.
 * This class can be used as an output stream that both print to cerr and to a log file.
 *
 */

#ifndef GLOBAL_LOG_H_INCLUDED
#define GLOBAL_LOG_H_INCLUDED


#include <iostream>
#include <fstream>



 /*!
  * @brief Log class
  *
  * This class can be used as and outpup stream that print a log in both cerr and a log file.
  * It is usefull to send issues to the dev team.
  *
  */
class globalLog
{
public:
    /*!
    * @brief Constructor
    *
    * Open the logfile.
    *
    * @param file : Log file's name
    *
    */
    globalLog(const char *file = nullptr);

    /*!
    * @brief Set file to the correct value
    *
    * Close old file if needed then open the new one.
    *
    * @param file : New file's name
    *
    */
    void setfile(const char* file);  // value of null is equivalent to close()

    /*!
    * @brief Flush the buffer
    *
    * Call flush on log_file.
    *
    */
    void flush();

    /*!
    * @brief Close the file
    *
    * Flush and close log_file.
    *
    */
    void close();

    /*!
    * @brief Check if the log file is already openned
    *
    * @return True if the log file is open
    *
    */
    bool is_open() const;


    // general template

    /*!
    * @brief Stream overloading for log file
    *
    * Operator << can be used just like with std::ostream.
    *
    * @param obj : object to pass throw the stream
    *
    * @return log file to chainload
    *
    */
    template<typename Type>
    globalLog& operator<<(const Type& obj);

    // manipulators

    /*!
    * @brief Stream overloading for log file (function pointeur specialisation)
    *
    * Operator << can be used just like with std::ostream.
    *
    *
    *
    * @return log file to chainload
    *
    */
    globalLog& operator<<(std::ostream& (*pf)(std::ostream&));

    /*!
    * @brief Stream overloading for log file (function pointeur specialisation)
    *
    * Operator << can be used just like with std::ostream.
    *
    * @return log file to chainload
    *
    */
    globalLog& operator<<(std::ios& (*pf)(std::ios&));

    /*!
    * @brief Stream overloading for log file (function pointeur specialisation)
    *
    * Operator << can be used just like with std::ostream.
    *
    * @return log file to chainload
    *
    */
    globalLog& operator<<(std::ios_base& (*pf)(std::ios_base&));

private:
    std::ofstream log_file;         /*!< Log file */
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
