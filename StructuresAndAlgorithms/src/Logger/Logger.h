#pragma once

#include "LogLevel.h"

#include <string>
#include <string_view>

#define LOG_SHOW_TIMESTAMP
#define LOG_SHOW_FUNCTION_NAME

namespace Logger {

std::string_view formatFunctionName(std::string_view function, std::string_view prettyFunction);
std::string timestamp();
std::string line(int);

void showMessage(const LogLevel& logLvl, const std::string& message);

std::string formatMessage(const std::string& message, std::string_view name);

} // namespace Logger