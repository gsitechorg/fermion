#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "generators.h"

namespace gen = rc::gen;

bool lepton_gen_weighted_bool(uint32_t prob_true) {
  uint32_t prob_false = 100 - prob_true;
  return *gen::weightedElement<bool>({
    {prob_true, true},
    {prob_false, false}
  }).as("weighted_bool");
}

bool lepton_gen_bool() {
  return rand() & 1;
}

uint32_t lepton_gen_seed() {
  return *gen::arbitrary<uint32_t>().as("seed");
}

std::vector<size_t> lepton_gen_row_nums() {
  std::vector<size_t> row_nums;
  for (size_t row_num = 0;
       row_num < LEPTON_NUM_SBS && row_nums.size() < LEPTON_NUM_RN_REGS;
       row_num += 1) {
    if (lepton_gen_weighted_bool(30)) {
      row_nums.push_back(row_num);
    }
  }
  return row_nums;
}

std::vector<size_t> lepton_gen_writable_row_nums() {
  std::vector<size_t> row_nums;
  size_t group = *gen::inRange<size_t>(0, 3);
  size_t lower_row_num = group * 8;
  size_t upper_row_num = lower_row_num + 8;
  for (size_t row_num = lower_row_num; row_num < upper_row_num; row_num += 1) {
    if (lepton_gen_weighted_bool(30)) {
      row_nums.push_back(row_num);
    }
  }
  return row_nums;
}

size_t lepton_gen_l1_addr() {
  return *gen::inRange<size_t>(0, LEPTON_NUM_L1_ROWS).as("l1_addr");
}

size_t lepton_gen_l2_addr() {
  return *gen::inRange<size_t>(0, LEPTON_NUM_L2_ROWS).as("l2_addr");
}

lepton_src_t lepton_gen_src_type() {
  return *gen::weightedElement<lepton_src_t>({
    {6.25, LEPTON_SRC_RL},
    {6.25, LEPTON_SRC_NRL},
    {6.25, LEPTON_SRC_ERL},
    {6.25, LEPTON_SRC_WRL},
    {6.25, LEPTON_SRC_SRL},
    {6.25, LEPTON_SRC_INV_RL},
    {6.25, LEPTON_SRC_INV_NRL},
    {6.25, LEPTON_SRC_INV_ERL},
    {6.25, LEPTON_SRC_INV_WRL},
    {6.25, LEPTON_SRC_INV_SRL},
    {6.25, LEPTON_SRC_GGL},
    {6.25, LEPTON_SRC_INV_GGL},
    {6.25, LEPTON_SRC_GL},
    {6.25, LEPTON_SRC_INV_GL},
    {6.25, LEPTON_SRC_RSP16},
    {6.25, LEPTON_SRC_INV_RSP16},
  }).as("src");
}

lepton_sm_t lepton_gen_mask() {
  lepton_sm_t mask = 0x0000;
  for (size_t section = 0; section < LEPTON_NUM_SECTIONS; section += 1) {
    if (lepton_gen_weighted_bool(30)) {
      mask |= (1 << section);
    }
  }
  return mask;
}

void lepton_randomize_apuc(lepton_apuc_t *apuc, uint32_t seed) {
  srand(seed);
  lepton_foreach_vr_row(row, lepton_randomize_vr(&apuc->vrs[row], rand()));
  lepton_randomize_rl(&apuc->rl, rand());
  lepton_randomize_gl(&apuc->gl, rand());
  lepton_randomize_ggl(&apuc->ggl, rand());
  lepton_randomize_rsp16(&apuc->rsp16, rand());
  lepton_randomize_rsp256(&apuc->rsp256, rand());
  lepton_randomize_rsp2k(&apuc->rsp2k, rand());
  lepton_randomize_rsp32k(&apuc->rsp32k, rand());
  lepton_foreach_l1_row(row, lepton_randomize_l1(&apuc->l1[row], rand()));
  lepton_foreach_l2_row(row, lepton_randomize_l2(&apuc->l2[row], rand()));
  lepton_randomize_lgl(&apuc->lgl, rand());
}

void lepton_randomize_wordline(lepton_wordline_t *wordline, uint32_t seed) {
  srand(seed);
  lepton_foreach_vr_plat(plat, {
    (*wordline)[plat] = lepton_gen_bool();
  });
}

void lepton_randomize_vr(lepton_vr_t *vr, uint32_t seed) {
  srand(seed);
  lepton_foreach_vr_section_plat(section, plat, {
    (*vr)[section][plat] = lepton_gen_bool();
  });
}

void lepton_randomize_ggl(lepton_ggl_t *ggl, uint32_t seed) {
  srand(seed);
  lepton_foreach_ggl_group_plat(group, plat, {
    (*ggl)[group][plat] = lepton_gen_bool();
  });
}

void lepton_randomize_gl(lepton_gl_t *gl, uint32_t seed) {
  srand(seed);
  lepton_foreach_gl_plat(plat, {
    (*gl)[plat] = lepton_gen_bool();
  });
}

void lepton_randomize_lgl(lepton_lgl_t *lgl, uint32_t seed) {
  srand(seed);
  lepton_foreach_lgl_plat(plat, {
    (*lgl)[plat] = lepton_gen_bool();
  });
}

void lepton_randomize_rsp16(lepton_rsp16_t *rsp16, uint32_t seed) {
  srand(seed);
  lepton_foreach_rsp16_section_plat(section, plat, {
    (*rsp16)[section][plat] = lepton_gen_bool();
  });
}

void lepton_randomize_rsp256(lepton_rsp256_t *rsp256, uint32_t seed) {
  srand(seed);
  lepton_foreach_rsp256_section_plat(section, plat, {
    (*rsp256)[section][plat] = lepton_gen_bool();
  });
}

void lepton_randomize_rsp2k(lepton_rsp2k_t *rsp2k, uint32_t seed) {
  srand(seed);
  lepton_foreach_rsp2k_section_plat(section, plat, {
    (*rsp2k)[section][plat] = lepton_gen_bool();
  });
}

void lepton_randomize_rsp32k(lepton_rsp32k_t *rsp32k, uint32_t seed) {
  srand(seed);
  lepton_foreach_rsp32k_section_plat(section, plat, {
    (*rsp32k)[section][plat] = lepton_gen_bool();
  });
}

void lepton_randomize_src(lepton_apuc_t *apuc, lepton_src_t src_type, uint32_t seed) {
  switch (src_type) {
  case LEPTON_SRC_RL:            // fallthrough
  case LEPTON_SRC_NRL:           // fallthrough
  case LEPTON_SRC_ERL:           // fallthrough
  case LEPTON_SRC_WRL:           // fallthrough
  case LEPTON_SRC_SRL:           // fallthrough
  case LEPTON_SRC_INV_RL:        // fallthrough
  case LEPTON_SRC_INV_NRL:       // fallthrough
  case LEPTON_SRC_INV_ERL:       // fallthrough
  case LEPTON_SRC_INV_WRL:       // fallthrough
  case LEPTON_SRC_INV_SRL:       // fallthrough
    lepton_randomize_rl(&apuc->rl, seed);
    break;
  case LEPTON_SRC_GGL:           // fallthrough
  case LEPTON_SRC_INV_GGL:
    lepton_randomize_ggl(&apuc->ggl, seed);
    break;
  case LEPTON_SRC_GL:            // fallthrough
  case LEPTON_SRC_INV_GL:
    lepton_randomize_gl(&apuc->gl, seed);
    break;
  case LEPTON_SRC_RSP16:         // fallthrough
  case LEPTON_SRC_INV_RSP16:
    lepton_randomize_rsp16(&apuc->rsp16, seed);
    break;
  }
}
