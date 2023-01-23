#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, ggl_from_rl, ()) {
  lepton_sm_t mask = lepton_gen_mask();

  uint32_t ggl_seed = lepton_gen_seed();
  uint32_t rl_seed = lepton_gen_seed();

  lepton_randomize_ggl(&apuc->ggl, ggl_seed);
  lepton_randomize_vr(&apuc->rl, rl_seed);

  lepton_ggl_t *expected = (lepton_ggl_t *)malloc(sizeof(lepton_ggl_t));
  memset(expected, true, LEPTON_GGL_SIZE);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
      (*expected)[section / LEPTON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });

  lepton_ggl_from_rl(apuc, mask);
  RC_ASSERT(lepton_ggl_eq(&apuc->ggl, expected));

  lepton_randomize_ggl(&apuc->ggl, ggl_seed);
  lepton_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  lepton_ggl_t *patch = lepton_ggl_from_rl(apuc, mask);
  lepton_patch_ggl(apuc, patch);
  lepton_free_ggl(patch);
  RC_ASSERT(lepton_ggl_eq(&apuc->ggl, expected));
  apuc->in_place = true;

  lepton_free_ggl(expected);
}
