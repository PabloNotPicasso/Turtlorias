#include "Logger.h"

#include <chrono>
#include <iomanip>
#include <iostream>

namespace Logger {

std::string_view formatFunctionName(std::string_view function, std::string_view prettyFunction)
{
    const size_t locFunName = prettyFunction.find(function);
    const size_t begin = prettyFunction.rfind(" ", locFunName) + 1;
    const size_t end = prettyFunction.length();
    std::string_view fmtName = prettyFunction.substr(begin, end - begin);

    // Cut off the namespace if exists
    for (size_t semicolonCounter = 0, namespaceIdx = fmtName.rfind("::", fmtName.length());
         namespaceIdx != std::string::npos;
         namespaceIdx = fmtName.rfind("::", namespaceIdx)) {
        ++semicolonCounter;
        if (2 == semicolonCounter) {
            fmtName.remove_prefix(namespaceIdx + 2);
            break;
        }
        namespaceIdx -= 1;
    }
    return fmtName;
}

std::string timestamp()
{
    using namespace std::chrono;
    auto nowTimeMs = time_point_cast<milliseconds>(steady_clock::now());
    return std::to_string(nowTimeMs.time_since_epoch().count() % 1'000'000);
}

std::string line(int lineNumber)
{
    return std::to_string(lineNumber);
}

std::string formatPrefix(std::string_view name)
{
#if !defined(LOG_SHOW_TIMESTAMP) and !defined(LOG_SHOW_FUNCTION_NAME)
    return "";
#endif

    std::string prefix;
    prefix.reserve(40);
    prefix.push_back(' ');

#ifdef LOG_SHOW_TIMESTAMP
    prefix += timestamp();
    prefix.push_back(' ');
#endif

#ifdef LOG_SHOW_FUNCTION_NAME
    prefix += name;
    prefix.push_back(' ');
#endif

    prefix.push_back(':');
    return prefix;
}

} // namespace Logger
