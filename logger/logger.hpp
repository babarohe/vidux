#include <string>
#include <iostream>

#define DEBUG 0
#define INFO 1
#define WARN 2
#define ERROR 3
#define FATAL 4
#define LEVEL_NUM 5

using namespace std;


class Logger {
public:
    string DEBUG_STRING = "DEBUG";
    string INFO_STRING  = "INFO";
    string WARN_STRING  = "WARN";
    string ERROR_STRING = "ERROR";
    string FATAL_STRING = "FATAL";

    string level_strings[LEVEL_NUM] = {DEBUG_STRING, INFO_STRING, WARN_STRING, ERROR_STRING, FATAL_STRING};

    void debug(string message);
    void info(string message);
    void warn(string message);

private:
    int _level = INFO;

    void _logging(int level, string message);

};
