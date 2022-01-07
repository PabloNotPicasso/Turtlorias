cmake_minimum_required(VERSION 3.5)
include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

project(gtest-guide)

include(AddGoogleTest)
include(CodeFormatting)

# adding possibility to run 'make test'
include(CTest)

include_directories(src)
add_subdirectory(src)