#include "lepton_test_apuc.h"
#include "lepton_test_rl_from_sb.h"

void lepton_test_rl_from_3_sbs_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *vr1 = &apuc->vrs[1];
  lepton_vr_t *vr2 = &apuc->vrs[2];
  lepton_vr_t *vr3 = &apuc->vrs[3];
  size_t num_vrs = 3;
  lepton_vr_t *vrs[] = { vr1, vr2, vr3 };
  lepton_vr_t *expected = malloc(sizeof(lepton_vr_t));
  lepton_foreach_vr_section_plat(section, plat, {
    (*expected)[section][plat] = (*vr1)[section][plat]
      & (*vr2)[section][plat]
      & (*vr3)[section][plat];
  });
  lepton_rl_from_sb(apuc, 0xFFFF, vrs, num_vrs);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_vr(expected);
}

void lepton_test_rl_from_3_sbs_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *vr1 = &apuc->vrs[1];
  lepton_vr_t *vr2 = &apuc->vrs[2];
  lepton_vr_t *vr3 = &apuc->vrs[3];
  size_t num_vrs = 3;
  lepton_vr_t *vrs[] = { vr1, vr2, vr3 };
  lepton_vr_t *expected = malloc(sizeof(lepton_vr_t));
  lepton_foreach_vr_section_plat(section, plat, {
    (*expected)[section][plat] = (*vr1)[section][plat]
      & (*vr2)[section][plat]
      & (*vr3)[section][plat];
  });
  lepton_wordline_map_t *patch =
      lepton_rl_from_sb(apuc, 0xFFFF, vrs, num_vrs);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, expected);
  lepton_free_vr(expected);
  apuc->in_place = true;
}

void lepton_test_rl_from_sb_in_place(lepton_apuc_t *apuc) {
  lepton_vr_t *vr = &apuc->vrs[1];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { vr };
  lepton_rl_from_sb(apuc, 0xFFFF, vrs, num_vrs);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, vr);
}

void lepton_test_rl_from_sb_w_patch(lepton_apuc_t *apuc) {
  apuc->in_place = false;
  lepton_vr_t *vr = &apuc->vrs[1];
  size_t num_vrs = 1;
  lepton_vr_t *vrs[] = { vr };
  lepton_wordline_map_t *patch =
      lepton_rl_from_sb(apuc, 0xFFFF, vrs, num_vrs);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  LEPTON_ASSERT_VR_EQ(&apuc->rl, vr);
  apuc->in_place = true;
}

void lepton_test_rl_from_sb(void) {
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_3_sbs_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_3_sbs_w_patch);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_sb_in_place);
  LEPTON_RUN_APUC_TEST(lepton_test_rl_from_sb_w_patch);
}
