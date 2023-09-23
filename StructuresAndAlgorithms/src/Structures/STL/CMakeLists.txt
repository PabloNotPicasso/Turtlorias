set(PACKAGE ${PACKAGE}::STL)

build_library(Any)
build_library(BoolVector)
build_library(SharedPointer)
build_library(String)
build_library(Vector)

build_test(Any)
build_test(BoolVector)
build_test(SharedPointer)
build_test(String)
build_test(Vector)