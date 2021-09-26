#include "Logger.h"

#include <iostream>
#include <string>

namespace Logger {

std::string formatFunctionName(
    const std::string& function, const std::string& prettyFunction, const int& line)
{
    size_t locFunName = prettyFunction.find(function);
    size_t begin = prettyFunction.rfind(" ", locFunName) + 1;
    size_t end = prettyFunction.find("(", locFunName + function.length());
    std::string fmtName(prettyFunction.substr(begin, end - begin) + "()");

#ifdef SHOW_LINE_NUMBERS_IN_FUNCTION_NAME
    auto lineNumber(std::to_string(line));
    return "Line:" + strPadTo(lineNumber, lineNumberDigitsSize) + fmtName;
#else
    return fmtName;
#endif
}

void showMessage(const LogLevel& logLvl, const std::string& message)
{
    std::cout << message << std::endl;
}

} // namespace Logger