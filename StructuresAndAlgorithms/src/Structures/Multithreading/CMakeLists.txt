include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_structure(TARGET Event)
add_structure(TARGET Signal)
add_structure(TARGET EventLoop DEPENDS Event)

add_subdirectory(Timer)
