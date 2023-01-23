#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rsp32k_from_rsp2k, ()) {
  uint32_t rsp32k_seed = lepton_gen_seed();
  uint32_t rsp2k_seed = lepton_gen_seed();

  lepton_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);
  lepton_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);

  lepton_rsp32k_from_rsp2k(apuc);
  RC_ASSERT(lepton_rsp32k_eq_rsp2k(&apuc->rsp32k, &apuc->rsp2k));

  lepton_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);
  lepton_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);

  apuc->in_place = false;
  lepton_rsp32k_t *patch = lepton_rsp32k_from_rsp2k(apuc);
  lepton_patch_rsp32k(apuc, patch);
  lepton_free_rsp32k(patch);
  apuc->in_place = true;
  RC_ASSERT(lepton_rsp32k_eq_rsp2k(&apuc->rsp32k, &apuc->rsp2k));
}
