#include "test_apuc.h"

TEST_F(LeptonAPUCTest, lgl_from_l2_in_place) {
  size_t l2_addr = 0;
  lepton_lgl_from_l2(apuc, l2_addr);
  LEPTON_ASSERT_LGL_EQ(&apuc->lgl, &apuc->l2[l2_addr]);
}

TEST_F(LeptonAPUCTest, lgl_from_l2_w_patch) {
  apuc->in_place = false;
  size_t l2_addr = 0;
  lepton_lgl_t *patch = lepton_lgl_from_l2(apuc, l2_addr);
  lepton_patch_lgl(apuc, patch);
  lepton_free_lgl(patch);
  LEPTON_ASSERT_LGL_EQ(&apuc->lgl, &apuc->l2[l2_addr]);
  apuc->in_place = true;
}
