cmake_minimum_required(VERSION 3.25.1 FATAL_ERROR)
project(baryon
  VERSION 1.1.1
  DESCRIPTION "C backend for Belex."
  HOMEPAGE_URL "https://bitbucket.org/gsitech/fermion"
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build testing suite" ON)

find_program(BELEX_AOT belex-aot)
message("belex-aot: ${BELEX_AOT}")

add_custom_command(
    OUTPUT
        "${CMAKE_BINARY_DIR}/gensrc/gsi/gvml_fragments.c"
        "${CMAKE_BINARY_DIR}/gensrc/gsi/gvml_fragments.h"
    COMMAND "${BELEX_AOT}"
        --source-file "${CMAKE_BINARY_DIR}/gensrc/gsi/gvml_fragments.c"
        --header-file "${CMAKE_BINARY_DIR}/gensrc/gsi/gvml_fragments.h"
        --target baryon
        --no-uniquify-nyms
        --explicit-frags-only
        "${CMAKE_SOURCE_DIR}/src/gsi/fragments.py"
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS
        "${CMAKE_SOURCE_DIR}/src/gsi/fragments.py"
    VERBATIM
)

add_library(gsi-baryon-sys
    src/gsi/baryon/operations.c
    src/gsi/baryon/fifo.c
    src/gsi/baryon/apuc.c
    src/gsi/baryon/seu_layer.c
    src/gsi/common_api.c
    src/gsi/libapl.c
    src/gsi/libgal.c
    src/gsi/libgdl.c
    src/gsi/libsys.c
    src/gsi/gsi_sim_config.c
)

add_library(gsi-baryon-gvml
  "${CMAKE_BINARY_DIR}/gensrc/gsi/gvml_fragments.c"
  src/gsi/libgvml.c
  src/gsi/rsp.c
)

target_include_directories(gsi-baryon-sys PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_BINARY_DIR}/gensrc"
)

target_include_directories(gsi-baryon-gvml PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_BINARY_DIR}/gensrc"
)

install(TARGETS gsi-baryon-sys gsi-baryon-gvml
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
