target_sources(test-lepton PUBLIC
  lepton_test_gvml_add_u16.c
  lepton_test_gvml_cpy_imm_16.c
  lepton_test_gvml_mul_u16.c
  lepton_test_libgvml.c
)

add_subdirectory(lepton)
