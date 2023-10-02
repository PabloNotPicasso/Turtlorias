#pragma once

#include "LoggerConfig.h"

#ifdef LOG_SHOW_FUNCTION_NAME // LOG_SHOW_FUNCTION_NAME is ON

#include "LogMessage.h"

#define FUNCTION_ENTERED FORMAT_MSG(" Entered{", FUNCTION_NAME)
#define FUNCTION_LEAVED FORMAT_MSG(" Leaved}", FUNCTION_NAME)
#define LOG_FUNCTION                                                                               \
    const FunctionEnterLeavedRAII __LogFunction__(FUNCTION_ENTERED, FUNCTION_LEAVED)

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

#else // LOG_SHOW_FUNCTION_NAME is OFF
#define FUNCTION_ENTERED
#endif