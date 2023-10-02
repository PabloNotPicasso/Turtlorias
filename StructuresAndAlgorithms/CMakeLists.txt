cmake_minimum_required(VERSION 3.22)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../CMakeModules")

project(StructuresAndAlogrithms)

include(ModuleList)

include_directories(src)
add_subdirectory(src)
