add_subdirectory(Algorithms)

set(SRC "main.cpp")
set(LIBS
    Algorithms
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})