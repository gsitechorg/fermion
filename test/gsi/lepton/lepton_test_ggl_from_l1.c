#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_ggl_from_l1.h"

void lepton_test_ggl_from_l1_in_place(lepton_apuc_t *apuc) {
  lepton_ggl_from_l1(apuc, 0);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, &apuc->l1[0]);
}

void lepton_test_ggl_from_l1_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_ggl_t *patch = lepton_ggl_from_l1(apuc, 0);
  lepton_patch_ggl(apuc, patch);
  lepton_free_ggl(patch);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, &apuc->l1[0]);
  apuc->in_place = true;
}

void lepton_test_ggl_from_l1(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_ggl_from_l1_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_ggl_from_l1_w_patch);
}
