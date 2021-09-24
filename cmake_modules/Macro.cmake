include(ExternalProject)

macro(build_library LIBRARY)
    set(SRC "${LIBRARY}/${LIBRARY}.cpp")
    add_library(${LIBRARY} ${SRC})
    add_library(${PACKAGE}::${LIBRARY} ALIAS ${LIBRARY})
endmacro()
