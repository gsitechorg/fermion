#include <string.h>

#include "lepton_test_apuc.h"
#include "lepton_test_ggl_from_rl.h"

void lepton_test_ggl_from_rl_in_place(lepton_apuc_t *apuc) {
  lepton_ggl_t *expected = malloc(sizeof(lepton_ggl_t));
  memset(expected, true, LEPTON_GGL_SIZE);
  lepton_foreach_rl_section_plat(section, plat, {
    (*expected)[section / LEPTON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
  });
  lepton_ggl_from_rl(apuc, 0xFFFF);
  LEPTON_ASSERT_GGL_EQ(&apuc->ggl, expected);
  lepton_free_ggl(expected);
}

void lepton_test_ggl_from_rl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_ggl_t *expected = malloc(sizeof(lepton_ggl_t));
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

void lepton_test_ggl_from_rl(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_ggl_from_rl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_ggl_from_rl_w_patch);
}
