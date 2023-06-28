set(PACKAGE Structures)

add_subdirectory( SegmentAccumulator )

build_library(Any)
build_library(BoolVector)
build_library(SharedPointer)
build_library(Mediator)
build_library(MinQueue)

build_test(Any)
build_test(BoolVector)
build_test(SharedPointer)
build_test(Mediator)
build_test(MinQueue)