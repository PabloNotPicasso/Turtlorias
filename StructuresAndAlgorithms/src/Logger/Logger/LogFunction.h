#pragma once

#include "LoggerConfig.h"

#ifdef LOG_SHOW_FUNCTION_NAME // LOG_SHOW_FUNCTION_NAME is ON

#include "LogMessage.h"

#define FUNCTION_ENTERED FORMAT_MSG(" Entered{", FUNCTION_NAME)
#define FUNCTION_LEAVED FORMAT_MSG(" Leaved}", FUNCTION_NAME)
#define LOG_FUNCTION                                                                               \
    static const auto __functionEnteredMsg__ = FUNCTION_ENTERED;                                   \
    static const auto __functionLeavedMsg__ = FUNCTION_LEAVED;                                     \
    const FunctionEnterLeavedRAII __LogFunction__(__functionEnteredMsg__, __functionLeavedMsg__)

// Function Enter\Leaved logging
struct FunctionEnterLeavedRAII {
    FunctionEnterLeavedRAII(std::string_view enterMsg, std::string_view exitMsg)
        : m_exitMsg(exitMsg)
    {
        LOG_MSG_IMPL(Logger::LogLevel::LOG_VERBOSE, enterMsg);
    }

    ~FunctionEnterLeavedRAII()
    {
        LOG_MSG_IMPL(Logger::LogLevel::LOG_VERBOSE, m_exitMsg);
    }

private:
    const std::string_view m_exitMsg;
};

#else // LOG_SHOW_FUNCTION_NAME is OFF
#define FUNCTION_ENTERED
#endif