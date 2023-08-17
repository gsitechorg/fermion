/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, ggl_from_rl_and_l1, ()) {
  baryon_sm_t mask = baryon_gen_mask();
  size_t l1_addr = baryon_gen_l1_addr();

  uint32_t ggl_seed = baryon_gen_seed();
  uint32_t rl_seed = baryon_gen_seed();
  uint32_t l1_seed = baryon_gen_seed();

  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);

  baryon_ggl_t *expected = (baryon_ggl_t *)malloc(sizeof(baryon_ggl_t));
  memset(expected, true, BARYON_GGL_SIZE);

  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      (*expected)[section / BARYON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });

  baryon_foreach_l1_group_plat(group, plat, {
    (*expected)[group][plat] &= apuc->l1[l1_addr][group][plat];
  });

  baryon_ggl_from_rl_and_l1(apuc, mask, l1_addr);
  RC_ASSERT(baryon_ggl_eq(&apuc->ggl, expected));

  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);

  apuc->in_place = false;
  baryon_ggl_t *patch = baryon_ggl_from_rl_and_l1(apuc, mask, l1_addr);
  baryon_patch_ggl(apuc, patch);
  baryon_free_ggl(patch);
  RC_ASSERT(baryon_ggl_eq(&apuc->ggl, expected));
  apuc->in_place = true;

  baryon_free_ggl(expected);
}
