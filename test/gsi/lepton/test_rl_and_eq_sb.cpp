#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rl_and_eq_sb, ()) {
  lepton_sm_t mask = lepton_gen_mask();
  std::vector<size_t> row_nums = lepton_gen_row_nums();
  size_t num_vrs = row_nums.size();
  lepton_vr_t *vrs[num_vrs];

  for (size_t i = 0; i < num_vrs; i += 1) {
    size_t row_num = row_nums[i];
    lepton_vr_t *vr = &apuc->vrs[row_num];
    vrs[i] = vr;
  }

  uint32_t vr_seeds[num_vrs];
  uint32_t rl_seed = lepton_gen_seed();

  for (size_t i = 0; i < num_vrs; i += 1) {
    lepton_vr_t *vr = vrs[i];
    uint32_t vr_seed = lepton_gen_seed();
    lepton_randomize_vr(vr, vr_seed);
    vr_seeds[i] = vr_seed;
  }
  lepton_randomize_rl(&apuc->rl, rl_seed);

  lepton_vr_t *expected = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));

  lepton_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], true, LEPTON_WORDLINE_SIZE);
    lepton_foreach_rl_plat(plat, {
      for (size_t i = 0; i < num_vrs; i += 1) {
        (*expected)[section][plat] &= (*vrs[i])[section][plat];
      }
      (*expected)[section][plat] &= apuc->rl[section][plat];
    });
  });

  lepton_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], LEPTON_WORDLINE_SIZE);
  });

  lepton_rl_and_eq_sb(apuc, mask, vrs, num_vrs);
  RC_ASSERT(lepton_rl_eq(&apuc->rl, expected));

  for (size_t i = 0; i < num_vrs; i += 1) {
    lepton_vr_t *vr = vrs[i];
    uint32_t vr_seed = vr_seeds[i];
    lepton_randomize_vr(vr, vr_seed);
  }
  lepton_randomize_rl(&apuc->rl, rl_seed);

  apuc->in_place = false;
  lepton_wordline_map_t *patch = lepton_rl_and_eq_sb(apuc, mask, vrs, num_vrs);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  RC_ASSERT(lepton_vr_eq(&apuc->rl, expected));
  apuc->in_place = true;

  lepton_free_vr(expected);
}
