cmake_minimum_required(VERSION 3.5)
include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

project(cpp-tricks)

include(CTest)
include(SetUp)
include(CodeFormatting)
include(Macro)
include(AddGoogleTest)

include_directories(src)
add_subdirectory(src)