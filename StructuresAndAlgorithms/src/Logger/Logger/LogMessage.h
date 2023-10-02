#pragma once

#include "LoggerConfig.h"

#ifdef ENABLE_LOGS // ENABLE_LOGS is ON

#include "Logger.h"
#ifdef LOG_SHOW_FUNCTION_NAME
#define FUNCTION_NAME Logger::formatFunctionName(__FUNCTION__, __PRETTY_FUNCTION__)
#else
#define FUNCTION_NAME std::string()
#endif

#define LOG_MSG_IMPL(LOG_LEVEL, message) Logger::showMessage(LOG_LEVEL, message)

#define FORMAT_MSG(message, name) Logger::formatMessage(message, name)

#define LOG_FUNC_MSG(LOG_LEVEL, message)                                                           \
    LOG_MSG_IMPL(Logger::LogLevel::LOG_LEVEL, FORMAT_MSG(message, FUNCTION_NAME))

#define LOG_VRB(message) LOG_FUNC_MSG(LOG_VERBOSE, message)
#define LOG_INF(message) LOG_FUNC_MSG(LOG_INFO, message)
#define LOG_ERR(message) LOG_FUNC_MSG(LOG_ERROR, message)
#define LOG_FTL(message) LOG_FUNC_MSG(LOG_FATAL, message)

#else // ENABLE_LOGS is OFF

#define LOG_VRB(message)
#define LOG_INF(message)
#define LOG_ERR(message)
#define LOG_FTL(message)

#endif // ENABLE_LOGS