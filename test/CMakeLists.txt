add_executable(test-lepton
  lepton_test.c
)

target_link_libraries(test-lepton PUBLIC
  gsilepton
)

add_subdirectory(gsi)
