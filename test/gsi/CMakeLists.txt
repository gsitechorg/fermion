target_sources(test-baryon PUBLIC
  fixtures.cpp
  test_gvml_init.cpp
  test_gvml_add_u16.cpp
  test_gvml_cpy_imm_16.cpp
  test_gvml_mul_u16.cpp
  test_gvml_store_load_16.cpp
  test_gvml_store_load_vmr_16.cpp
  test_libgal.cpp
)

add_subdirectory(baryon)
