set(TARGET BoolVector)
set(SRC "BoolVector.cpp")

add_library(${TARGET} ${SRC})
add_library(${PACKAGE}::${TARGET} ALIAS ${TARGET})