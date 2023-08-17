/* By Dylon Edwards
 */

#include <gsi/baryon/apuc.h>
#include <gsi/common_api.h>
#include <gsi/libgvml_memory.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "baryon/generators.h"
#include "fixtures.h"

RC_GTEST_FIXTURE_PROP(BaryonGVMLTest, gvml_store_load_16, ()) {
  srand(baryon_gen_seed());
  baryon_randomize_vr(&apuc.vrs[0], rand());
  baryon_randomize_vr(&apuc.vrs[1], rand());
  for (size_t i = 0; i < 9; i += 1) {
    baryon_randomize_l1(&apuc.l1[i], rand());
  }
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_0);
  baryon_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc.vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc.vrs[GVML_VR16_1][section][plat];
    RC_ASSERT(actual_value == expected_value);
  });
}
