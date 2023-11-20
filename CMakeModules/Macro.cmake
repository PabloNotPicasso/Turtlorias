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

function(build_test)
    set(options "")
    set(oneValueArgs TARGET TEST_FOLDER)
    set(multiValueArgs "")
    cmake_parse_arguments(PARSED "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(TARGET ${PARSED_TARGET})
    if(NOT PARSED_TARGET)
        message(FATAL_ERROR "Missing required argument: TARGET")
    endif()

    set(TEST_FOLDER ${PARSED_TEST_FOLDER})
    if(NOT PARSED_TEST_FOLDER)
        set(TEST_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET}/test")
    endif()

    set(MainTest "${TEST_FOLDER}/main.cpp")
    set(SingleTest "${TEST_FOLDER}/${TARGET}Test.cpp")

    if(EXISTS ${MainTest})
        set(TEST_SRC ${MainTest})
    elseif(EXISTS ${SingleTest})
        set(TEST_SRC ${SingleTest})
    else()
        message(FATAL_ERROR "There is no tests for ${SingleTest}. MainTest = ${MainTest}. SingleTest = ${SingleTest}")
    endif()

    message(STATUS "test:")
    list(APPEND CMAKE_MESSAGE_INDENT "   ")

    message(STATUS "${TEST_SRC}")
    list(POP_BACK CMAKE_MESSAGE_INDENT)

    add_gtest_test(${TARGET}_test ${TEST_SRC} ${TARGET})
endfunction()



function(add_structure)

    set(options "")
    set(oneValueArgs TARGET DEPENDS)
    set(multiValueArgs "")
    cmake_parse_arguments(PARSED "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(TARGET ${PARSED_TARGET})
    set(DEPENDS ${PARSED_DEPENDS})
    if(NOT PARSED_TARGET)
        message(FATAL_ERROR "Missing required argument: TARGET")
    endif()
    
    message(STATUS "Add structure \'${TARGET}\':")

    list(APPEND CMAKE_MESSAGE_INDENT "   ")
    build_library(${TARGET})
    target_link_libraries(${TARGET} ${DEPENDS} Logger)
    build_test(TARGET ${TARGET})
    list(POP_BACK CMAKE_MESSAGE_INDENT)

endfunction()
