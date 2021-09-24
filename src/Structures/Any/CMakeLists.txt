set(TARGET Any)
set(SRC "Any.cpp")

add_library(${TARGET} ${SRC})
add_library(${PACKAGE}::${TARGET} ALIAS ${TARGET})