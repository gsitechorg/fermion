#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_memory.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "lepton/generators.h"
#include "fixtures.h"

RC_GTEST_FIXTURE_PROP(LeptonGVMLTest, gvml_store_load_16, ()) {
  srand(lepton_gen_seed());
  lepton_randomize_vr(&apuc.vrs[0], rand());
  lepton_randomize_vr(&apuc.vrs[1], rand());
  for (size_t i = 0; i < 9; i += 1) {
    lepton_randomize_l1(&apuc.l1[i], rand());
  }
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_0);
  lepton_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc.vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc.vrs[GVML_VR16_1][section][plat];
    RC_ASSERT(actual_value == expected_value);
  });
}
