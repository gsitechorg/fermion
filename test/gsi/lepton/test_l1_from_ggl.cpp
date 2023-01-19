#include "test_apuc.h"

TEST_F(LeptonAPUCTest, l1_from_ggl_in_place) {
  lepton_l1_from_ggl(apuc, 0);
  LEPTON_ASSERT_L1_EQ(&apuc->l1[0], &apuc->ggl);
}

TEST_F(LeptonAPUCTest, l1_from_ggl_w_patch) {
  apuc->in_place = false;
  lepton_l1_patch_t *patch = lepton_l1_from_ggl(apuc, 0);
  lepton_patch_l1(apuc, patch);
  lepton_free_l1_patch(patch);
  LEPTON_ASSERT_L1_EQ(&apuc->l1[0], &apuc->ggl);
  apuc->in_place = true;
}
