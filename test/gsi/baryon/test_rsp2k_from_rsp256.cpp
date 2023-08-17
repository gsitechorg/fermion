/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp2k_from_rsp256, ()) {
  uint32_t rsp2k_seed = baryon_gen_seed();
  uint32_t rsp256_seed = baryon_gen_seed();

  baryon_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  baryon_rsp2k_from_rsp256(apuc);
  RC_ASSERT(baryon_rsp2k_eq_rsp256(&apuc->rsp2k, &apuc->rsp256));

  baryon_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  apuc->in_place = false;
  baryon_rsp2k_t *patch = baryon_rsp2k_from_rsp256(apuc);
  baryon_patch_rsp2k(apuc, patch);
  baryon_free_rsp2k(patch);
  apuc->in_place = true;
  RC_ASSERT(baryon_rsp2k_eq_rsp256(&apuc->rsp2k, &apuc->rsp256));
}
