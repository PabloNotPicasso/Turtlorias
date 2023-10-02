#pragma once

#include "LogLevel.h"
#include "LoggerConfig.h"

#include <string>
#include <string_view>

namespace Logger {

std::string_view formatFunctionName(std::string_view function, std::string_view prettyFunction);
std::string timestamp();
std::string line(int);

void showMessage(const LogLevel& logLvl, std::string_view message);

std::string formatMessage(const std::string& message, std::string_view name);

} // namespace Logger