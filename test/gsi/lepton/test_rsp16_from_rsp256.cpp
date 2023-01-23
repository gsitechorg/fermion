#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rsp16_from_rsp256, ()) {
  uint32_t rsp16_seed = lepton_gen_seed();
  uint32_t rsp256_seed = lepton_gen_seed();

  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  lepton_rsp16_from_rsp256(apuc);
  RC_ASSERT(lepton_rsp16_eq_rsp256(&apuc->rsp16, &apuc->rsp256));

  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  apuc->in_place = false;
  lepton_rsp16_t *patch = lepton_rsp16_from_rsp256(apuc);
  lepton_patch_rsp16(apuc, patch);
  lepton_free_rsp16(patch);
  apuc->in_place = true;
  RC_ASSERT(lepton_rsp16_eq_rsp256(&apuc->rsp16, &apuc->rsp256));
}
