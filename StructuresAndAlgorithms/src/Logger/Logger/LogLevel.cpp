#include "LogLevel.h"

#include <ostream>
#include <string_view>
#include <unordered_map>

namespace Logger {

static const std::unordered_map<LogLevel, std::string_view> logLevelToStr{
    {LogLevel::LOG_VERBOSE, "VRB"},
    {LogLevel::LOG_INFO, "INF"},
    {LogLevel::LOG_ERROR, "ERR"},
    {LogLevel::LOG_FATAL, "FAT"}};

std::ostream& operator<<(std::ostream& os, LogLevel logLevel)
{
    return os << logLevelToStr.at(logLevel);
}

} // namespace Logger