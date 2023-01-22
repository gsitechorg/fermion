#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, lgl_from_l2, ()) {
  size_t l2_addr = lepton_gen_l2_addr();

  uint32_t l2_seed = lepton_gen_seed();
  uint32_t lgl_seed = lepton_gen_seed();

  lepton_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  lepton_randomize_lgl(&apuc->lgl, lgl_seed);

  lepton_lgl_from_l2(apuc, l2_addr);
  RC_ASSERT(lepton_lgl_eq(&apuc->lgl, &apuc->l2[l2_addr]));

  lepton_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  lepton_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  lepton_lgl_t *patch = lepton_lgl_from_l2(apuc, l2_addr);
  lepton_patch_lgl(apuc, patch);
  lepton_free_lgl(patch);
  RC_ASSERT(lepton_lgl_eq(&apuc->lgl, &apuc->l2[l2_addr]));
  apuc->in_place = true;
}
