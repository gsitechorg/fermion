#include "test_apuc.h"

TEST_F(LeptonAPUCTest, l2_from_lgl_in_place) {
  lepton_l2_from_lgl(apuc, 0);
  LEPTON_ASSERT_L2_EQ(&apuc->l2[0], &apuc->lgl);
}

TEST_F(LeptonAPUCTest, l2_from_lgl_w_patch) {
  apuc->in_place = false;
  lepton_l2_patch_t *patch = lepton_l2_from_lgl(apuc, 0);
  lepton_patch_l2(apuc, patch);
  lepton_free_l2_patch(patch);
  LEPTON_ASSERT_L2_EQ(&apuc->l2[0], &apuc->lgl);
  apuc->in_place = true;
}
