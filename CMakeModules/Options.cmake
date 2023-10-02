include_guard(GLOBAL)

include(FeatureSummary)

option(ENABLE_TESTS "Enable test compilation" ON)
add_feature_info(ENABLE_TESTS ENABLE_TESTS "enables compilation of tests")

option(ENABLE_LOGS "Enable logs" ON)
add_feature_info(ENABLE_LOGS ENABLE_LOGS "enables showing of logs")

feature_summary(WHAT ALL)
