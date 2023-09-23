find_program(FORMAT_CPP_PRG NAMES clang-format)
if(NOT FORMAT_CPP_PRG)
    message(FATAL_ERROR "No program 'clang-format' found")
endif()

set(EXCLUDE_PATH
    "-not -path '${CMAKE_BINARY_DIR}/*'"
)

set(FIND_CPP_COMMAND
    "find '${PROJECT_SOURCE_DIR}' -regex '.*\\.\\(c\\|cc\\|cpp\\|cxx\\|h\\|hh\\|hpp\\|hxx\\)$' ${EXCLUDE_PATH}"
)

add_custom_target(
    codeformat
    VERBATIM
    COMMAND bash -c "${FIND_CPP_COMMAND} | xargs -n 1 ${FORMAT_CPP_PRG} -i"
)

add_custom_target(
    formatcheck
    VERBATIM
    COMMAND
        bash -c
        "${FORMAT_CPP_PRG} --version; ${FIND_CPP_COMMAND} | xargs -n 1 -I {} bash -c 'diff -u {} <(${FORMAT_CPP_PRG} {})'"
)