#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_element_wise.h>

#include "lepton_test_libgvml.h"
#include "lepton_test_gvml_add_u16.h"

void lepton_test_gvml_add_u16() {
  lepton_repeatably_randomize_apuc(apuc);
  gvml_add_u16(0, 1, 2);
  lepton_foreach_vr_plat(plat, {
    uint16_t lhs = 0x0000;
    uint16_t rhs = 0x0000;
    uint16_t expected = 0x0000;
    uint16_t actual = 0x0000;
    lepton_foreach_vr_section(section, {
      lhs |= (apuc->vrs[1][section][plat] << section);
      rhs |= (apuc->vrs[2][section][plat] << section);
      actual |= (apuc->vrs[0][section][plat] << section);
    });
    expected = (uint16_t) (((uint32_t) lhs + (uint32_t) rhs) & 0xFFFF);
    if (actual != expected) {
      printf("%s:%d: Expected apuc->vrs[0][:][%zu] = (0x%04X + 0x%04X) to be "
             "0x%04X but was 0x%04X\n",
             __FILE__, __LINE__, plat, lhs, rhs, expected, actual);
      LEPTON_TEST_PASSED = false;
      break;
    }
  });
}
