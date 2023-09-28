#pragma once
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

#define FUNCTION_ENTERED FORMAT_MSG(" Entered{", FUNCTION_NAME)
#define FUNCTION_LEAVED FORMAT_MSG(" Leaved}", FUNCTION_NAME)
#define LOG_FUNCTION_ENTERED_LEAVED                                                                \
    const FunctionEnterLeavedRAII __logFelRAII__(FUNCTION_ENTERED, FUNCTION_LEAVED)
#define LOG_FUNCTION LOG_FUNCTION_ENTERED_LEAVED

// Function Enter\Leaved logging
struct FunctionEnterLeavedRAII {
    FunctionEnterLeavedRAII(const std::string& enterMsg, const std::string& exitMsg)
        : m_exitMsg(exitMsg)
    {
        LOG_MSG_IMPL(Logger::LogLevel::LOG_VERBOSE, enterMsg);
    }

    ~FunctionEnterLeavedRAII()
    {
        LOG_MSG_IMPL(Logger::LogLevel::LOG_VERBOSE, m_exitMsg);
    }

private:
    const std::string m_exitMsg;
};
