#include <stdint.h>

#include "lepton_test_libgvml.h"
#include "lepton_test_libgal.h"

void lepton_test_gal_mem_to_l2_to_mem() {
  uint16_t *p = malloc(LEPTON_NUM_PLATS_PER_APUC * sizeof(uint16_t));
  for (size_t i = 0; i < LEPTON_NUM_PLATS_PER_APUC; i += 1) {
    p[i] = (i & 0xFFFF);
  }
  free(p);
}

void lepton_test_libgal() {
  LEPTON_RUN_GVML_TEST(lepton_test_gal_mem_to_l2_to_mem);
}
