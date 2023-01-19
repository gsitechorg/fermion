#include "test_apuc.h"

TEST_F(LeptonAPUCTest, gl_from_rl_in_place) {
  lepton_gl_t *expected = (lepton_gl_t *)malloc(sizeof(lepton_gl_t));
  memset(expected, true, LEPTON_GL_SIZE);
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[plat] &= apuc->rl[section][plat];
  });
  lepton_gl_from_rl(apuc, 0xFFFF);
  LEPTON_ASSERT_GL_EQ(&apuc->gl, expected);
  lepton_free_gl(expected);
}

TEST_F(LeptonAPUCTest, gl_from_rl_w_patch) {
  apuc->in_place = false;
  lepton_gl_t *expected = (lepton_gl_t *)malloc(sizeof(lepton_gl_t));
  memset(expected, true, LEPTON_GL_SIZE);
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[plat] &= apuc->rl[section][plat];
  });
  lepton_gl_t *patch = lepton_gl_from_rl(apuc, 0xFFFF);
  lepton_patch_gl(apuc, patch);
  lepton_free_gl(patch);
  LEPTON_ASSERT_GL_EQ(&apuc->gl, expected);
  lepton_free_gl(expected);
  apuc->in_place = true;
}
