add_subdirectory(Algorithms)
add_subdirectory(Structures)
add_subdirectory(Logger)

set(SRC "main.cpp")
set(LIBS
    Algorithms
    Structures::Any
    Structures::BoolVector
    Structures::SharedPointer
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})