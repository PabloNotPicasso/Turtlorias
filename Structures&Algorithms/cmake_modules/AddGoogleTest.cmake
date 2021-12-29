find_package(GTest REQUIRED CONFIG)

include(GoogleTest)

if(TARGET GTest::gtest)
    get_property(
        GTEST_LOCATION
        TARGET GTest::gtest
        PROPERTY LOCATION
    )
    message(STATUS "Found GTest: ${GTEST_LOCATION}")
else()
    message(FATAL_ERROR "GTest library NOT found")
endif()

if(TARGET GTest::gmock)
    get_property(
        GMOCK_LOCATION
        TARGET GTest::gmock
        PROPERTY LOCATION
    )
    message(STATUS "Found GMock: ${GMOCK_LOCATION}")
else()
    message(FATAL_ERROR "GMock library NOT found")
endif()

macro(add_gtest_test testName files libraries)

    if((NOT TARGET GTest::gtest) OR (NOT TARGET GTest::gmock))
        message(FATAL_ERROR "No gtest or gmock targets found, can't add tests")
    else()
        add_executable(${testName} ${files})

        target_link_libraries(
            ${testName} ${libraries} GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
        )

        add_test(NAME ${testName} COMMAND ${testName})
    endif()

endmacro()
