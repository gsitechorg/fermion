/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rl_and_eq_inv_sb, ()) {
  baryon_sm_t mask = baryon_gen_mask();
  std::vector<size_t> row_nums = baryon_gen_row_nums();
  size_t num_vrs = row_nums.size();
  baryon_vr_t *vrs[num_vrs];

  for (size_t i = 0; i < num_vrs; i += 1) {
    size_t row_num = row_nums[i];
    baryon_vr_t *vr = &apuc->vrs[row_num];
    vrs[i] = vr;
  }

  uint32_t vr_seeds[num_vrs];
  uint32_t rl_seed = baryon_gen_seed();

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = baryon_gen_seed();
    baryon_randomize_vr(vr, vr_seed);
    vr_seeds[i] = vr_seed;
  }
  baryon_randomize_rl(&apuc->rl, rl_seed);

  baryon_vr_t *expected = (baryon_vr_t *)malloc(sizeof(baryon_vr_t));

  baryon_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], false, BARYON_WORDLINE_SIZE);
    baryon_foreach_rl_plat(plat, {
      for (size_t i = 0; i < num_vrs; i += 1) {
        (*expected)[section][plat] |= !(*vrs[i])[section][plat];
      }
      (*expected)[section][plat] &= apuc->rl[section][plat];
    });
  });

  baryon_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], BARYON_WORDLINE_SIZE);
  });

  baryon_rl_and_eq_inv_sb(apuc, mask, vrs, num_vrs);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = vr_seeds[i];
    baryon_randomize_vr(vr, vr_seed);
  }
  baryon_randomize_rl(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_wordline_map_t *patch =
    baryon_rl_and_eq_inv_sb(apuc, mask, vrs, num_vrs);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  RC_ASSERT(baryon_vr_eq(&apuc->rl, expected));
  apuc->in_place = true;

  baryon_free_vr(expected);
}
