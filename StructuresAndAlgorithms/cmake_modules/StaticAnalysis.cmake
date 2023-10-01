find_package(
    Python3
    COMPONENTS Interpreter
    REQUIRED
)

###############################################################################
# cpp-check
###############################################################################
find_program(CPPCHECK_PATH cppcheck)

if(NOT CPPCHECK_PATH)
    message(FATAL_ERROR "No program 'cppcheck' found")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake_modules/cppcheck/cppcheck-suppressions.txt.in
    ${CMAKE_BINARY_DIR}/cppcheck-suppressions.txt
)

set(CPPCHECK_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/cppcheck-result.xml)

add_custom_command(
    OUTPUT ${CPPCHECK_OUTPUT}
    COMMAND
        ${CPPCHECK_PATH} --quiet
        # Enabled checks
        --enable=warning,performance,portability,information,missingInclude --language=c++ --xml
        --xml-version=2
        # Error to supress
        --inline-suppr
        # Suppression list
        --suppressions-list=${CMAKE_BINARY_DIR}/cppcheck-suppressions.txt
        # Ignore binary dir
        -i ${CMAKE_BINARY_DIR} ${CMAKE_SOURCE_DIR}
        --project=${CMAKE_BINARY_DIR}/compile_commands.json 2> ${CPPCHECK_OUTPUT}
    COMMENT "Analyzing code by 'cppcheck'"
)

add_custom_target(codeanalysis DEPENDS ${CPPCHECK_OUTPUT})

###############################################################################
# clang-tidy
###############################################################################
find_program(CLANG_TIDY_PATH clang-tidy)
if(NOT CLANG_TIDY_PATH)
    message(FATAL_ERROR "No program 'clang-tidy' found")
endif()

find_program(RUN_CLANG_TIDY_PATH run-clang-tidy.py HINTS /usr/share/clang)
if(NOT RUN_CLANG_TIDY_PATH)
    find_program(RUN_CLANG_TIDY_PATH run-clang-tidy HINTS /usr/bin/)
endif()
if(NOT RUN_CLANG_TIDY_PATH)
    message(FATAL_ERROR "No program 'run-clang-tidy.py' found")
endif()

set(CLANG_TIDY_OUTPUT_TEMP ${CMAKE_CURRENT_BINARY_DIR}/clang-tidy-result.output)
set(CLANG_TIDY_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/clang-tidy-result.txt)

add_custom_command(
    OUTPUT ${CLANG_TIDY_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E touch ${CLANG_TIDY_OUTPUT}
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${CLANG_TIDY_OUTPUT} ${CLANG_TIDY_OUTPUT_TEMP}
    COMMAND
        ${Python3_EXECUTABLE} ${RUN_CLANG_TIDY_PATH} -quiet
        # Header filter
        -p ${CMAKE_CURRENT_BINARY_DIR} -j `nproc` > ${CLANG_TIDY_OUTPUT_TEMP}
    COMMENT "Analyzing code by 'clang-tidy'"
)

add_custom_target(clangTidy DEPENDS ${CLANG_TIDY_OUTPUT})
