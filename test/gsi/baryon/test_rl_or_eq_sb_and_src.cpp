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

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rl_or_eq_sb_and_src, ()) {
  baryon_sm_t mask = baryon_gen_mask();
  baryon_src_t src_type = baryon_gen_src_type();
  std::vector<size_t> row_nums = baryon_gen_row_nums();
  size_t num_vrs = row_nums.size();
  baryon_vr_t *vrs[num_vrs];

  for (size_t i = 0; i < num_vrs; i += 1) {
    size_t row_num = row_nums[i];
    baryon_vr_t *vr = &apuc->vrs[row_num];
    vrs[i] = vr;
  }

  uint32_t vr_seeds[num_vrs];
  uint32_t rl_seed = baryon_gen_seed();
  uint32_t src_seed = baryon_gen_seed();

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = baryon_gen_seed();
    baryon_randomize_vr(vr, vr_seed);
    vr_seeds[i] = vr_seed;
  }
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_randomize_src(apuc, src_type, src_seed);

  // NOTE: Load src only after randomizing it
  void *src = baryon_src(apuc, src_type);

  baryon_vr_t *expected = (baryon_vr_t *)malloc(sizeof(baryon_vr_t));

  baryon_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], true, BARYON_WORDLINE_SIZE);
    baryon_foreach_rl_plat(plat, {
      for (size_t i = 0; i < num_vrs; i += 1) {
        (*expected)[section][plat] &= (*vrs[i])[section][plat];
      }

      switch (src_type) {
      case BARYON_SRC_RL:      // fallthrough
      case BARYON_SRC_NRL:     // fallthrough
      case BARYON_SRC_ERL:     // fallthrough
      case BARYON_SRC_WRL:     // fallthrough
      case BARYON_SRC_SRL:     // fallthrough
      case BARYON_SRC_INV_RL:  // fallthrough
      case BARYON_SRC_INV_NRL: // fallthrough
      case BARYON_SRC_INV_ERL: // fallthrough
      case BARYON_SRC_INV_WRL: // fallthrough
      case BARYON_SRC_INV_SRL: // fallthrough
        (*expected)[section][plat] &= (*(baryon_rl_t *)src)[section][plat];
        break;
      case BARYON_SRC_GGL: // fallthrough
      case BARYON_SRC_INV_GGL:
        (*expected)[section][plat] &=
          (*(baryon_ggl_t *)src)[section / BARYON_NUM_GROUPS][plat];
        break;
      case BARYON_SRC_GL: // fallthrough
      case BARYON_SRC_INV_GL:
        (*expected)[section][plat] &= (*(baryon_gl_t *)src)[plat];
        break;
      case BARYON_SRC_RSP16: // fallthrough
      case BARYON_SRC_INV_RSP16:
        (*expected)[section][plat] &= (*(baryon_rsp16_t *)src)[section][plat / 16];
        break;
      }
      (*expected)[section][plat] |= apuc->rl[section][plat];
    });
  });
  baryon_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section], &apuc->rl[section], BARYON_WORDLINE_SIZE);
  });

  baryon_rl_or_eq_sb_and_src(apuc, mask, vrs, num_vrs, src, src_type);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = vr_seeds[i];
    baryon_randomize_vr(vr, vr_seed);
  }
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_randomize_src(apuc, src_type, src_seed);

  // Refresh src
  baryon_free_src(src, src_type);
  src = baryon_src(apuc, src_type);

  apuc->in_place = false;
  baryon_wordline_map_t *patch =
    baryon_rl_or_eq_sb_and_src(apuc, mask, vrs, num_vrs, src, src_type);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  RC_ASSERT(baryon_vr_eq(&apuc->rl, expected));
  apuc->in_place = true;

  baryon_free_vr(expected);
  baryon_free_src(src, src_type);
}
