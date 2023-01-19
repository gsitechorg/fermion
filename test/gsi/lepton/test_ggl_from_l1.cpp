#include "test_apuc.h"

TEST_F(LeptonAPUCTest, ggl_from_l1_in_place) {
  lepton_ggl_from_l1(apuc, 0);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, &apuc->l1[0]);
}

TEST_F(LeptonAPUCTest, ggl_from_l1_w_patch) {
  apuc->in_place = false;
  lepton_ggl_t *patch = lepton_ggl_from_l1(apuc, 0);
  lepton_patch_ggl(apuc, patch);
  lepton_free_ggl(patch);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, &apuc->l1[0]);
  apuc->in_place = true;
}
