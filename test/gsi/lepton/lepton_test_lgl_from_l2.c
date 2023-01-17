#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_lgl_from_l2.h"

void lepton_test_lgl_from_l2_in_place(lepton_apuc_t *apuc) {
  size_t l2_addr = 0;
  lepton_lgl_from_l2(apuc, l2_addr);
  LEPTON_ASSERT_LGL_EQ(&apuc->lgl, &apuc->l2[l2_addr]);
}

void lepton_test_lgl_from_l2_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  size_t l2_addr = 0;
  lepton_lgl_t *patch = lepton_lgl_from_l2(apuc, l2_addr);
  lepton_patch_lgl(apuc, patch);
  lepton_free_lgl(patch);
  LEPTON_ASSERT_LGL_EQ(&apuc->lgl, &apuc->l2[l2_addr]);
  apuc->in_place = true;
}

void lepton_test_lgl_from_l2(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_lgl_from_l2_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_lgl_from_l2_w_patch);
}
