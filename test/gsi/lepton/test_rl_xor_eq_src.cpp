#include "test_apuc.h"

TEST_F(LeptonAPUCTest, rl_xor_eq_src_nrl_in_place) {
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_vr_t *expected = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section][plat] =
      apuc->rl[section][plat] ^ (*nrl)[section][plat];
  });
  lepton_rl_xor_eq_src(apuc, 0xFFFF, nrl, LEPTON_SRC_NRL);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_rl(expected);
  lepton_free_rl(nrl);
}

TEST_F(LeptonAPUCTest, rl_xor_eq_src_nrl_w_patch) {
  apuc->in_place = false;
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_vr_t *expected = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section][plat] =
        apuc->rl[section][plat] ^ (*nrl)[section][plat];
  });
  lepton_wordline_map_t *patch =
      lepton_rl_xor_eq_src(apuc, 0xFFFF, nrl, LEPTON_SRC_NRL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_rl(expected);
  lepton_free_vr(nrl);
  apuc->in_place = true;
}

TEST_F(LeptonAPUCTest, rl_xor_eq_src_gl_in_place) {
  lepton_gl_t *gl = &apuc->gl;
  lepton_vr_t *expected = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section][plat] = apuc->rl[section][plat] ^ (*gl)[plat];
  });
  lepton_rl_xor_eq_src(apuc, 0xFFFF, gl, LEPTON_SRC_GL);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_rl(expected);
}

TEST_F(LeptonAPUCTest, rl_xor_eq_src_gl_w_patch) {
  apuc->in_place = false;
  lepton_gl_t *gl = &apuc->gl;
  lepton_vr_t *expected = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section][plat] = apuc->rl[section][plat] ^ (*gl)[plat];
  });
  lepton_wordline_map_t *patch =
      lepton_rl_xor_eq_src(apuc, 0xFFFF, gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_rl(expected);
  apuc->in_place = true;
}
