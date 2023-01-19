#include "test_apuc.h"

TEST_F(LeptonAPUCTest, l1_from_lgl_in_place) {
  size_t l1_addr = 0;
  lepton_l1_from_lgl(apuc, l1_addr);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->l1[row][group][l1_plat];
    bool expected_value = apuc->lgl[lgl_plat];
    ASSERT_EQ(actual_value, expected_value)
        << "Expected apuc->l1[" << row << "][" << group << "][" << l1_plat
        << "] to be " << expected_value << " but was " << actual_value;
  });
}

TEST_F(LeptonAPUCTest, l1_from_lgl_w_patch) {
  apuc->in_place = false;
  size_t l1_addr = 0;
  lepton_l1_patch_t *patch = lepton_l1_from_lgl(apuc, l1_addr);
  lepton_patch_l1(apuc, patch);
  lepton_free_l1_patch(patch);
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    bool actual_value = apuc->l1[row][group][l1_plat];
    bool expected_value = apuc->lgl[lgl_plat];
    ASSERT_EQ(actual_value, expected_value)
        << "Expected apuc->l1[" << row << "][" << group << "][" << l1_plat
        << "] to be " << expected_value << " but was " << actual_value;
  });
  apuc->in_place = true;
}
