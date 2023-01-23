#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, lgl_from_l1, ()) {
  size_t l1_addr = baryon_gen_l1_addr();

  size_t bank, group, row;
  baryon_bank_group_row(l1_addr, &bank, &group, &row);

  uint32_t l1_seed = baryon_gen_seed();
  uint32_t lgl_seed = baryon_gen_seed();

  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  baryon_lgl_from_l1(apuc, l1_addr);

  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    RC_ASSERT(apuc->lgl[lgl_plat] == apuc->l1[row][group][l1_plat]);
  });

  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  baryon_lgl_t *patch = baryon_lgl_from_l1(apuc, l1_addr);
  baryon_patch_lgl(apuc, patch);
  baryon_free_lgl(patch);
  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    RC_ASSERT(apuc->lgl[lgl_plat] == apuc->l1[row][group][l1_plat]);
  });
  apuc->in_place = true;
}
