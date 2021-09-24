set(TARGET SharedPointer)
set(SRC "SharedPointer.cpp")

add_library(${TARGET} ${SRC})
add_library(${PACKAGE}::${TARGET} ALIAS ${TARGET})