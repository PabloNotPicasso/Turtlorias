add_subdirectory(Algorithms)
add_subdirectory(Structures)
add_subdirectory(Logger)
add_subdirectory(CppTricks/FastPIMPL)

set(SRC "main.cpp")
set(LIBS
    Algorithms
    Structures::Geometry
    Structures::Mediator
    Structures::MinQueue
    Structures::SegmentSqrt
    Structures::SegmentBrute
    Structures::SegmentTree
    Structures::STL::Any
    Structures::STL::BoolVector
    Structures::STL::SharedPointer
    Structures::STL::String
    Structures::STL::Vector
)

add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIBS})