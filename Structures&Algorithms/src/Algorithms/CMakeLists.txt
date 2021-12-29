set(TARGET Algorithms)
set(SRC "Algorithms.cpp")

add_library(${TARGET} ${SRC})

add_gtest_test(${TARGET}_test "test/${TARGET}Test.cpp" ${TARGET})