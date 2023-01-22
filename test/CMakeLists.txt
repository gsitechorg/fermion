add_executable(test-lepton
  lepton_rapidcheck_parser.cpp
  test_matvec.cpp
  test_lepton.cpp
)

target_include_directories(test-lepton PUBLIC
  "$ENV{CONDA_PREFIX}/include"
)

target_link_directories(test-lepton PUBLIC
  "$ENV{CONDA_PREFIX}/lib"
)

target_link_libraries(test-lepton PUBLIC
  gsilepton
  gtest
  rapidcheck
  yaml-cpp
  stdc++fs
  pthread
)

add_subdirectory(gsi)

# ==============================================================================
# Copy rapidcheck.yml to the testing dir when it is changed, even if test-lepton
# is not built.

add_custom_target(copy-rapidcheck-config ALL
  COMMAND
  "${CMAKE_COMMAND}" -E copy
  "${CMAKE_CURRENT_SOURCE_DIR}/rapidcheck.yml"
  "${CMAKE_CURRENT_BINARY_DIR}/rapidcheck.yml"
)

add_dependencies(test-lepton copy-rapidcheck-config)
