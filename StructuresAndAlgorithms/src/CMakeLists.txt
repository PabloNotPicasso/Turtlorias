add_subdirectory(Algorithms)
add_subdirectory(Logger)
add_subdirectory(Structures)

set(TARGET Sandbox)

set(SRC "main.cpp")
set(LIBS
    Algorithms
    Logger
    Structures::Geometry
    Structures::Mediator
    Structures::MinQueue
    Structures::SegmentAccumulator
    Structures::STL::Any
    Structures::STL::VectorBool
    Structures::STL::SharedPointer
    Structures::STL::String
    Structures::STL::Vector
    pthread
)
add_executable(${TARGET} ${SRC})
target_link_libraries(${TARGET} ${LIBS})
