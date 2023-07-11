find_program(CPPCHECK_PATH cppcheck)
find_program(CLANG_TIDY_PATH clang-tidy)
find_program(RUN_CLANG_TIDY_PATH run-clang-tidy.py HINTS /usr/share/clang)
find_package(
    Python3
    COMPONENTS Interpreter
    REQUIRED
)

if(NOT CPPCHECK_PATH)
    message(FATAL_ERROR "No program 'cppcheck' found")
endif()
if(NOT CLANG_TIDY_PATH)
    message(FATAL_ERROR "No program 'clang-tidy' found")
endif()
if(NOT RUN_CLANG_TIDY_PATH)
    find_program(RUN_CLANG_TIDY_PATH run-clang-tidy HINTS /usr/bin/)
endif()
if(NOT RUN_CLANG_TIDY_PATH)
    message(FATAL_ERROR "No program 'run-clang-tidy.py' found")
endif()

configure_file(
    ${CMAKE_SOURCE_DIR}/cmake_modules/cppcheck/cppcheck-suppressions.txt.in
    ${CMAKE_BINARY_DIR}/cppcheck-suppressions.txt
)

add_custom_command(
    OUTPUT cppcheck-result.xml
    COMMAND
        ${CPPCHECK_PATH} --quiet --enable=warning,performance,portability,information,missingInclude
        --language=c++ --xml --xml-version=2
        --suppressions-list=${CMAKE_BINARY_DIR}/cppcheck-suppressions.txt
        -i ${CMAKE_BINARY_DIR}
        ${CMAKE_SOURCE_DIR}
        --project=${CMAKE_BINARY_DIR}/compile_commands.json 2>
        ${CMAKE_BINARY_DIR}/cppcheck-result.xml
    COMMENT "Analyzing code by 'cppcheck'"
)

add_custom_command(
    OUTPUT clang-tidy-result.txt
    COMMAND
        ${Python3_EXECUTABLE} ${RUN_CLANG_TIDY_PATH} -quiet
        -header-filter=${CMAKE_CURRENT_SOURCE_DIR}/src/.* -p ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR} -j `nproc` > ${CMAKE_CURRENT_BINARY_DIR}/clang-tidy-result.txt
    COMMENT "Analyzing code by 'clang-tidy'"
)

add_custom_target(codeanalysis DEPENDS cppcheck-result.xml)
