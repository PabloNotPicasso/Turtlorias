#pragma once

#include "LoggerConfig.h"

#ifdef ENABLE_LOGS // ENABLE_LOGS is ON

#include "Logger.h"

#include <iomanip>
#include <iostream>

#ifdef LOG_SHOW_FUNCTION_NAME
#define FUNCTION_NAME Logger::formatFunctionName(__FUNCTION__, __PRETTY_FUNCTION__)
#else
#define FUNCTION_NAME std::string()
#endif

#define SHOW_LOG(logMessage) std::cout << std::boolalpha << logMessage << '\n';

#define CREATE_LOG_MSG(LOG_LEVEL, prefix, message)                                                 \
    "[" << LOG_LEVEL << "]" << prefix << " " << message

#define FORMAT_PREFIX(name) Logger::formatPrefix(name)

#define LOG_MESSAGE_WITH_FUNCTION(LOG_LEVEL, message, functionName)                                \
    SHOW_LOG(CREATE_LOG_MSG(Logger::LogLevel::LOG_LEVEL, FORMAT_PREFIX(functionName), message))

#define LOG_MESSAGE(LOG_LEVEL, message) LOG_MESSAGE_WITH_FUNCTION(LOG_LEVEL, message, FUNCTION_NAME)

#define LOG_VRB(message) LOG_MESSAGE(LOG_VERBOSE, message)
#define LOG_INF(message) LOG_MESSAGE(LOG_INFO, message)
#define LOG_ERR(message) LOG_MESSAGE(LOG_ERROR, message)
#define LOG_FTL(message) LOG_MESSAGE(LOG_FATAL, message)

#else // ENABLE_LOGS is OFF

#define LOG_VRB(message)
#define LOG_INF(message)
#define LOG_ERR(message)
#define LOG_FTL(message)

#endif // ENABLE_LOGS
