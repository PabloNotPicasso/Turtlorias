include(ExternalProject)

function(build_library LIBRARY)
    file(GLOB_RECURSE SRC_LIST "${LIBRARY}/*.cpp")
    list(FILTER SRC_LIST EXCLUDE REGEX "test")

    message(STATUS "sources:")
    list(APPEND CMAKE_MESSAGE_INDENT "   ")
    foreach(SRC_FILE ${SRC_LIST})
        message(STATUS "${SRC_FILE}")
    endforeach()
    list(POP_BACK CMAKE_MESSAGE_INDENT)

    add_library(${LIBRARY} ${SRC_LIST})
    add_library(${PACKAGE}::${LIBRARY} ALIAS ${LIBRARY})
endfunction()

function(build_test LIBRARY)
    if(NOT ${ENABLE_TESTS})
        return()
    endif()

    set(TestFolder "${CMAKE_CURRENT_SOURCE_DIR}/${LIBRARY}/test")
    set(MainTest "${TestFolder}/main.cpp")
    set(SingleTest "${TestFolder}/${LIBRARY}Test.cpp")

    if(EXISTS ${MainTest})
        set(TEST_SRC ${MainTest})
    elseif(EXISTS ${SingleTest})
        set(TEST_SRC ${SingleTest})
    else()
        message(FATAL_ERROR "There is no tests for ${SingleTest}")
    endif()

    message(STATUS "test:")
    list(APPEND CMAKE_MESSAGE_INDENT "   ")

    message(STATUS "${TEST_SRC}")
    list(POP_BACK CMAKE_MESSAGE_INDENT)

    add_gtest_test(${LIBRARY}_test ${TEST_SRC} ${LIBRARY})
endfunction()

function(add_structure LIBRARY)
    message(STATUS "Add structure \'${LIBRARY}\':")

    list(APPEND CMAKE_MESSAGE_INDENT "   ")
    build_library(${LIBRARY})
    target_link_libraries(${LIBRARY} Logger)
    build_test(${LIBRARY})
    list(POP_BACK CMAKE_MESSAGE_INDENT)

endfunction()
