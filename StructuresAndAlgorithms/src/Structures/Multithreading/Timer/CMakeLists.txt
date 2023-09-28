set(TARGET Timer)

set(SRC TimerThread.cpp Timer.cpp TimerImpl.cpp)

add_library(${TARGET} ${SRC})
target_link_libraries(${TARGET} Logger)

add_gtest_test(${TARGET}_test "test/TimerThreadTest.cpp" ${TARGET})
