set(TARGET Algorithms)
set(SRC "AlgorithmsSandbox.cpp")

add_library(${TARGET} ${SRC})

add_gtest_test(${TARGET}_test "test/${TARGET}Test.cpp" ${TARGET})

add_gtest_test(QuickSelect_test "test/QuickSelectTest.cpp" ${TARGET})
