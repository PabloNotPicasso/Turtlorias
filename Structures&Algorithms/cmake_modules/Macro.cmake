include(ExternalProject)

macro(build_library LIBRARY)
    set(SRC "${LIBRARY}/${LIBRARY}.cpp")
    add_library(${LIBRARY} ${SRC})
    add_library(${PACKAGE}::${LIBRARY} ALIAS ${LIBRARY})
endmacro()

macro(build_test LIBRARY)
    add_gtest_test(${LIBRARY}_test "${LIBRARY}/test/${LIBRARY}Test.cpp" ${LIBRARY})
endmacro()
