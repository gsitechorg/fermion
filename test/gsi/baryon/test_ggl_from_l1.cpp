#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, ggl_from_l1, ()) {
  size_t l1_addr = baryon_gen_l1_addr();

  uint32_t ggl_seed = baryon_gen_seed();
  uint32_t l1_seed = baryon_gen_seed();

  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);

  baryon_ggl_from_l1(apuc, l1_addr);
  RC_ASSERT(baryon_ggl_eq(&apuc->ggl, &apuc->l1[l1_addr]));

  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);

  apuc->in_place = false;
  baryon_ggl_t *patch = baryon_ggl_from_l1(apuc, l1_addr);
  baryon_patch_ggl(apuc, patch);
  baryon_free_ggl(patch);
  RC_ASSERT(baryon_ggl_eq(&apuc->ggl, &apuc->l1[l1_addr]));
  apuc->in_place = true;
}
