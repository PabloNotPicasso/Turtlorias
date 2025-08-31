#pragma once

#include "LogLevel.h"
#include "LoggerConfig.h"

#include <string>
#include <string_view>

namespace Logger {

std::string_view formatFunctionName(std::string_view function, std::string_view prettyFunction);
std::string timestamp();
std::string line(int);

std::string formatPrefix(std::string_view name);

} // namespace Logger
