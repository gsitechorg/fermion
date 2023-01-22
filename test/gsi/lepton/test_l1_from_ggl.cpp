#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, l1_from_ggl, ()) {
  size_t l1_addr = lepton_gen_l1_addr();

  uint32_t l1_seed = lepton_gen_seed();
  uint32_t ggl_seed = lepton_gen_seed();

  lepton_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  lepton_randomize_ggl(&apuc->ggl, ggl_seed);

  lepton_l1_from_ggl(apuc, l1_addr);
  RC_ASSERT(lepton_l1_eq(&apuc->l1[l1_addr], &apuc->ggl));

  lepton_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  lepton_randomize_ggl(&apuc->ggl, ggl_seed);

  apuc->in_place = false;
  lepton_l1_patch_t *patch = lepton_l1_from_ggl(apuc, l1_addr);
  lepton_patch_l1(apuc, patch);
  lepton_free_l1_patch(patch);
  RC_ASSERT(lepton_l1_eq(&apuc->l1[l1_addr], &apuc->ggl));
  apuc->in_place = true;
}
