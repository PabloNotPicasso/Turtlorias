set(TARGET Geometry)

set(SRC "Geometry.h")

add_library(${TARGET} ${SRC})
add_library(${PACKAGE}::${TARGET} ALIAS ${TARGET})

set_target_properties(${TARGET} PROPERTIES LINKER_LANGUAGE CXX)

add_gtest_test(GeometryVector_test "test/GeometryVectorTest.cpp" ${TARGET})