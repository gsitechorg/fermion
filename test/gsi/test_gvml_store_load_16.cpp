#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_memory.h>

#include <gtest/gtest.h>

#include "test_libgvml.h"

TEST_F(LeptonGVMLTest, gvml_store_load_16) {
  lepton_repeatably_randomize_apuc(&apuc);
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_0);
  lepton_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc.vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc.vrs[GVML_VR16_1][section][plat];
    ASSERT_EQ(actual_value, expected_value)
        << "Expected apuc.vrs[0][" << section << "][" << plat << "] to be "
        << expected_value << " but was " << actual_value;
  });
}
