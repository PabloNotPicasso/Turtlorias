set(PACKAGE Structures)

add_subdirectory( SegmentAccumulator )
add_subdirectory(Geometry)

build_library(Any)
build_library(Vector)
build_library(BoolVector)
build_library(SharedPointer)
build_library(Mediator)
build_library(MinQueue)

build_test(Any)
build_test(Vector)
build_test(BoolVector)
build_test(SharedPointer)
build_test(Mediator)
build_test(MinQueue)