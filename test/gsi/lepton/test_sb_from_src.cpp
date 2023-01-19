#include "test_apuc.h"

TEST_F(LeptonAPUCTest, sb_from_src_rl_in_place) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *rl = &apuc->rl;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, rl, LEPTON_SRC_RL);
  LEPTON_ASSERT_VR_EQ(out, rl);
}

TEST_F(LeptonAPUCTest, sb_from_src_rl_w_patch) {
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

TEST_F(LeptonAPUCTest, sb_from_src_nrl_in_place) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, nrl, LEPTON_SRC_NRL);
  LEPTON_ASSERT_VR_EQ(out, nrl);
  lepton_free_rl(nrl);
}

TEST_F(LeptonAPUCTest, sb_from_src_nrl_w_patch) {
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

TEST_F(LeptonAPUCTest, sb_from_src_srl_in_place) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rl_t *srl = lepton_srl(apuc);
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, srl, LEPTON_SRC_SRL);
  LEPTON_ASSERT_VR_EQ(out, srl);
  lepton_free_rl(srl);
}

TEST_F(LeptonAPUCTest, sb_from_src_srl_w_patch) {
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

TEST_F(LeptonAPUCTest, sb_from_src_gl_in_place) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { out };
  lepton_gl_t *gl = &apuc->gl;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, gl, LEPTON_SRC_GL);
  LEPTON_ASSERT_VR_EQ_GL(out, gl);
}

TEST_F(LeptonAPUCTest, sb_from_src_gl_w_patch) {
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

TEST_F(LeptonAPUCTest, sb_from_src_ggl_in_place) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, ggl, LEPTON_SRC_GGL);
  LEPTON_ASSERT_VR_EQ_GGL(out, ggl);
}

TEST_F(LeptonAPUCTest, sb_from_src_ggl_w_patch) {
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

TEST_F(LeptonAPUCTest, sb_from_src_rsp16_in_place) {
  lepton_vr_t *out = &apuc->vrs[0];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = {out};
  lepton_rsp16_t *rsp16 = &apuc->rsp16;
  lepton_sb_from_src(apuc, 0xFFFF, vrs, num_vrs, rsp16, LEPTON_SRC_RSP16);
  LEPTON_ASSERT_VR_EQ_RSP16(out, rsp16);
}

TEST_F(LeptonAPUCTest, sb_from_src_rsp16_w_patch) {
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
