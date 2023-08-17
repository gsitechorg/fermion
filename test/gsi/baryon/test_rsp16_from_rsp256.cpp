/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp16_from_rsp256, ()) {
  uint32_t rsp16_seed = baryon_gen_seed();
  uint32_t rsp256_seed = baryon_gen_seed();

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  baryon_rsp16_from_rsp256(apuc);
  RC_ASSERT(baryon_rsp16_eq_rsp256(&apuc->rsp16, &apuc->rsp256));

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  apuc->in_place = false;
  baryon_rsp16_t *patch = baryon_rsp16_from_rsp256(apuc);
  baryon_patch_rsp16(apuc, patch);
  baryon_free_rsp16(patch);
  apuc->in_place = true;
  RC_ASSERT(baryon_rsp16_eq_rsp256(&apuc->rsp16, &apuc->rsp256));
}
