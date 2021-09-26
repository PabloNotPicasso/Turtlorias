#pragma once
#include "Logger.h"
#include <string>

#ifdef SHOW_LINE_NUMBERS_IN_FUNCTION_NAME
#define __FORMAT_PRETTY_FUNCTION__                                                                 \
    Logger::formatFunctionName(__FUNCTION__, __PRETTY_FUNCTION__,__LINE__)
#else
#define __FORMAT_PRETTY_FUNCTION__                                                                 \
    Logger::formatFunctionName(__FUNCTION__, __PRETTY_FUNCTION__)
#endif

#define FUNCTION_NAME __FORMAT_PRETTY_FUNCTION__

#define LOG_MSG_IMPL(LOG_LEVEL, message) Logger::showMessage(LOG_LEVEL, message)
#define FORMAT_MSG(message) Logger::formatMessage(message).c_str()
#define LOG_FUNC_MSG(LOG_LEVEL, message)                                                               \
    LOG_MSG_IMPL(                                                                                  \
        Logger::LogLevel::LOG_LEVEL, FORMAT_MSG( FUNCTION_NAME + " : " + message))

#define LOG_VRB(message) LOG_FUNC_MSG(LOG_VERBOSE, FORMAT_MSG(message))
#define LOG_INF(message) LOG_FUNC_MSG(LOG_INFO, FORMAT_MSG(message))
#define LOG_ERR(message) LOG_FUNC_MSG(LOG_ERROR, FORMAT_MSG(message))
#define LOG_FTL(message) LOG_FUNC_MSG(LOG_FATAL, FORMAT_MSG(message))

#define FUNCTION_ENTERED FORMAT_MSG( FUNCTION_NAME + " Entered{")
#define FUNCTION_LEAVED FORMAT_MSG(FUNCTION_NAME + " Leaved}")
#define LOG_FUNCTION_ENTERED_LEAVED                                                                \
    const FunctionEnterLeavedRAII __logFelRAII__(FUNCTION_ENTERED, FUNCTION_LEAVED)
#define LOG_FUNCTION LOG_FUNCTION_ENTERED_LEAVED

// Function Enter\Leaved logging
struct FunctionEnterLeavedRAII
{
    FunctionEnterLeavedRAII(const std::string& enterMsg, const std::string& exitMsg)
        : m_exitMsg(exitMsg)
    {
        LOG_VRB(enterMsg);
    }

    ~FunctionEnterLeavedRAII()
    {
        LOG_VRB(m_exitMsg);
    }

private:
    const std::string m_exitMsg;
};
