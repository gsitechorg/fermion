#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, l2_from_lgl, ()) {
  size_t l2_addr = lepton_gen_l2_addr();

  uint32_t l2_seed = lepton_gen_seed();
  uint32_t lgl_seed = lepton_gen_seed();

  lepton_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  lepton_randomize_lgl(&apuc->lgl, lgl_seed);

  lepton_l2_from_lgl(apuc, l2_addr);
  RC_ASSERT(lepton_l2_eq(&apuc->l2[l2_addr], &apuc->lgl));

  lepton_randomize_l2(&apuc->l2[l2_addr], l2_seed);
  lepton_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  lepton_l2_patch_t *patch = lepton_l2_from_lgl(apuc, l2_addr);
  lepton_patch_l2(apuc, patch);
  lepton_free_l2_patch(patch);
  RC_ASSERT(lepton_l2_eq(&apuc->l2[l2_addr], &apuc->lgl));
  apuc->in_place = true;
}
