set(TARGET Geometry)

set(SRC "geometry.cpp")
add_library(${TARGET} ${SRC})

add_gtest_test(GeometryVector_test "test/GeometryVectorTest.cpp" ${TARGET})