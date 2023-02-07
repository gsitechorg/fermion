#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp2k_fifo, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);

  baryon_rsp16_from_rl(apuc, mask);
  baryon_rsp256_from_rsp16(apuc);
  baryon_rsp2k_from_rsp256(apuc);

  uint16_t expected_value[BARYON_NUM_HALF_BANKS_PER_APUC];

  for (size_t half_bank = 0;
       half_bank < BARYON_NUM_HALF_BANKS_PER_APUC;
       half_bank += 1) {
    expected_value[half_bank] = 0x0000;
    for (size_t section = 0;
         section < BARYON_NUM_RSP2K_SECTIONS;
         section += 1) {
      expected_value[half_bank] |=
        apuc->rsp2k[section][half_bank] << section;
    }
  }

  baryon_rsp_end(apuc);

  uint16_t actual_value[BARYON_NUM_HALF_BANKS_PER_APUC];
  RC_ASSERT(rsp2k_fifo->length == 1);
  baryon_rsp2k_fifo_deque(rsp2k_fifo, actual_value);
  RC_ASSERT(rsp2k_fifo->length == 0);

  for (size_t half_bank = 0;
       half_bank < BARYON_NUM_HALF_BANKS_PER_APUC;
       half_bank += 1) {
    RC_ASSERT(expected_value[half_bank] == actual_value[half_bank]);
  }
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp32k_fifo, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);

  baryon_rsp16_from_rl(apuc, mask);
  baryon_rsp256_from_rsp16(apuc);
  baryon_rsp2k_from_rsp256(apuc);
  baryon_rsp32k_from_rsp2k(apuc);

  uint16_t expected_value = 0x0000;
  for (size_t half_bank = 0;
       half_bank < BARYON_NUM_HALF_BANKS_PER_APUC;
       half_bank += 1) {
    for (size_t section = 0;
         section < BARYON_NUM_RSP32K_SECTIONS;
         section += 1) {
      expected_value |= apuc->rsp32k[section] << section;
    }
  }

  baryon_rsp_end(apuc);

  uint16_t actual_value;
  RC_ASSERT(rsp32k_fifo->length == 1);
  baryon_rsp32k_fifo_deque(rsp32k_fifo, &actual_value);
  RC_ASSERT(rsp32k_fifo->length == 0);
  RC_ASSERT(expected_value == actual_value);
}
