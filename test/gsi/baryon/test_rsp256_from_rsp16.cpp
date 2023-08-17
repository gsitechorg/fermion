/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp256_from_rsp16, ()) {
  uint32_t rsp256_seed = baryon_gen_seed();
  uint32_t rsp16_seed = baryon_gen_seed();

  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);

  baryon_rsp256_from_rsp16(apuc);
  RC_ASSERT(baryon_rsp256_eq_rsp16(&apuc->rsp256, &apuc->rsp16));

  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);

  apuc->in_place = false;
  baryon_rsp256_t *patch = baryon_rsp256_from_rsp16(apuc);
  baryon_patch_rsp256(apuc, patch);
  baryon_free_rsp256(patch);
  apuc->in_place = true;
  RC_ASSERT(baryon_rsp256_eq_rsp16(&apuc->rsp256, &apuc->rsp16));
}
