#include "Logger.h"

#include <chrono>
#include <iostream>

namespace Logger {

std::string_view formatFunctionName(std::string_view function, std::string_view prettyFunction)
{
    const size_t locFunName = prettyFunction.find(function);
    const size_t begin = prettyFunction.rfind(" ", locFunName) + 1;
    const size_t end = prettyFunction.find("(", locFunName + function.length());
    std::string_view fmtName = prettyFunction.substr(begin, end - begin);
    return fmtName;
}

std::string timestamp()
{
    using namespace std::chrono;
    auto nowTime = duration_cast<milliseconds>(steady_clock::now().time_since_epoch());
    return std::to_string(nowTime.count() % 1'000'000);
}

std::string line(int lineNumber)
{
    return std::to_string(lineNumber);
}

std::string formatMessage(const std::string& message, std::string_view name)
{
    std::string prefix;

#ifdef LOG_SHOW_TIMESTAMP
    prefix += timestamp() + " ";
#endif

#ifdef LOG_SHOW_FUNCTION_NAME
    prefix += name;
    prefix += "()";
#endif

#if defined(LOG_SHOW_TIMESTAMP) or defined(LOG_SHOW_FUNCTION_NAME)
    prefix += ": ";
#endif

    return prefix + message;
}

void showMessage(const LogLevel& logLvl, const std::string& message)
{
    std::cout << message << std::endl;
}

} // namespace Logger