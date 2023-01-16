#include <stdio.h>

#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_element_wise.h>
#include <gsi/libgvml.h>

#include "lepton_test_libgvml.h"
#include "lepton_test_gvml_cpy_imm_16.h"

void lepton_test_gvml_cpy_imm_16() {
  gvml_cpy_imm_16(0, 0xBEEF);
  lepton_foreach_vr_plat(plat, {
    uint16_t value = 0x0000;
    lepton_foreach_vr_section(section, {
      value |= (apuc->vrs[0][section][plat] << section);
    });
    if (value != 0xBEEF) {
      printf("%s:%d: Expected apuc->vrs[0][:][%zu] to be 0xBEEF but was 0x%04X\n",
             __FILE__, __LINE__, plat, value);
      LEPTON_TEST_PASSED = false;
      break;
    }
  });
}
