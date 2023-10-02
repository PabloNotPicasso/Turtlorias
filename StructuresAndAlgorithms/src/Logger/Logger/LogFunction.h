#pragma once

#include "LoggerConfig.h"

#ifdef LOG_SHOW_FUNCTION_NAME // LOG_SHOW_FUNCTION_NAME is ON

#include "LogMessage.h"

#define LOG_FUNCTION                                                                               \
    static const auto __functionName__ = FUNCTION_NAME;                                            \
    const FunctionEnterLeavedRAII __LogFunction__(__functionName__)

// Function Enter\Leaved logging
struct FunctionEnterLeavedRAII {
    FunctionEnterLeavedRAII(std::string_view functionName)
        : m_functionName(functionName)
    {
        static constexpr std::string_view entered = "Entered {";
        LOG_MESSAGE_WITH_FUNCTION(LOG_VERBOSE, entered, m_functionName);
    }

    ~FunctionEnterLeavedRAII()
    {
        static constexpr std::string_view leaved = "Leaved  }";
        LOG_MESSAGE_WITH_FUNCTION(LOG_VERBOSE, leaved, m_functionName);
    }

private:
    const std::string_view m_functionName;
};

#else // LOG_SHOW_FUNCTION_NAME is OFF
#define LOG_FUNCTION
#endif