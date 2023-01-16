#include "lepton_test_apuc.h"
#include "lepton_test_rl_from_src.h"

void lepton_test_rl_from_src_inv_rl_in_place(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_rl = lepton_inv_rl(apuc);
  lepton_rl_from_src(apuc, 0xFFFF, inv_rl, LEPTON_SRC_INV_RL);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, inv_rl);
  lepton_free_vr(inv_rl);
}

void lepton_test_rl_from_src_inv_rl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_rl_t *inv_rl = lepton_inv_rl(apuc);
  lepton_wordline_map_t *patch =
      lepton_rl_from_src(apuc, 0xFFFF, inv_rl, LEPTON_SRC_INV_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, inv_rl);
  lepton_free_vr(inv_rl);
  apuc->in_place = true;
}

void lepton_test_rl_from_src(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_inv_rl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_inv_rl_w_patch);
}
