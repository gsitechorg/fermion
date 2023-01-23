#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, set_rl, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_vr(&apuc->rl, rl_seed);

  baryon_rl_t *expected = (baryon_rl_t *) malloc(sizeof(baryon_rl_t));
  baryon_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], true, BARYON_WORDLINE_SIZE);
  });
  baryon_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], BARYON_WORDLINE_SIZE);
  });

  baryon_set_rl(apuc, mask, true);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));

  baryon_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_wordline_map_t *patch = baryon_set_rl(apuc, mask, true);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));
  apuc->in_place = true;

  baryon_free_rl(expected);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, reset_rl, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_vr(&apuc->rl, rl_seed);

  baryon_rl_t *expected = (baryon_rl_t *)malloc(sizeof(baryon_rl_t));
  baryon_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], false, BARYON_WORDLINE_SIZE);
  });
  baryon_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], BARYON_WORDLINE_SIZE);
  });

  baryon_set_rl(apuc, mask, false);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));

  baryon_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_wordline_map_t *patch = baryon_set_rl(apuc, mask, false);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));
  apuc->in_place = true;

  baryon_free_rl(expected);
}
