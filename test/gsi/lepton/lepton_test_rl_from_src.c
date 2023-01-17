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

void lepton_test_rl_from_src_ggl_in_place(lepton_apuc_t *apuc) {
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_rl_from_src(apuc, 0xFFFF, ggl, LEPTON_SRC_GGL);
  LEPTON_ASSERT_VR_EQ_GGL(&apuc->rl, ggl);
}

void lepton_test_rl_from_src_ggl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_wordline_map_t *patch =
      lepton_rl_from_src(apuc, 0xFFFF, ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ_GGL(&apuc->rl, ggl);
  apuc->in_place = true;
}

void lepton_test_rl_from_src_gl_in_place(lepton_apuc_t *apuc) {
  lepton_gl_t *gl = &apuc->gl;
  lepton_rl_from_src(apuc, 0xFFFF, gl, LEPTON_SRC_GL);
  LEPTON_ASSERT_VR_EQ_GL(&apuc->rl, gl);
}

void lepton_test_rl_from_src_gl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_gl_t *gl = &apuc->gl;
  lepton_wordline_map_t *patch =
      lepton_rl_from_src(apuc, 0xFFFF, gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ_GL(&apuc->rl, gl);
  apuc->in_place = true;
}

void lepton_test_rl_from_src(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_inv_rl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_inv_rl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_ggl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_gl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_gl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_src_ggl_w_patch);
}
