#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, set_rl, ()) {
  lepton_sm_t mask = lepton_gen_mask();

  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_vr(&apuc->rl, rl_seed);

  lepton_rl_t *expected = (lepton_rl_t *) malloc(sizeof(lepton_rl_t));
  lepton_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], true, LEPTON_WORDLINE_SIZE);
  });
  lepton_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], LEPTON_WORDLINE_SIZE);
  });

  lepton_set_rl(apuc, mask, true);
  RC_ASSERT(lepton_rl_eq(&apuc->rl, expected));

  lepton_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  lepton_wordline_map_t *patch = lepton_set_rl(apuc, mask, true);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  RC_ASSERT(lepton_rl_eq(&apuc->rl, expected));
  apuc->in_place = true;

  lepton_free_rl(expected);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, reset_rl, ()) {
  lepton_sm_t mask = lepton_gen_mask();

  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_vr(&apuc->rl, rl_seed);

  lepton_rl_t *expected = (lepton_rl_t *)malloc(sizeof(lepton_rl_t));
  lepton_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], false, LEPTON_WORDLINE_SIZE);
  });
  lepton_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], LEPTON_WORDLINE_SIZE);
  });

  lepton_set_rl(apuc, mask, false);
  RC_ASSERT(lepton_rl_eq(&apuc->rl, expected));

  lepton_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  lepton_wordline_map_t *patch = lepton_set_rl(apuc, mask, false);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  RC_ASSERT(lepton_rl_eq(&apuc->rl, expected));
  apuc->in_place = true;

  lepton_free_rl(expected);
}
