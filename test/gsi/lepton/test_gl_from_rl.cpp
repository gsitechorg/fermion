#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, gl_from_rl, ()) {
  lepton_sm_t mask = lepton_gen_mask();

  uint32_t gl_seed = lepton_gen_seed();
  uint32_t rl_seed = lepton_gen_seed();

  lepton_randomize_gl(&apuc->gl, gl_seed);
  lepton_randomize_vr(&apuc->rl, rl_seed);

  lepton_gl_t *expected = (lepton_gl_t *)malloc(sizeof(lepton_gl_t));
  memset(expected, true, LEPTON_GL_SIZE);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
      (*expected)[plat] &= apuc->rl[section][plat];
    });
  });

  lepton_gl_from_rl(apuc, mask);
  RC_ASSERT(lepton_gl_eq(&apuc->gl, expected));

  lepton_randomize_gl(&apuc->gl, gl_seed);
  lepton_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  lepton_gl_t *patch = lepton_gl_from_rl(apuc, mask);
  lepton_patch_gl(apuc, patch);
  lepton_free_gl(patch);
  RC_ASSERT(lepton_gl_eq(&apuc->gl, expected));
  apuc->in_place = true;

  lepton_free_gl(expected);
}
