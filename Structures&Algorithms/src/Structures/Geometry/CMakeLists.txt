set(TARGET Geometry)

set(SRC "geometry.cpp")
add_library(${TARGET} ${SRC})

add_gtest_test(Vector_test "test/VectorTest.cpp" ${TARGET})