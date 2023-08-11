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

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rl_from_sb, ()) {
  baryon_sm_t mask = baryon_gen_mask();
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

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = baryon_gen_seed();
    baryon_randomize_vr(vr, vr_seed);
    vr_seeds[i] = vr_seed;
  }
  baryon_randomize_vr(&apuc->rl, rl_seed);

  baryon_rl_t *expected = (baryon_rl_t *)malloc(sizeof(baryon_rl_t));
  memcpy(expected, &apuc->rl, BARYON_RL_SIZE);

  baryon_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], true, BARYON_WORDLINE_SIZE);
    baryon_foreach_rl_plat(plat, {
      for (size_t i = 0; i < num_vrs; i += 1) {
        (*expected)[section][plat] &= (*vrs[i])[section][plat];
      }
    });
  });

  baryon_rl_from_sb(apuc, mask, vrs, num_vrs);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));

  for (size_t i = 0; i < num_vrs; i += 1) {
    baryon_vr_t *vr = vrs[i];
    uint32_t vr_seed = vr_seeds[i];
    baryon_randomize_vr(vr, vr_seed);
  }
  baryon_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_wordline_map_t *patch =
    baryon_rl_from_sb(apuc, mask, vrs, num_vrs);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));
  apuc->in_place = true;

  baryon_free_rl(expected);
}
