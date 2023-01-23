#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, gl_from_rl, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t gl_seed = baryon_gen_seed();
  uint32_t rl_seed = baryon_gen_seed();

  baryon_randomize_gl(&apuc->gl, gl_seed);
  baryon_randomize_vr(&apuc->rl, rl_seed);

  baryon_gl_t *expected = (baryon_gl_t *)malloc(sizeof(baryon_gl_t));
  memset(expected, true, BARYON_GL_SIZE);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      (*expected)[plat] &= apuc->rl[section][plat];
    });
  });

  baryon_gl_from_rl(apuc, mask);
  RC_ASSERT(baryon_gl_eq(&apuc->gl, expected));

  baryon_randomize_gl(&apuc->gl, gl_seed);
  baryon_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_gl_t *patch = baryon_gl_from_rl(apuc, mask);
  baryon_patch_gl(apuc, patch);
  baryon_free_gl(patch);
  RC_ASSERT(baryon_gl_eq(&apuc->gl, expected));
  apuc->in_place = true;

  baryon_free_gl(expected);
}
