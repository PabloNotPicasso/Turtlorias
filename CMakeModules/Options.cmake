include_guard(GLOBAL)

include(FeatureSummary)

option(ENABLE_TESTS "Enable test compilation" ON)
add_feature_info(ENABLE_TESTS ENABLE_TESTS "enables compilation of tests")

option(ENABLE_LOGS "Enable logs" ON)
add_feature_info(ENABLE_LOGS ENABLE_LOGS "enables showing of logs")

if(ENABLE_LOGS)
    option(LOG_SHOW_TIMESTAMP "Enable timestamps in logs" ON)
    add_feature_info(LOG_SHOW_TIMESTAMP LOG_SHOW_TIMESTAMP "enables timestamps in logs")

    option(LOG_SHOW_FUNCTION_NAME "Enable function enter-leave logs" ON)
    add_feature_info(LOG_SHOW_FUNCTION_NAME LOG_SHOW_FUNCTION_NAME "enables function enter-leave logs")
endif()

feature_summary(WHAT ALL)
