#include <gsi/lepton/apuc.h>
#include <gsi/libgvml.h>
#include <gsi/libgvml_memory.h>
#include <gsi/gal-fast-funcs.h>

#include "lepton_test_gvml_store_load_vmr_16.h"
#include "lepton_test_libgvml.h"

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

void lepton_test_gvml_store_load_vmr_16() {
  lepton_repeatably_randomize_apuc(apuc);
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  dma_l1_to_l2(GVML_VM_0);
  dma_l2_to_l1(GVML_VM_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_1);
  lepton_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc->vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc->vrs[GVML_VR16_1][section][plat];
    if (actual_value != expected_value) {
      LEPTON_FAIL_TEST("Expected apuc->vrs[0][%zu][%zu] to be %d but was %d\n",
                       section, plat, expected_value, actual_value);
      goto assertion_done;
    }
  });
assertion_done:
  ;;
}
