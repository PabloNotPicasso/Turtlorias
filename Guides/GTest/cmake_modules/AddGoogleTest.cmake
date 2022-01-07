find_package(GTest REQUIRED CONFIG)

include(GoogleTest)

if((NOT TARGET GTest::gtest) OR (NOT TARGET GTest::gmock))
    message(FATAL_ERROR "No gtest or gmock targets found, can't add tests")
endif()

set(GTest_libs GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

macro(add_gtest_test testName files libraries)
    add_executable(${testName} ${files})
    target_link_libraries(
        ${testName} ${libraries} ${GTest_libs} 
    )
    add_test(NAME ${testName} COMMAND ${testName})
endmacro()
