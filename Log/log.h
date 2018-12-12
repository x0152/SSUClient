#ifndef LOG_H
#define LOG_H
#include <string>

using std::string;

class Log
{
public:
    Log();
    static void WriteMsg(const string msg);
};

#endif // LOG_H
