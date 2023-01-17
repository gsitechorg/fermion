#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_l2_from_lgl.h"

void lepton_test_l2_from_lgl_in_place(lepton_apuc_t *apuc) {
  lepton_l2_from_lgl(apuc, 0);
  LEPTON_ASSERT_L2_EQ(&apuc->l2[0], &apuc->lgl);
}

void lepton_test_l2_from_lgl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_l2_patch_t *patch = lepton_l2_from_lgl(apuc, 0);
  lepton_patch_l2(apuc, patch);
  lepton_free_l2_patch(patch);
  LEPTON_ASSERT_L2_EQ(&apuc->l2[0], &apuc->lgl);
  apuc->in_place = true;
}

void lepton_test_l2_from_lgl(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_l2_from_lgl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_l2_from_lgl_w_patch);
}
