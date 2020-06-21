#include "logger.hpp"



void Logger::debug(string message) {
    int level = DEBUG;
    _logging(level, message);

    return;
}

void Logger::info(string message) {
    int level = INFO;
    _logging(level, message);

    return;
}
void Logger::warn(string message) {
    int level = WARN;
    _logging(level, message);

    return;
}



void Logger::_logging(int level, string message) {
    if (_level <= level) {
        cout << message << endl;
    }

    return;
}
