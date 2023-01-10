cmake_minimum_required(VERSION 3.13.4 FATAL_ERROR)
project(lepton LANGUAGES C)


add_library(gsilepton
    src/gsi/lepton/operations.c
    src/gsi/lepton/apuc.c
    src/gsi/libgal.c
    src/gsi/libgvml.c
    src/gsi/libgdl.c
    src/gsi/libsys.c
)
target_include_directories(gsilepton PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
