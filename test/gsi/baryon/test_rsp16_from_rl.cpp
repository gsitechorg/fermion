#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp16_from_rl, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t rsp16_seed = baryon_gen_seed();
  uint32_t rl_seed = baryon_gen_seed();

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rl(&apuc->rl, rl_seed);

  baryon_rsp16_t *expected = (baryon_rsp16_t *) malloc(sizeof(baryon_rsp16_t));

  baryon_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], false, BARYON_RSP16_SECTION_SIZE);
    baryon_foreach_rl_plat(rl_plat, {
      size_t rsp16_plat = rl_plat / 16;
      (*expected)[section][rsp16_plat] |= apuc->rl[section][rl_plat];
    });
  });

  baryon_foreach_unmasked_section(mask, section, {
      memcpy(&(*expected)[section],
             &apuc->rsp16[section],
             BARYON_RSP16_SECTION_SIZE);
  });

  baryon_rsp16_from_rl(apuc, mask);
  RC_ASSERT(baryon_rsp16_eq(&apuc->rsp16, expected));

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rl(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_rsp16_section_map_t *patch = baryon_rsp16_from_rl(apuc, mask);
  baryon_patch_partial_rsp16(apuc, patch);
  baryon_free_rsp16_section_map(patch);
  apuc->in_place = true;
  RC_ASSERT(baryon_rsp16_eq(&apuc->rsp16, expected));

  baryon_free_rsp16(expected);
}
