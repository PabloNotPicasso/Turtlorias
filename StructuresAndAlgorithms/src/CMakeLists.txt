add_subdirectory(Algorithms)
add_subdirectory(CppTricks/FastPIMPL)
add_subdirectory(Logger)
add_subdirectory(Structures)

set(SRC "main.cpp")
set(LIBS
    Algorithms
    Structures::Geometry
    Structures::Mediator
    Structures::MinQueue
    Structures::SegmentAccumulator
    Structures::STL::Any
    Structures::STL::VectorBool
    Structures::STL::SharedPointer
    Structures::STL::String
    Structures::STL::Vector
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})
