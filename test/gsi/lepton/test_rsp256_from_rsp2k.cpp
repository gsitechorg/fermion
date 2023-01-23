#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rsp256_from_rsp2k, ()) {
  uint32_t rsp256_seed = lepton_gen_seed();
  uint32_t rsp2k_seed = lepton_gen_seed();

  lepton_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  lepton_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);

  lepton_rsp256_from_rsp2k(apuc);
  RC_ASSERT(lepton_rsp256_eq_rsp2k(&apuc->rsp256, &apuc->rsp2k));

  lepton_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  lepton_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);

  apuc->in_place = false;
  lepton_rsp256_t *patch = lepton_rsp256_from_rsp2k(apuc);
  lepton_patch_rsp256(apuc, patch);
  lepton_free_rsp256(patch);
  apuc->in_place = true;
  RC_ASSERT(lepton_rsp256_eq_rsp2k(&apuc->rsp256, &apuc->rsp2k));
}
