#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_lgl_from_l1.h"

void lepton_test_lgl_from_l1_in_place(lepton_apuc_t *apuc) {
  size_t l1_addr = 0;
  lepton_lgl_from_l1(apuc, l1_addr);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->lgl[lgl_plat];
    bool expected_value = apuc->l1[row][group][l1_plat];
    if (actual_value != expected_value) {
      LEPTON_FAIL_TEST("Expected apuc->lgl[%zu] to be %d but was %d\n",
                       lgl_plat, expected_value, actual_value);
      goto assertion_done;
    }
  });
assertion_done:
  ;;
}

void lepton_test_lgl_from_l1_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  size_t l1_addr = 0;
  lepton_lgl_t *patch = lepton_lgl_from_l1(apuc, l1_addr);
  lepton_patch_lgl(apuc, patch);
  lepton_free_lgl(patch);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->lgl[lgl_plat];
    bool expected_value = apuc->l1[row][group][l1_plat];
    if (actual_value != expected_value) {
      LEPTON_FAIL_TEST("Expected apuc->lgl[%zu] to be %d but was %d\n",
                       lgl_plat, expected_value, actual_value);
      goto assertion_done;
    }
  });
assertion_done:
  apuc->in_place = true;
}

void lepton_test_lgl_from_l1(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_lgl_from_l1_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_lgl_from_l1_w_patch);
}
