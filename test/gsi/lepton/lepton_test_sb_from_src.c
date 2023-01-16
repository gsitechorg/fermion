#include "lepton_test_apuc.h"
#include "lepton_test_sb_from_src.h"

void lepton_test_sb_from_src_rl_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *rl = &apuc->rl;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, rl, LEPTON_SRC_RL);
  LEPTON_ASSERT_VR_EQ(out, rl);
}

void lepton_test_sb_from_src_rl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { out };
  lepton_rl_t *rl = &apuc->rl;
  lepton_wordline_map_t *patch =
    lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(out, rl);
  apuc->in_place = true;
}

void lepton_test_sb_from_src_nrl_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, nrl, LEPTON_SRC_NRL);
  LEPTON_ASSERT_VR_EQ(out, nrl);
  lepton_free_rl(nrl);
}

void lepton_test_sb_from_src_nrl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_wordline_map_t *patch =
      lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, nrl, LEPTON_SRC_NRL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(out, nrl);
  lepton_free_rl(nrl);
  apuc->in_place = true;
}

void lepton_test_sb_from_src_srl_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *srl = lepton_srl(apuc);
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, srl, LEPTON_SRC_SRL);
  LEPTON_ASSERT_VR_EQ(out, srl);
  lepton_free_rl(srl);
}

void lepton_test_sb_from_src_srl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *srl = lepton_srl(apuc);
  lepton_wordline_map_t *patch =
      lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, srl, LEPTON_SRC_SRL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(out, srl);
  lepton_free_rl(srl);
  apuc->in_place = true;
}

void lepton_test_sb_from_src_gl_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { out };
  lepton_gl_t *gl = &apuc->gl;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, gl, LEPTON_SRC_GL);
  LEPTON_ASSERT_VR_EQ_GL(out, gl);
}

void lepton_test_sb_from_src_gl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { out };
  lepton_gl_t *gl = &apuc->gl;
  lepton_wordline_map_t *patch =
      lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ_GL(out, gl);
  apuc->in_place = true;
}

void lepton_test_sb_from_src_ggl_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, ggl, LEPTON_SRC_GGL);
  LEPTON_ASSERT_VR_EQ_GGL(out, ggl);
}

void lepton_test_sb_from_src_ggl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_wordline_map_t *patch =
      lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ_GGL(out, ggl);
  apuc->in_place = true;
}

void lepton_test_sb_from_src_rsp16_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rsp16_t *rsp16 = &apuc->rsp16;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, rsp16, LEPTON_SRC_RSP16);
  LEPTON_ASSERT_VR_EQ_RSP16(out, rsp16);
}

void lepton_test_sb_from_src_rsp16_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rsp16_t *rsp16 = &apuc->rsp16;
  lepton_wordline_map_t *patch =
      lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ_RSP16(out, rsp16);
  apuc->in_place = true;
}

void lepton_test_sb_from_src() {
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_rl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_rl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_nrl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_nrl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_srl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_srl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_ggl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_ggl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_gl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_gl_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_rsp16_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_sb_from_src_rsp16_w_patch);
}
