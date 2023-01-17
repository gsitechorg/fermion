#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_l1_from_lgl.h"

void lepton_test_l1_from_lgl_in_place(lepton_apuc_t *apuc) {
  size_t l1_addr = 0;
  lepton_l1_from_lgl(apuc, l1_addr);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->l1[row][group][l1_plat];
    bool expected_value = apuc->lgl[lgl_plat];
    if (actual_value != expected_value) {
      LEPTON_FAIL_TEST("Expected apuc->l1[%zu][%zu][%zu] to be %d but was %d\n",
                       row, group, l1_plat, expected_value, actual_value);
      goto end_of_test;
    }
  });
end_of_test:
  ;;
}

void lepton_test_l1_from_lgl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  size_t l1_addr = 0;
  lepton_l1_patch_t *patch = lepton_l1_from_lgl(apuc, l1_addr);
  lepton_patch_l1(apuc, patch);
  lepton_free_l1_patch(patch);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->l1[row][group][l1_plat];
    bool expected_value = apuc->lgl[lgl_plat];
    if (actual_value != expected_value) {
      LEPTON_FAIL_TEST("Expected apuc->l1[%zu][%zu][%zu] to be %d but was %d\n",
                       row, group, l1_plat, expected_value, actual_value);
      goto end_of_test;
    }
  });
end_of_test:
  apuc->in_place = true;
}

void lepton_test_l1_from_lgl(void) {
  /* LEPTON_RUN_APUC_TEST(lepton_test_l1_from_lgl_in_place); */
  LEPTON_RUN_APUC_TEST(lepton_test_l1_from_lgl_w_patch);
}
