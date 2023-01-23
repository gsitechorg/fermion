#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, lgl_from_l2, ()) {
  size_t l2_addr = baryon_gen_l2_addr();

  uint32_t l2_seed = baryon_gen_seed();
  uint32_t lgl_seed = baryon_gen_seed();

  baryon_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  baryon_lgl_from_l2(apuc, l2_addr);
  RC_ASSERT(baryon_lgl_eq(&apuc->lgl, &apuc->l2[l2_addr]));

  baryon_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  baryon_lgl_t *patch = baryon_lgl_from_l2(apuc, l2_addr);
  baryon_patch_lgl(apuc, patch);
  baryon_free_lgl(patch);
  RC_ASSERT(baryon_lgl_eq(&apuc->lgl, &apuc->l2[l2_addr]));
  apuc->in_place = true;
}
