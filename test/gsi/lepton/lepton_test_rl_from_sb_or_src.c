#include "lepton_test_apuc.h"
#include "lepton_test_rl_from_sb_or_src.h"

void lepton_test_rl_from_sb_or_src_ggl_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *vr = &apuc->vrs[1];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { vr };
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_vr_t *expected = malloc(sizeof(lepton_vr_t));
  lepton_foreach_vr_section_plat(section, plat, {
    (*expected)[section][plat] =
      (*vr)[section][plat] | (*ggl)[section / LEPTON_NUM_GROUPS][plat];
  });
  lepton_rl_from_sb_or_src(apuc, 0xFFFF, vrs, num_vrs, ggl, LEPTON_SRC_GGL);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_vr(expected);
}

void lepton_test_rl_from_sb_or_src_ggl_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *vr = &apuc->vrs[1];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { vr };
  lepton_ggl_t *ggl = &apuc->ggl;
  lepton_vr_t *expected = malloc(sizeof(lepton_vr_t));
  lepton_foreach_vr_section_plat(section, plat, {
    (*expected)[section][plat] =
        (*vr)[section][plat] | (*ggl)[section / LEPTON_NUM_GROUPS][plat];
  });
  lepton_wordline_map_t *patch =
    lepton_rl_from_sb_or_src(apuc, 0xFFFF, vrs, num_vrs, ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_vr(expected);
  apuc->in_place = true;
}

void lepton_test_rl_from_sb_or_src(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_sb_or_src_ggl_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_sb_or_src_ggl_w_patch);
}
