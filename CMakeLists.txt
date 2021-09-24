cmake_minimum_required(VERSION 3.5)
include(GNUInstallDirs)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

project(cpp-tricks)

include(SetUp)
include(CodeFormatting)
include(Macro)

add_subdirectory(src)

