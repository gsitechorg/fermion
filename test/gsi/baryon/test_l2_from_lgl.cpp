/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, l2_from_lgl, ()) {
  size_t l2_addr = baryon_gen_l2_addr();

  uint32_t l2_seed = baryon_gen_seed();
  uint32_t lgl_seed = baryon_gen_seed();

  baryon_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  baryon_l2_from_lgl(apuc, l2_addr);
  RC_ASSERT(baryon_l2_eq(&apuc->l2[l2_addr], &apuc->lgl));

  baryon_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  baryon_l2_patch_t *patch = baryon_l2_from_lgl(apuc, l2_addr);
  baryon_patch_l2(apuc, patch);
  baryon_free_l2_patch(patch);
  RC_ASSERT(baryon_l2_eq(&apuc->l2[l2_addr], &apuc->lgl));
  apuc->in_place = true;
}
