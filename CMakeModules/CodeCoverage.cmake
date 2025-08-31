set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1 -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O1 -fprofile-arcs -ftest-coverage")

find_program(GCOV_PATH gcov)
find_program(GCOVR_PATH gcovr)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)
find_program(LCOV_COBERTURA_PATH lcov_cobertura)
if(NOT GCOV_PATH)
    message(FATAL_ERROR "gcov not found! Aborting...")
endif()
if(NOT GCOVR_PATH)
    message(FATAL_ERROR "gcovr not found! Aborting...")
endif()
if(NOT LCOV_PATH)
    message(FATAL_ERROR "lcov not found! Aborting...")
endif()
if(NOT GENHTML_PATH)
    message(FATAL_ERROR "genhtml not found! Aborting...")
endif()

if(LCOV_COBERTURA_PATH)
    set(LCOV_COBERTURA_COMMAND ${LCOV_COBERTURA_PATH})
else()
    find_package(Python3 REQUIRED COMPONENTS Interpreter)
    set(LCOV_COBERTURA_COMMAND ${Python3_EXECUTABLE} -m lcov_cobertura)
endif()

function(setup_coverage_target)
    set(COVERAGE_CLEAN coverage-clean)
    set(COVERAGE_TEST coverage-test)
    set(COVERAGE_TARGET coverage)

    set(COVERAGE_OUTPUT_DIRECTORY coverage_results)
    set(GRAFANA_OUTPUT_NAME "coverage_results.txt")

    # Remove user defined pattern from report if the pattern was given
    set(COVERAGE_EXCLUDE_PATTERN "${PROJECT_BINARY_DIR}/*")
    list(APPEND COVERAGE_EXCLUDE_PATTERN "*/test/*")
    if(COVERAGE_EXCLUDE)
        foreach(exclude IN LISTS COVERAGE_EXCLUDE)
            list(APPEND COVERAGE_EXCLUDE_PATTERN "${exclude}")
        endforeach()
    endif()

    set(LCOV_OPTIONS --rc lcov_branch_coverage=1 --gcov-tool ${GCOV_PATH} --quiet)
    set(LCOV_DIRS --base-directory ${PROJECT_SOURCE_DIR} --directory .)

    # Generate list of excluded files for GCOVR
    set(GCOVR_EXCLUDED_FILES)
    foreach(exclude IN LISTS COVERAGE_EXCLUDE_PATTERN)
        file(
            GLOB_RECURSE
            files
            "*.cpp"
            "*.c"
            "*.cxx"
            "*.c++"
            "*.hpp"
            "*.h"
            "*.hxx"
            "*.h++"
        )
        # Patch glob string to turn it into regex
        string(REPLACE "*" ".*" exclude ${exclude})
        string(REPLACE "?" "." exclude ${exclude})

        if(files)
            list(FILTER files INCLUDE REGEX ${exclude})
            list(APPEND GCOVR_EXCLUDED_FILES ${files})
        endif()
    endforeach()

    list(TRANSFORM COVERAGE_EXTRACT_FOR_GCOVR PREPEND "--filter;")
    list(TRANSFORM GCOVR_EXCLUDED_FILES PREPEND "--exclude;")

    set(GCOVR_PARAMS --root ${CMAKE_CURRENT_SOURCE_DIR} --print-summary
                     ${COVERAGE_EXTRACT_FOR_GCOVR} ${GCOVR_EXCLUDED_FILES}
    )

    add_custom_target(
        ${COVERAGE_CLEAN}
        # Cleanup lcov
        COMMAND ${LCOV_PATH} ${LCOV_OPTIONS} --zerocounters --directory .
                # Cleanup generated code coverage of grafana
        COMMAND ${CMAKE_COMMAND} -E remove ${GRAFANA_OUTPUT_NAME}
                # Create baseline to make sure untouched files show up in the report
        COMMAND ${LCOV_PATH} ${LCOV_OPTIONS} --capture --no-external --initial ${LCOV_DIRS}
                --output-file coverage.base.info
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        VERBATIM
        COMMENT "Clean coverage"
    )

    add_custom_target(
        ${COVERAGE_TEST}
        COMMAND ${CMAKE_CTEST_COMMAND} --extra-verbose --output-on-failure --stop-on-failure
        COMMENT "Executing tests for coverage"
    )

    add_custom_target(
        ${COVERAGE_TARGET}
        # Capturing lcov counters and generating report
        COMMAND
            ${LCOV_PATH} ${LCOV_OPTIONS} --capture --no-external ${LCOV_DIRS} --output-file
            coverage.run.info
            # add baseline counters
        COMMAND ${LCOV_PATH} ${LCOV_OPTIONS} --add-tracefile coverage.base.info --add-tracefile
                coverage.run.info --output-file coverage.total.info
        COMMAND ${LCOV_PATH} ${LCOV_OPTIONS} --remove coverage.total.info
                ${COVERAGE_EXCLUDE_PATTERN} --output-file coverage.info
        COMMAND
            ${GENHTML_PATH} --title ${PROJECT_NAME} --prefix ${PROJECT_SOURCE_DIR} --rc
            genhtml_branch_coverage=1 --demangle-cpp --quiet --output-directory
            ${COVERAGE_OUTPUT_DIRECTORY} coverage.info
            # Generates code coverage for Cobertura
        COMMAND ${LCOV_COBERTURA_COMMAND} -b ${PROJECT_SOURCE_DIR} -o coverage.xml coverage.info
                # Generates Code Coverage for Grafana Dashboard.
        COMMAND ${GCOVR_PATH} ${CMAKE_CURRENT_BINARY_DIR} ${GCOVR_PARAMS} --output
                ${GRAFANA_OUTPUT_NAME}
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
        VERBATIM
        COMMENT "Processing code coverage counters and generating report."
    )

    add_dependencies(${COVERAGE_TEST} ${COVERAGE_CLEAN})
    add_dependencies(${COVERAGE_TARGET} ${COVERAGE_TEST})
endfunction()

setup_coverage_target(EXTRACT_FOR_GCOVR "${PROJECT_SOURCE_DIR}/src")
