#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, l1_from_lgl, ()) {
  size_t l1_addr = lepton_gen_l1_addr();

  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);

  uint32_t l1_seed = lepton_gen_seed();
  uint32_t lgl_seed = lepton_gen_seed();

  lepton_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  lepton_randomize_lgl(&apuc->lgl, lgl_seed);

  lepton_l1_from_lgl(apuc, l1_addr);

  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    RC_ASSERT(apuc->l1[row][group][l1_plat] == apuc->lgl[lgl_plat]);
  });

  lepton_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  lepton_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  lepton_l1_patch_t *patch = lepton_l1_from_lgl(apuc, l1_addr);
  lepton_patch_l1(apuc, patch);
  lepton_free_l1_patch(patch);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    RC_ASSERT(apuc->l1[row][group][l1_plat] == apuc->lgl[lgl_plat]);
  });
  apuc->in_place = true;
}
