#pragma once
#include <string>

namespace Logger {

enum LogLevel {
    LOG_VERBOSE,
    LOG_INFO,
    LOG_ERROR,
    LOG_FATAL,
};

std::string formatFunctionName(
    const std::string& function, const std::string& prettyFunction, const int& line = 0);
void showMessage(const LogLevel& logLvl, const std::string& message);

template<typename... Args>
std::string formatMessage(const std::string& message)
{
    return message;
}

} // namespace Logger