#include <gsi/lepton/apuc.h>
#include <gsi/libgvml_memory.h>

#include "lepton_test_libgvml.h"
#include "lepton_test_gvml_store_load_16.h"

void lepton_test_gvml_store_load_16() {
  lepton_repeatably_randomize_apuc(&apuc);
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_0);
  lepton_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc.vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc.vrs[GVML_VR16_1][section][plat];
    if (actual_value != expected_value) {
      LEPTON_FAIL_TEST("Expected apuc.vrs[0][%zu][%zu] to be %d but was %d\n",
                       section, plat, expected_value, actual_value);
      goto assertion_done;
    }
  });
assertion_done:
  ;;
}
