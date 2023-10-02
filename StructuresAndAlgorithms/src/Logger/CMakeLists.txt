set(TARGET Logger)

configure_file(
    "${CMAKE_CURRENT_LIST_DIR}/Logger/LoggerConfig.h.in"
    "${CMAKE_CURRENT_LIST_DIR}/Logger/LoggerConfig.h" @ONLY
)

set(SRC "Logger/Logger.cpp" "Logger/LogLevel.cpp")

add_library(${TARGET} SHARED ${SRC})

add_gtest_test(${TARGET}_test "test/${TARGET}Test.cpp" ${TARGET})
