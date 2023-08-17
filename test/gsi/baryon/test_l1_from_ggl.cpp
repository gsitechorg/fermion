/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, l1_from_ggl, ()) {
  size_t l1_addr = baryon_gen_l1_addr();

  uint32_t l1_seed = baryon_gen_seed();
  uint32_t ggl_seed = baryon_gen_seed();

  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  baryon_randomize_ggl(&apuc->ggl, ggl_seed);

  baryon_l1_from_ggl(apuc, l1_addr);
  RC_ASSERT(baryon_l1_eq(&apuc->l1[l1_addr], &apuc->ggl));

  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  baryon_randomize_ggl(&apuc->ggl, ggl_seed);

  apuc->in_place = false;
  baryon_l1_patch_t *patch = baryon_l1_from_ggl(apuc, l1_addr);
  baryon_patch_l1(apuc, patch);
  baryon_free_l1_patch(patch);
  RC_ASSERT(baryon_l1_eq(&apuc->l1[l1_addr], &apuc->ggl));
  apuc->in_place = true;
}
