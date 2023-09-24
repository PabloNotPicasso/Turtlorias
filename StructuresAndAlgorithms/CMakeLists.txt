cmake_minimum_required(VERSION 3.5)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

project(StructuresAndAlogrithms)

include(ModuleList)

include_directories(src)
add_subdirectory(src)