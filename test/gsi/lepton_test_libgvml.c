#include "lepton_test_libgvml.h"
#include "lepton_test_gvml_add_u16.h"
#include "lepton_test_gvml_cpy_imm_16.h"
#include "lepton_test_gvml_mul_u16.h"
#include "lepton_test_gvml_store_load_16.h"
#include "lepton_test_gvml_store_load_vmr_16.h"

void lepton_test_libgvml() {
  LEPTON_RUN_GVML_TEST(lepton_test_gvml_add_u16);
  LEPTON_RUN_GVML_TEST(lepton_test_gvml_cpy_imm_16);
  LEPTON_RUN_GVML_TEST(lepton_test_gvml_mul_u16);
  LEPTON_RUN_GVML_TEST(lepton_test_gvml_store_load_16);
  LEPTON_RUN_GVML_TEST(lepton_test_gvml_store_load_vmr_16);
}
