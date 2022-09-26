cmake_minimum_required(VERSION 3.5)
include(GNUInstallDirs)

project(Tricks)

function(addTrick TrickName)
    add_executable(Trick_${TrickName} ${TrickName}.cpp)
endfunction(addTrick)

addTrick(streamRedirection)
addTrick(strangeDefaultValues)
