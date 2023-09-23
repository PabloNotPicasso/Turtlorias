set(PACKAGE Structures)

add_subdirectory(SegmentAccumulator)
add_subdirectory(Geometry)
add_subdirectory(STL)

build_library(Mediator)
build_library(MinQueue)

build_test(Mediator)
build_test(MinQueue)