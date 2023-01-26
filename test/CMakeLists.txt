add_executable(test-baryon
  rapidcheck_parser.cpp
  test_matvec.cpp
  test_baryon.cpp
)

target_include_directories(test-baryon PUBLIC
  "$ENV{CONDA_PREFIX}/include"
)

target_link_directories(test-baryon PUBLIC
  "$ENV{CONDA_PREFIX}/lib"
)

target_link_libraries(test-baryon PUBLIC
  gsi-baryon-gvml
  gsi-baryon-sys
  gtest
  rapidcheck
  yaml-cpp
  stdc++fs
  pthread
  atomic
  m
  dl
)

add_subdirectory(gsi)

# ==============================================================================
# Copy rapidcheck.yml to the testing dir when it is changed, even if test-baryon
# is not built.

add_custom_target(copy-rapidcheck-config ALL
  COMMAND
  "${CMAKE_COMMAND}" -E copy
  "${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck.yml"
  "${CMAKE_CURRENT_BINARY_DIR}/rapidcheck.yml"
)

add_dependencies(test-baryon copy-rapidcheck-config)
