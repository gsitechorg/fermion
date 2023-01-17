#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_l1_from_ggl.h"

void lepton_test_l1_from_ggl_in_place(lepton_apuc_t *apuc) {
  lepton_l1_from_ggl(apuc, 0);
  LEPTON_ASSERT_L1_EQ(&apuc->l1[0], &apuc->ggl);
}

void lepton_test_l1_from_ggl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_l1_patch_t *patch = lepton_l1_from_ggl(apuc, 0);
  lepton_patch_l1(apuc, patch);
  lepton_free_l1_patch(patch);
  LEPTON_ASSERT_L1_EQ(&apuc->l1[0], &apuc->ggl);
  apuc->in_place = true;
}

void lepton_test_l1_from_ggl(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_l1_from_ggl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_l1_from_ggl_w_patch);
}
