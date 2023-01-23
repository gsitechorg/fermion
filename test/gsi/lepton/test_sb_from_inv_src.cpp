#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, sb_from_inv_src, ()) {
  lepton_sm_t mask = lepton_gen_mask();
  lepton_src_t src_type = lepton_gen_src_type();
  std::vector<size_t> row_nums = lepton_gen_writable_row_nums();
  size_t num_vrs = row_nums.size();
  lepton_vr_t *vrs[num_vrs];

  for (size_t i = 0; i < num_vrs; i += 1) {
    size_t row_num = row_nums[i];
    lepton_vr_t *vr = &apuc->vrs[row_num];
    vrs[i] = vr;
  }

  uint32_t vr_seeds[num_vrs];
  uint32_t src_seed = lepton_gen_seed();

  for (size_t i = 0; i < num_vrs; i += 1) {
    lepton_vr_t *vr = vrs[i];
    uint32_t vr_seed = lepton_gen_seed();
    lepton_randomize_vr(vr, vr_seed);
    vr_seeds[i] = vr_seed;
  }
  lepton_randomize_src(apuc, src_type, src_seed);

  // NOTE: Load src only after randomizing it
  void *src = lepton_src(apuc, src_type);

  lepton_vr_t *expected[num_vrs];
  for (size_t i = 0; i < num_vrs; i += 1) {
    expected[i] = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));
  }

  lepton_foreach_masked_section(mask, section, {
    for (size_t i = 0; i < num_vrs; i += 1) {
      lepton_foreach_rl_plat(plat, {
        switch (src_type) {
        case LEPTON_SRC_RL:      // fallthrough
        case LEPTON_SRC_NRL:     // fallthrough
        case LEPTON_SRC_ERL:     // fallthrough
        case LEPTON_SRC_WRL:     // fallthrough
        case LEPTON_SRC_SRL:     // fallthrough
        case LEPTON_SRC_INV_RL:  // fallthrough
        case LEPTON_SRC_INV_NRL: // fallthrough
        case LEPTON_SRC_INV_ERL: // fallthrough
        case LEPTON_SRC_INV_WRL: // fallthrough
        case LEPTON_SRC_INV_SRL: // fallthrough
          (*expected[i])[section][plat] = !(*(lepton_rl_t *)src)[section][plat];
          break;
        case LEPTON_SRC_GGL: // fallthrough
        case LEPTON_SRC_INV_GGL:
          (*expected[i])[section][plat] =
            !(*(lepton_ggl_t *)src)[section / LEPTON_NUM_GROUPS][plat];
          break;
        case LEPTON_SRC_GL: // fallthrough
        case LEPTON_SRC_INV_GL:
          (*expected[i])[section][plat] = !(*(lepton_gl_t *)src)[plat];
          break;
        case LEPTON_SRC_RSP16: // fallthrough
        case LEPTON_SRC_INV_RSP16:
          (*expected[i])[section][plat] = !(*(lepton_rsp16_t *)src)[section][plat / 16];
          break;
        }
      });
    }
  });

  lepton_foreach_unmasked_section(mask, section, {
    for (size_t i = 0; i < num_vrs; i += 1) {
      memcpy(&(*expected[i])[section], &(*vrs[i])[section], LEPTON_WORDLINE_SIZE);
    }
  });

  lepton_sb_from_inv_src(apuc, mask, vrs, num_vrs, src, src_type);
  for (size_t i = 0; i < num_vrs; i += 1) {
    RC_ASSERT(lepton_rl_eq(vrs[i], expected[i]));
  }

  for (size_t i = 0; i < num_vrs; i += 1) {
    lepton_vr_t *vr = vrs[i];
    uint32_t vr_seed = vr_seeds[i];
    lepton_randomize_vr(vr, vr_seed);
  }
  lepton_randomize_src(apuc, src_type, src_seed);

  // Refresh src
  lepton_free_src(src, src_type);
  src = lepton_src(apuc, src_type);

  apuc->in_place = false;
  lepton_wordline_map_t *patch =
    lepton_sb_from_inv_src(apuc, mask, vrs, num_vrs, src, src_type);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  for (size_t i = 0; i < num_vrs; i += 1) {
    RC_ASSERT(lepton_rl_eq(vrs[i], expected[i]));
  }
  apuc->in_place = true;

  for (size_t i = 0; i < num_vrs; i += 1) {
    lepton_free_vr(expected[i]);
  }
  lepton_free_src(src, src_type);
}
