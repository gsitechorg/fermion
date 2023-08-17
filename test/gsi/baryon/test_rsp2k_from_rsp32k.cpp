/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp2k_from_rsp32k, ()) {
  uint32_t rsp2k_seed = baryon_gen_seed();
  uint32_t rsp32k_seed = baryon_gen_seed();

  baryon_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  baryon_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);

  baryon_rsp2k_from_rsp32k(apuc);
  RC_ASSERT(baryon_rsp2k_eq_rsp32k(&apuc->rsp2k, &apuc->rsp32k));

  baryon_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  baryon_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);

  apuc->in_place = false;
  baryon_rsp2k_t *patch = baryon_rsp2k_from_rsp32k(apuc);
  baryon_patch_rsp2k(apuc, patch);
  baryon_free_rsp2k(patch);
  apuc->in_place = true;
  RC_ASSERT(baryon_rsp2k_eq_rsp32k(&apuc->rsp2k, &apuc->rsp32k));
}
