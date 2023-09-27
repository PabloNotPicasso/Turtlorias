#include "LogLevel.h"

#include <ostream>
#include <string_view>
#include <unordered_map>

namespace Logger {

static const std::unordered_map<LogLevel, std::string_view> logLevelToStr{
    {LogLevel::LOG_VERBOSE, "LOG_VERBOSE"},
    {LogLevel::LOG_INFO, "LOG_INFO"},
    {LogLevel::LOG_ERROR, "LOG_ERROR"},
    {LogLevel::LOG_FATAL, "LOG_FATAL"}};

std::ostream& operator<<(std::ostream& os, LogLevel logLevel)
{
    return os << logLevelToStr.at(logLevel);
}

} // namespace Logger