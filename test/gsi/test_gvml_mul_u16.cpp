#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_element_wise.h>

#include <gtest/gtest.h>

#include "test_libgvml.h"

TEST_F(LeptonGVMLTest, gvml_mul_u16) {
  lepton_repeatably_randomize_apuc(&apuc);
  gvml_mul_u16(GVML_VR16_0, GVML_VR16_1, GVML_VR16_2);
  lepton_foreach_vr_plat(plat, {
    uint16_t lhs = 0x0000;
    uint16_t rhs = 0x0000;
    uint16_t expected = 0x0000;
    uint16_t actual = 0x0000;
    lepton_foreach_vr_section(section, {
      lhs |= (apuc.vrs[GVML_VR16_1][section][plat] << section);
      rhs |= (apuc.vrs[GVML_VR16_2][section][plat] << section);
      actual |= (apuc.vrs[GVML_VR16_0][section][plat] << section);
    });
    expected = (uint16_t)(((uint32_t)lhs * (uint32_t)rhs) & 0xFFFF);
    ASSERT_EQ(actual, expected)
        << "Expected apuc.vrs[0][:][" << plat << "] = (" << lhs << " * " << rhs
        << ") to be " << expected << " but was " << actual;
  });
}
