/* By Dylon Edwards
 */

#include <gsi/baryon/apuc.h>
#include <gsi/common_api.h>
#include <gsi/gal-fast-funcs.h>
#include <gsi/libgvml.h>
#include <gsi/libgvml_memory.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "baryon/generators.h"
#include "fixtures.h"

static inline void dma_l2_to_l1(enum gvml_vm_reg vmr) {
  uint8_t bank;

  gal_fast_l2dma_l2_ready_rst_all();
  for (bank = 0; bank < 4; bank++) {
    gvml_load_vmr_16(vmr, bank, bank == (4 - 1), (uint8_t)(bank * 2));
  }
}

static inline void dma_l1_to_l2(enum gvml_vm_reg vmr) {
  uint8_t bank;

  gal_fast_l2dma_l2_ready_rst_all();
  for (bank = 0; bank < 4; bank++) {
    gvml_store_vmr_16(vmr, bank, bank == (4 - 1), (uint8_t)(bank * 2));
  }
}

RC_GTEST_FIXTURE_PROP(BaryonGVMLTest, gvml_store_load_vmr_16, ()) {
  srand(baryon_gen_seed());
  baryon_randomize_vr(&apuc.vrs[0], rand());
  baryon_randomize_vr(&apuc.vrs[1], rand());
  for (size_t i = 0; i < 9; i += 1) {
    baryon_randomize_l1(&apuc.l1[i], rand());
  }
  baryon_foreach_l2_row(row, {
      baryon_randomize_l2(&apuc.l2[row], rand());
  });
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  dma_l1_to_l2(GVML_VM_0);
  dma_l2_to_l1(GVML_VM_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_1);
  baryon_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc.vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc.vrs[GVML_VR16_1][section][plat];
    RC_ASSERT(actual_value == expected_value);
  });
}
