add_executable(test-lepton
  lepton_test_matvec.c
  lepton_test.c
)

target_link_libraries(test-lepton PUBLIC
  # mcheck
  gsilepton
)

add_subdirectory(gsi)
