#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "generators.h"

namespace gen = rc::gen;

bool baryon_gen_weighted_bool(uint32_t prob_true) {
  uint32_t prob_false = 100 - prob_true;
  return *gen::weightedElement<bool>({
    {prob_true, true},
    {prob_false, false}
  }).as("weighted_bool");
}

bool baryon_gen_bool() {
  return rand() & 1;
}

uint32_t baryon_gen_seed() {
  return *gen::arbitrary<uint32_t>().as("seed");
}

std::vector<size_t> baryon_gen_row_nums() {
  std::vector<size_t> row_nums;
  for (size_t row_num = 0;
       row_num < BARYON_NUM_SBS && row_nums.size() < BARYON_NUM_RN_REGS;
       row_num += 1) {
    if (baryon_gen_weighted_bool(30)) {
      row_nums.push_back(row_num);
    }
  }
  return row_nums;
}

std::vector<size_t> baryon_gen_writable_row_nums() {
  std::vector<size_t> row_nums;
  size_t group = *gen::inRange<size_t>(0, 3);
  size_t lower_row_num = group * 8;
  size_t upper_row_num = lower_row_num + 8;
  for (size_t row_num = lower_row_num; row_num < upper_row_num; row_num += 1) {
    if (baryon_gen_weighted_bool(30)) {
      row_nums.push_back(row_num);
    }
  }
  return row_nums;
}

size_t baryon_gen_l1_addr() {
  return *gen::inRange<size_t>(0, BARYON_NUM_L1_ROWS).as("l1_addr");
}

size_t baryon_gen_l2_addr() {
  return *gen::inRange<size_t>(0, BARYON_NUM_L2_ROWS).as("l2_addr");
}

baryon_src_t baryon_gen_src_type() {
  return *gen::weightedElement<baryon_src_t>({
    {6.25, BARYON_SRC_RL},
    {6.25, BARYON_SRC_NRL},
    {6.25, BARYON_SRC_ERL},
    {6.25, BARYON_SRC_WRL},
    {6.25, BARYON_SRC_SRL},
    {6.25, BARYON_SRC_INV_RL},
    {6.25, BARYON_SRC_INV_NRL},
    {6.25, BARYON_SRC_INV_ERL},
    {6.25, BARYON_SRC_INV_WRL},
    {6.25, BARYON_SRC_INV_SRL},
    {6.25, BARYON_SRC_GGL},
    {6.25, BARYON_SRC_INV_GGL},
    {6.25, BARYON_SRC_GL},
    {6.25, BARYON_SRC_INV_GL},
    {6.25, BARYON_SRC_RSP16},
    {6.25, BARYON_SRC_INV_RSP16},
  }).as("src");
}

baryon_sm_t baryon_gen_mask() {
  baryon_sm_t mask = 0x0000;
  for (size_t section = 0; section < BARYON_NUM_SECTIONS; section += 1) {
    if (baryon_gen_weighted_bool(30)) {
      mask |= (1 << section);
    }
  }
  return mask;
}

void baryon_randomize_apuc(baryon_apuc_t *apuc, uint32_t seed) {
  srand(seed);
  baryon_foreach_vr_row(row, baryon_randomize_vr(&apuc->vrs[row], rand()));
  baryon_randomize_rl(&apuc->rl, rand());
  baryon_randomize_gl(&apuc->gl, rand());
  baryon_randomize_ggl(&apuc->ggl, rand());
  baryon_randomize_rsp16(&apuc->rsp16, rand());
  baryon_randomize_rsp256(&apuc->rsp256, rand());
  baryon_randomize_rsp2k(&apuc->rsp2k, rand());
  baryon_randomize_rsp32k(&apuc->rsp32k, rand());
  baryon_foreach_l1_row(row, baryon_randomize_l1(&apuc->l1[row], rand()));
  baryon_foreach_l2_row(row, baryon_randomize_l2(&apuc->l2[row], rand()));
  baryon_randomize_lgl(&apuc->lgl, rand());
}

void baryon_randomize_wordline(baryon_wordline_t *wordline, uint32_t seed) {
  srand(seed);
  baryon_foreach_vr_plat(plat, {
    (*wordline)[plat] = baryon_gen_bool();
  });
}

void baryon_randomize_vr(baryon_vr_t *vr, uint32_t seed) {
  srand(seed);
  baryon_foreach_vr_section_plat(section, plat, {
    (*vr)[section][plat] = baryon_gen_bool();
  });
}

void baryon_randomize_ggl(baryon_ggl_t *ggl, uint32_t seed) {
  srand(seed);
  baryon_foreach_ggl_group_plat(group, plat, {
    (*ggl)[group][plat] = baryon_gen_bool();
  });
}

void baryon_randomize_gl(baryon_gl_t *gl, uint32_t seed) {
  srand(seed);
  baryon_foreach_gl_plat(plat, {
    (*gl)[plat] = baryon_gen_bool();
  });
}

void baryon_randomize_lgl(baryon_lgl_t *lgl, uint32_t seed) {
  srand(seed);
  baryon_foreach_lgl_plat(plat, {
    (*lgl)[plat] = baryon_gen_bool();
  });
}

void baryon_randomize_rsp16(baryon_rsp16_t *rsp16, uint32_t seed) {
  srand(seed);
  baryon_foreach_rsp16_section_plat(section, plat, {
    (*rsp16)[section][plat] = baryon_gen_bool();
  });
}

void baryon_randomize_rsp256(baryon_rsp256_t *rsp256, uint32_t seed) {
  srand(seed);
  baryon_foreach_rsp256_section_plat(section, plat, {
    (*rsp256)[section][plat] = baryon_gen_bool();
  });
}

void baryon_randomize_rsp2k(baryon_rsp2k_t *rsp2k, uint32_t seed) {
  srand(seed);
  baryon_foreach_rsp2k_section_plat(section, plat, {
    (*rsp2k)[section][plat] = baryon_gen_bool();
  });
}

void baryon_randomize_rsp32k(baryon_rsp32k_t *rsp32k, uint32_t seed) {
  srand(seed);
  baryon_foreach_rsp32k_section(section, {
    (*rsp32k)[section] = baryon_gen_bool();
  });
}

void baryon_randomize_src(baryon_apuc_t *apuc, baryon_src_t src_type, uint32_t seed) {
  switch (src_type) {
  case BARYON_SRC_RL:            // fallthrough
  case BARYON_SRC_NRL:           // fallthrough
  case BARYON_SRC_ERL:           // fallthrough
  case BARYON_SRC_WRL:           // fallthrough
  case BARYON_SRC_SRL:           // fallthrough
  case BARYON_SRC_INV_RL:        // fallthrough
  case BARYON_SRC_INV_NRL:       // fallthrough
  case BARYON_SRC_INV_ERL:       // fallthrough
  case BARYON_SRC_INV_WRL:       // fallthrough
  case BARYON_SRC_INV_SRL:       // fallthrough
    baryon_randomize_rl(&apuc->rl, seed);
    break;
  case BARYON_SRC_GGL:           // fallthrough
  case BARYON_SRC_INV_GGL:
    baryon_randomize_ggl(&apuc->ggl, seed);
    break;
  case BARYON_SRC_GL:            // fallthrough
  case BARYON_SRC_INV_GL:
    baryon_randomize_gl(&apuc->gl, seed);
    break;
  case BARYON_SRC_RSP16:         // fallthrough
  case BARYON_SRC_INV_RSP16:
    baryon_randomize_rsp16(&apuc->rsp16, seed);
    break;
  }
}
