add_executable(test-lepton
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
  pthread
)

add_subdirectory(gsi)
