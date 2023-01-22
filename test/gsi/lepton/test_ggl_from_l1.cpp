#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, ggl_from_l1, ()) {
  size_t l1_addr = lepton_gen_l1_addr();

  uint32_t ggl_seed = lepton_gen_seed();
  uint32_t l1_seed = lepton_gen_seed();

  lepton_randomize_ggl(&apuc->ggl, ggl_seed);
  lepton_randomize_l1(&apuc->l1[l1_addr], l1_seed);

  lepton_ggl_from_l1(apuc, l1_addr);
  RC_ASSERT(lepton_ggl_eq(&apuc->ggl, &apuc->l1[l1_addr]));

  lepton_randomize_ggl(&apuc->ggl, ggl_seed);
  lepton_randomize_l1(&apuc->l1[l1_addr], l1_seed);

  apuc->in_place = false;
  lepton_ggl_t *patch = lepton_ggl_from_l1(apuc, l1_addr);
  lepton_patch_ggl(apuc, patch);
  lepton_free_ggl(patch);
  RC_ASSERT(lepton_ggl_eq(&apuc->ggl, &apuc->l1[l1_addr]));
  apuc->in_place = true;
}
