cmake_minimum_required(VERSION 3.25.1 FATAL_ERROR)
project(lepton LANGUAGES C CXX)

option(BUILD_TESTS "Build testing suite" ON)

find_program(BELEX_AOT belex-aot)
message("belex-aot: ${BELEX_AOT}")

add_custom_command(
    OUTPUT
        "${CMAKE_BINARY_DIR}/gensrc/gsi/lepton/gvml_fragments.c"
        "${CMAKE_BINARY_DIR}/gensrc/gsi/lepton/gvml_fragments.h"
    COMMAND "${BELEX_AOT}"
        -O0
        --source-file "${CMAKE_BINARY_DIR}/gensrc/gsi/lepton/gvml_fragments.c"
        --header-file "${CMAKE_BINARY_DIR}/gensrc/gsi/lepton/gvml_fragments.h"
        --target lepton
        --no-uniquify-nyms
        "${CMAKE_SOURCE_DIR}/src/gsi/lepton/fragments.py"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/src/gsi/lepton/fragments.py"
    VERBATIM
)

add_library(gsilepton
    src/gsi/lepton/operations.c
    src/gsi/lepton/apuc.c
    src/gsi/lepton/seu_layer.c
    "${CMAKE_BINARY_DIR}/gensrc/gsi/lepton/gvml_fragments.c"
    src/gsi/libapl.c
    src/gsi/libgal.c
    src/gsi/libgvml.c
    src/gsi/libgdl.c
    src/gsi/libsys.c
)
target_include_directories(gsilepton PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_BINARY_DIR}/gensrc"
)

install(TARGETS gsilepton
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)
install(
    FILES ${HEADERS}
    DESTINATION include/gsi/
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/gsi
        DESTINATION include
        FILES_MATCHING PATTERN "*.h"
)



message("Configuration results")
message("---------------------")
message("C compiler      : ${CMAKE_C_COMPILER}")
message("Build type: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("C compiler flags      : ${CMAKE_C_FLAGS_DEBUG}")
else ()
    message("C compiler flags      : ${CMAKE_C_FLAGS_RELEASE}")
endif ()
message("Installation prefix: ${CMAKE_INSTALL_PREFIX}")

if(BUILD_TESTS)
    add_subdirectory(test)
endif()
