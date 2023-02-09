#include <gsi/baryon/constants.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"

TEST_F(BaryonAPUCTest, plats_for_bank) {
  for (size_t bank = 0; bank < 4; bank += 1) {
    size_t lower_plat_apc_0;
    size_t upper_plat_apc_0;
    size_t lower_plat_apc_1;
    size_t upper_plat_apc_1;
    baryon_plats_for_bank(bank, &lower_plat_apc_0, &upper_plat_apc_0,
                          &lower_plat_apc_1, &upper_plat_apc_1);
    size_t expected_value = bank * 2 * BARYON_NUM_PLATS_PER_HALF_BANK;
    ASSERT_EQ(lower_plat_apc_0, expected_value)
        << "Expected lower_plat_apc_0 for bank " << bank << " to be "
        << expected_value << " but was " << lower_plat_apc_0;
    expected_value = (bank + 1) * 2 * BARYON_NUM_PLATS_PER_HALF_BANK;
    ASSERT_EQ(upper_plat_apc_0, expected_value)
        << "Expected upper_plat_apc_0 for bank " << bank << " to be "
        << expected_value << " but was " << upper_plat_apc_0;
    expected_value = lower_plat_apc_0 + BARYON_NUM_PLATS_PER_APC;
    ASSERT_EQ(lower_plat_apc_1, expected_value)
        << "Expected lower_plat_apc_1 for bank " << bank << " to be "
        << expected_value << " but was " << lower_plat_apc_1;
    expected_value = upper_plat_apc_0 + BARYON_NUM_PLATS_PER_APC;
    ASSERT_EQ(upper_plat_apc_1, expected_value)
        << "Expected upper_plat_apc_1 for bank " << bank << " to be "
        << expected_value << " but was " << upper_plat_apc_1;
  }
}

TEST_F(BaryonAPUCTest, foreach_bank_plat) {
  for (size_t bank = 0; bank < 4; bank += 1) {
    size_t num_plats = 0;
    ssize_t prev_lgl_plat = -1;
    ssize_t prev_l1_plat = bank * 2 * BARYON_NUM_PLATS_PER_HALF_BANK - 1;
    baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
      ASSERT_EQ(lgl_plat, prev_lgl_plat + 1)
          << "Expected lgl_plat to be " << prev_lgl_plat + 1 << " but was "
          << lgl_plat;
      prev_lgl_plat = lgl_plat;
      if (lgl_plat == 2 * BARYON_NUM_PLATS_PER_HALF_BANK) {
        prev_l1_plat = bank * 2 * BARYON_NUM_PLATS_PER_HALF_BANK +
                       BARYON_NUM_PLATS_PER_APC - 1;
      }
      ASSERT_EQ(l1_plat, prev_l1_plat + 1)
          << "Expected l1_plat to be " << prev_l1_plat + 1
          << " when lgl_plat is " << lgl_plat << " but was " << l1_plat;
      prev_l1_plat = l1_plat;
      num_plats += 1;
    });
    ASSERT_EQ(num_plats, BARYON_NUM_LGL_PLATS)
        << "Expected num_plats to be " << BARYON_NUM_LGL_PLATS
        << " but was " << num_plats;
  }
}

TEST_F(BaryonAPUCTest, foreach_masked_section) {
  uint16_t expected_mask = 0xFFFF;
  uint16_t actual_mask = 0x0000;
  size_t num_sections = 0;
  baryon_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  ASSERT_EQ(actual_mask, expected_mask)
      << "Expected mask to be " << expected_mask << " but was " << actual_mask;
  ASSERT_EQ(num_sections, 16)
      << "Expected 16 sections but got " << num_sections;

  expected_mask = 0x0000;
  actual_mask = 0x0000;
  num_sections = 0;
  baryon_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  ASSERT_EQ(actual_mask, expected_mask)
      << "Expected mask to be " << expected_mask << " but was " << actual_mask;
  ASSERT_EQ(num_sections, 0)
      << "Expected 0 sections but got " << num_sections;

  expected_mask = 0x0001;
  actual_mask = 0x0000;
  num_sections = 0;
  baryon_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  ASSERT_EQ(actual_mask, expected_mask)
      << "Expected mask to be " << expected_mask << " but was " << actual_mask;
  ASSERT_EQ(num_sections, 1)
      << "Expected 1 sections but got " << num_sections;

  expected_mask = 0x1000;
  actual_mask = 0x0000;
  num_sections = 0;
  baryon_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  ASSERT_EQ(actual_mask, expected_mask)
      << "Expected mask to be " << expected_mask << " but was " << actual_mask;
  ASSERT_EQ(num_sections, 1)
      << "Expected 1 sections but got " << num_sections;

  expected_mask = 0xABCD;
  actual_mask = 0x0000;
  num_sections = 0;
  baryon_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  ASSERT_EQ(actual_mask, expected_mask)
      << "Expected mask to be " << expected_mask << " but was " << actual_mask;
  ASSERT_EQ(num_sections, 10)
      << "Expected 10 sections but got " << num_sections;
}
