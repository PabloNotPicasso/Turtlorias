#pragma once
#include <ostream>

namespace Logger {

enum class LogLevel {
    LOG_VERBOSE,
    LOG_INFO,
    LOG_ERROR,
    LOG_FATAL,
};

std::ostream& operator<<(std::ostream& os, LogLevel logLevel);

} // namespace Logger
