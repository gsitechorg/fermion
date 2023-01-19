#include "test_apuc.h"

TEST_F(LeptonAPUCTest, lgl_from_l1_in_place) {
  size_t l1_addr = 0;
  lepton_lgl_from_l1(apuc, l1_addr);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->lgl[lgl_plat];
    bool expected_value = apuc->l1[row][group][l1_plat];
    ASSERT_EQ(actual_value, expected_value)
        << "Expected apuc->lgl[" << lgl_plat << "] to be " << expected_value
        << " but was " << actual_value;
  });
}

TEST_F(LeptonAPUCTest, lgl_from_l1_w_patch) {
  apuc->in_place = false;
  size_t l1_addr = 0;
  lepton_lgl_t *patch = lepton_lgl_from_l1(apuc, l1_addr);
  lepton_patch_lgl(apuc, patch);
  lepton_free_lgl(patch);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->lgl[lgl_plat];
    bool expected_value = apuc->l1[row][group][l1_plat];
    ASSERT_EQ(actual_value, expected_value)
        << "Expected apuc->lgl[" << lgl_plat << "] to be " << expected_value
        << " but was " << actual_value;
  });
  apuc->in_place = true;
}
