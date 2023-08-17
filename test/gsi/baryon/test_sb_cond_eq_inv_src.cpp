/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, sb_cond_eq_inv_src, ()) {
  baryon_sm_t mask = baryon_gen_mask();
  baryon_src_t src_type = baryon_gen_src_type();
  std::vector<size_t> row_nums = baryon_gen_writable_row_nums();
  size_t num_vrs = row_nums.size();
  baryon_vr_t *vrs[num_vrs];

  for (size_t i = 0; i < num_vrs; i += 1) {
    size_t row_num = row_nums[i];
    baryon_vr_t *vr = &apuc->vrs[row_num];
    vrs[i] = vr;
  }

  uint32_t vr_seeds[num_vrs];
  uint32_t src_seed = baryon_gen_seed();

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = baryon_gen_seed();
    baryon_randomize_vr(vr, vr_seed);
    vr_seeds[i] = vr_seed;
  }
  baryon_randomize_src(apuc, src_type, src_seed);

  // NOTE: Load src only after randomizing it
  void *src = baryon_src(apuc, src_type);

  baryon_vr_t *expected[num_vrs];
  for (size_t i = 0; i < num_vrs; i += 1) {
    expected[i] = (baryon_vr_t *) malloc(sizeof(baryon_vr_t));
    memcpy(expected[i], vrs[i], BARYON_VR_SIZE);
  }

  baryon_foreach_masked_section(mask, section, {
    for (size_t i = 0; i < num_vrs; i += 1) {
      baryon_foreach_rl_plat(plat, {
        switch (src_type) {
        case BARYON_SRC_INV_RL:  // fallthrough
        case BARYON_SRC_INV_NRL: // fallthrough
        case BARYON_SRC_INV_ERL: // fallthrough
        case BARYON_SRC_INV_WRL: // fallthrough
        case BARYON_SRC_INV_SRL: {
          (*expected[i])[section][plat] &= (*(baryon_rl_t *)src)[section][plat];
          break;
        }
        case BARYON_SRC_INV_GGL: {
          (*expected[i])[section][plat] &=
            (*(baryon_ggl_t *)src)[section / BARYON_NUM_GROUPS][plat];
          break;
        }
        case BARYON_SRC_INV_GL: {
          (*expected[i])[section][plat] &= (*(baryon_gl_t *)src)[plat];
          break;
        }
        case BARYON_SRC_INV_RSP16:{
          (*expected[i])[section][plat] &=
            (*(baryon_rsp16_t *)src)[section][plat / 16];
          break;
        }
        case BARYON_SRC_RL:  // fallthrough
        case BARYON_SRC_NRL: // fallthrough
        case BARYON_SRC_ERL: // fallthrough
        case BARYON_SRC_WRL: // fallthrough
        case BARYON_SRC_SRL: {
          (*expected[i])[section][plat] |= (*(baryon_rl_t *)src)[section][plat];
          break;
        }
        case BARYON_SRC_GGL: {
          (*expected[i])[section][plat] |=
              (*(baryon_ggl_t *)src)[section / BARYON_NUM_GROUPS][plat];
          break;
        }
        case BARYON_SRC_GL: {
          (*expected[i])[section][plat] |= (*(baryon_gl_t *)src)[plat];
          break;
        }
        case BARYON_SRC_RSP16: {
          (*expected[i])[section][plat] |=
              (*(baryon_rsp16_t *)src)[section][plat / 16];
          break;
        }
        }
      });
    }
  });

  baryon_sb_cond_eq_inv_src(apuc, mask, vrs, num_vrs, src, src_type);
  for (size_t i = 0; i < num_vrs; i += 1) {
    RC_ASSERT(baryon_rl_eq(vrs[i], expected[i]));
  }

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = vr_seeds[i];
    baryon_randomize_vr(vr, vr_seed);
  }
  baryon_randomize_src(apuc, src_type, src_seed);

  // Refresh src
  baryon_free_src(src, src_type);
  src = baryon_src(apuc, src_type);

  apuc->in_place = false;
  baryon_wordline_map_t *patch =
    baryon_sb_cond_eq_inv_src(apuc, mask, vrs, num_vrs, src, src_type);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  for (size_t i = 0; i < num_vrs; i += 1) {
    RC_ASSERT(baryon_rl_eq(vrs[i], expected[i]));
  }
  apuc->in_place = true;

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_free_vr(expected[i]);
  }
  baryon_free_src(src, src_type);
}
