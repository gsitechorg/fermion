#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_element_wise.h>
#include <gsi/libgvml.h>

#include <gtest/gtest.h>

#include "test_libgvml.h"

TEST_F(LeptonGVMLTest, gvml_cpy_imm_16) {
  gvml_cpy_imm_16(GVML_VR16_0, 0xBEEF);
  lepton_foreach_vr_plat(plat, {
    uint16_t value = 0x0000;
    lepton_foreach_vr_section(section, {
      value |= (apuc.vrs[GVML_VR16_0][section][plat] << section);
    });
    ASSERT_EQ(value, 0xBEEF) << "Expected apuc.vrs[0][:][" << plat
                             << "] to be 0xBEEF but was " << value;
  });
}
