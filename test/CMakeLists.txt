add_executable(test-lepton
  test_matvec.cpp
  test_lepton.cpp
)

target_link_libraries(test-lepton PUBLIC
  gsilepton
  gtest
  pthread
)

add_subdirectory(gsi)
