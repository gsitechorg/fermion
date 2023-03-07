#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, apuc_rsp_fifo, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);

  baryon_rsp16_from_rl(apuc, mask);
  baryon_rsp256_from_rsp16(apuc);
  baryon_rsp2k_from_rsp256(apuc);
  baryon_rsp32k_from_rsp2k(apuc);
  baryon_noop(apuc);
  baryon_noop(apuc);

  uint16_t expected_rsp2k[BARYON_NUM_HALF_BANKS_PER_APUC];

  baryon_foreach_range(half_bank, BARYON_NUM_HALF_BANKS_PER_APUC, {
    expected_rsp2k[half_bank] = 0x0000;
    baryon_foreach_rsp2k_section(section, {
      expected_rsp2k[half_bank] |= apuc->rsp2k[section][half_bank] << section;
    });
  });

  uint16_t expected_rsp32k = 0x0000;

  baryon_foreach_rsp32k_section(section, {
    expected_rsp32k |= apuc->rsp32k[section] << section;
  });

  baryon_rsp_end(apuc);

  for (size_t apc_id = 0; apc_id < 2; apc_id += 1) {
    size_t offset = apc_id * 8;
    RC_ASSERT(!baryon_apuc_rsp_rd(apuc_rsp_fifo, apc_id));
    for (size_t bank_id = 0; bank_id < 4; bank_id += 1) {
      uint32_t rsp2k_value = baryon_rd_rsp2k_reg(apuc_rsp_fifo, bank_id);
      uint16_t lower_value = rsp2k_value & 0xFFFF;
      uint16_t upper_value = rsp2k_value >> 16;
      size_t lower_half_bank = bank_id * 2 + offset;
      size_t upper_half_bank = lower_half_bank + 1;
      RC_ASSERT(expected_rsp2k[lower_half_bank] == lower_value);
      RC_ASSERT(expected_rsp2k[upper_half_bank] == upper_value);
    }
    uint8_t rsp32k_value = baryon_rd_rsp32k_reg(apuc_rsp_fifo);
    RC_ASSERT(rsp32k_value == ((expected_rsp32k >> offset) & 0xFF));
  }
}
