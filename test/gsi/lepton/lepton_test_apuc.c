#include "lepton_test_apuc.h"
#include "lepton_test_ggl_from_l1.h"
#include "lepton_test_ggl_from_rl.h"
#include "lepton_test_gl_from_rl.h"
#include "lepton_test_l1_from_ggl.h"
#include "lepton_test_l1_from_lgl.h"
#include "lepton_test_l2_from_lgl.h"
#include "lepton_test_lgl_from_l1.h"
#include "lepton_test_lgl_from_l2.h"
#include "lepton_test_rl_from_sb.h"
#include "lepton_test_rl_from_sb_or_src.h"
#include "lepton_test_rl_from_src.h"
#include "lepton_test_rl_or_eq_sb.h"
#include "lepton_test_rl_xor_eq_sb.h"
#include "lepton_test_rl_xor_eq_src.h"
#include "lepton_test_sb_from_src.h"
#include "lepton_test_src.h"
#include <gsi/lepton/constants.h>

void lepton_test_plats_for_bank(lepton_apuc_t *apuc) {
  for (size_t bank = 0; bank < 4; bank += 1) {
    size_t lower_plat_apc_0;
    size_t upper_plat_apc_0;
    size_t lower_plat_apc_1;
    size_t upper_plat_apc_1;
    lepton_plats_for_bank(bank, &lower_plat_apc_0, &upper_plat_apc_0,
                          &lower_plat_apc_1, &upper_plat_apc_1);
    size_t expected_value = bank * 2 * LEPTON_NUM_PLATS_PER_HALF_BANK;
    if (lower_plat_apc_0 != expected_value) {
      LEPTON_FAIL_TEST(
          "Expected lower_plat_apc_0 for bank %zu to be %zu but was %zu\n",
          bank, expected_value, lower_plat_apc_0);
      break;
    }
    expected_value = (bank + 1) * 2 * LEPTON_NUM_PLATS_PER_HALF_BANK;
    if (upper_plat_apc_0 != expected_value) {
      LEPTON_FAIL_TEST(
          "Expected upper_plat_apc_0 for bank %zu to be %zu but was %zu\n",
          bank, expected_value, upper_plat_apc_0);
      break;
    }
    expected_value = lower_plat_apc_0 + LEPTON_NUM_PLATS_PER_APC;
    if (lower_plat_apc_1 != expected_value) {
      LEPTON_FAIL_TEST(
          "Expected lower_plat_apc_1 for bank %zu to be %zu but was %zu\n",
          bank, expected_value, lower_plat_apc_1);
      break;
    }
    expected_value = upper_plat_apc_0 + LEPTON_NUM_PLATS_PER_APC;
    if (upper_plat_apc_1 != expected_value) {
      LEPTON_FAIL_TEST(
          "Expected upper_plat_apc_1 for bank %zu to be %zu but was %zu\n",
          bank, expected_value, upper_plat_apc_1);
      break;
    }
  }
}

void lepton_test_foreach_bank_plat(lepton_apuc_t *apuc) {
  for (size_t bank = 0; bank < 4; bank += 1) {
    size_t num_plats = 0;
    ssize_t prev_lgl_plat = -1;
    ssize_t prev_l1_plat = bank * 2 * LEPTON_NUM_PLATS_PER_HALF_BANK - 1;
    lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
      if (lgl_plat != prev_lgl_plat + 1) {
        LEPTON_FAIL_TEST("Expected lgl_plat to be %zd but was %zu\n",
                         prev_lgl_plat + 1, lgl_plat);
        goto assertion_done;
      }
      prev_lgl_plat = lgl_plat;
      if (lgl_plat == 2 * LEPTON_NUM_PLATS_PER_HALF_BANK) {
        prev_l1_plat = bank * 2 * LEPTON_NUM_PLATS_PER_HALF_BANK +
                       LEPTON_NUM_PLATS_PER_APC - 1;
      }
      if (l1_plat != prev_l1_plat + 1) {
        LEPTON_FAIL_TEST(
            "Expected l1_plat to be %zd when lgl_plat is %zu but was %zu\n",
            prev_l1_plat + 1, lgl_plat, l1_plat);
        goto assertion_done;
      }
      prev_l1_plat = l1_plat;
      num_plats += 1;
    });
    if (num_plats != LEPTON_NUM_LGL_PLATS) {
      LEPTON_FAIL_TEST("Expected num_plats to be %d but was %zu\n",
                       LEPTON_NUM_LGL_PLATS, num_plats);
      goto assertion_done;
    }
  }
assertion_done:
  ;;
}

void lepton_test_foreach_masked_section(lepton_apuc_t *apuc) {
  uint16_t expected_mask = 0xFFFF;
  uint16_t actual_mask = 0x0000;
  size_t num_sections = 0;
  lepton_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  if (actual_mask != expected_mask) {
    LEPTON_FAIL_TEST("Expected mask to be 0x%04X but was 0x%04X\n",
                     expected_mask, actual_mask);
    goto end_of_test;
  }
  if (num_sections != 16) {
    LEPTON_FAIL_TEST("Expected %d sections but got %zu\n",
                     16, num_sections);
    goto end_of_test;
  }

  expected_mask = 0x0000;
  actual_mask = 0x0000;
  num_sections = 0;
  lepton_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  if (actual_mask != expected_mask) {
    LEPTON_FAIL_TEST("Expected mask to be 0x%04X but was 0x%04X\n",
                     expected_mask, actual_mask);
    goto end_of_test;
  }
  if (num_sections != 0) {
    LEPTON_FAIL_TEST("Expected %d sections but got %zu\n", 0, num_sections);
    goto end_of_test;
  }

  expected_mask = 0x0001;
  actual_mask = 0x0000;
  num_sections = 0;
  lepton_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  if (actual_mask != expected_mask) {
    LEPTON_FAIL_TEST("Expected mask to be 0x%04X but was 0x%04X\n",
                     expected_mask, actual_mask);
    goto end_of_test;
  }
  if (num_sections != 1) {
    LEPTON_FAIL_TEST("Expected %d sections but got %zu\n", 1, num_sections);
    goto end_of_test;
  }

  expected_mask = 0x1000;
  actual_mask = 0x0000;
  num_sections = 0;
  lepton_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  if (actual_mask != expected_mask) {
    LEPTON_FAIL_TEST("Expected mask to be 0x%04X but was 0x%04X\n",
                     expected_mask, actual_mask);
    goto end_of_test;
  }
  if (num_sections != 1) {
    LEPTON_FAIL_TEST("Expected %d sections but got %zu\n", 1, num_sections);
    goto end_of_test;
  }

  expected_mask = 0xABCD;
  actual_mask = 0x0000;
  num_sections = 0;
  lepton_foreach_masked_section(expected_mask, section, {
    actual_mask |= (1 << section);
    num_sections += 1;
  });
  if (actual_mask != expected_mask) {
    LEPTON_FAIL_TEST("Expected mask to be 0x%04X but was 0x%04X\n",
                     expected_mask, actual_mask);
    goto end_of_test;
  }
  if (num_sections != 10) {
    LEPTON_FAIL_TEST("Expected %d sections but got %zu\n", 10, num_sections);
    goto end_of_test;
  }

end_of_test:
  ;;
}

void lepton_test_apuc() {
  LEPTON_RUN_APUC_TEST(lepton_test_plats_for_bank);
  LEPTON_RUN_APUC_TEST(lepton_test_foreach_bank_plat);
  LEPTON_RUN_APUC_TEST(lepton_test_foreach_masked_section);
  lepton_test_ggl_from_l1();
  lepton_test_ggl_from_rl();
  lepton_test_gl_from_rl();
  lepton_test_l1_from_ggl();
  lepton_test_l1_from_lgl();
  lepton_test_l2_from_lgl();
  lepton_test_lgl_from_l1();
  lepton_test_lgl_from_l2();
  lepton_test_rl_from_sb();
  lepton_test_rl_from_sb_or_src();
  lepton_test_rl_from_src();
  lepton_test_rl_or_eq_sb();
  lepton_test_rl_xor_eq_sb();
  lepton_test_rl_xor_eq_src();
  lepton_test_sb_from_src();
  lepton_test_src();
}
