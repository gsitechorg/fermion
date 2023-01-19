#include "test_apuc.h"

TEST_F(LeptonAPUCTest, ggl_from_rl_in_place) {
  lepton_ggl_t *expected = (lepton_ggl_t *)malloc(sizeof(lepton_ggl_t));
  memset(expected, true, LEPTON_GGL_SIZE);
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section / LEPTON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
  });
  lepton_ggl_from_rl(apuc, 0xFFFF);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, expected);
  lepton_free_ggl(expected);
}

TEST_F(LeptonAPUCTest, ggl_from_rl_w_patch) {
  apuc->in_place = false;
  lepton_ggl_t *expected = (lepton_ggl_t *)malloc(sizeof(lepton_ggl_t));
  memset(expected, true, LEPTON_GGL_SIZE);
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section / LEPTON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
  });
  lepton_ggl_t *patch = lepton_ggl_from_rl(apuc, 0xFFFF);
  lepton_patch_ggl(apuc, patch);
  lepton_free_ggl(patch);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, expected);
  lepton_free_ggl(expected);
  apuc->in_place = true;
}
