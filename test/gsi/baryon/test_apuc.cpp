/* By Dylon Edwards
 *
 * Copyright 2019 - 2023 GSI Technology, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gsi/baryon/constants.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"

TEST_F(BaryonAPUCTest, plats_for_bank) {
  for (size_t bank = 0; bank < 4; bank += 1) {
    size_t apc_0_lo;
    size_t apc_0_hi;
    size_t apc_1_lo;
    size_t apc_1_hi;
    baryon_plats_for_bank(bank, &apc_0_lo, &apc_0_hi, &apc_1_lo, &apc_1_hi);
    size_t expected_value = bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    ASSERT_EQ(apc_0_lo, expected_value)
        << "Expected apc_0_lo for bank " << bank << " to be "
        << expected_value << " but was " << apc_0_lo;
    expected_value = apc_0_lo + 4 * BARYON_NUM_PLATS_PER_HALF_BANK;
    ASSERT_EQ(apc_0_hi, expected_value)
        << "Expected apc_0_hi for bank " << bank << " to be "
        << expected_value << " but was " << apc_0_hi;
    expected_value = apc_0_lo + BARYON_NUM_PLATS_PER_APC;
    ASSERT_EQ(apc_1_lo, expected_value)
        << "Expected apc_1_lo for bank " << bank << " to be "
        << expected_value << " but was " << apc_1_lo;
    expected_value = apc_0_hi + BARYON_NUM_PLATS_PER_APC;
    ASSERT_EQ(apc_1_hi, expected_value)
        << "Expected apc_1_hi for bank " << bank << " to be "
        << expected_value << " but was " << apc_1_hi;
  }
}

TEST_F(BaryonAPUCTest, foreach_bank_plat) {
  for (size_t bank = 0; bank < 4; bank += 1) {
    size_t num_plats = 0;
    ssize_t prev_l1_plat = bank * BARYON_NUM_PLATS_PER_HALF_BANK - 1;
    baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
      ASSERT_EQ(lgl_plat, num_plats)
        << "Expected lgl_plat to be " << num_plats << " but was " << lgl_plat;
      if (lgl_plat % BARYON_NUM_PLATS_PER_HALF_BANK == 0) {
        switch (lgl_plat / BARYON_NUM_PLATS_PER_HALF_BANK) {
        case 1:
          prev_l1_plat = (bank + 4) * BARYON_NUM_PLATS_PER_HALF_BANK - 1;
          break;
        case 2:
          prev_l1_plat =
            bank * BARYON_NUM_PLATS_PER_HALF_BANK
            + BARYON_NUM_PLATS_PER_APC - 1;
          break;
        case 3:
          prev_l1_plat =
            (bank + 4) * BARYON_NUM_PLATS_PER_HALF_BANK
            + BARYON_NUM_PLATS_PER_APC - 1;
          break;
        }
      }
      ASSERT_EQ(l1_plat, prev_l1_plat + 1)
        << "Expected l1_plat for bank " << bank << " to be " << prev_l1_plat + 1
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
