include(ExternalProject)

macro(build_library LIBRARY)
    file(GLOB SRC "${LIBRARY}/*.cpp")
    message("${LIBRARY} source files: ${SRC}")
    add_library(${LIBRARY} ${SRC})
    add_library(${PACKAGE}::${LIBRARY} ALIAS ${LIBRARY})
endmacro()

macro(build_test LIBRARY)
    add_gtest_test(${LIBRARY}_test "${LIBRARY}/test/${LIBRARY}Test.cpp" ${LIBRARY})
endmacro()

macro(build_multitest LIBRARY)
    add_gtest_test(${LIBRARY}_test "${LIBRARY}/test/main.cpp" ${LIBRARY})
endmacro()