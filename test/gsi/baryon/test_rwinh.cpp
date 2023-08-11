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

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rwinh_standard_use, ()) {
  size_t out_vp = 0;
  size_t mrk_vp = 1;

  baryon_sm_t mask = baryon_gen_mask();

  uint32_t out_seed = baryon_gen_seed();
  uint32_t mrk_seed = baryon_gen_seed();
  uint32_t rl_seed = baryon_gen_seed();

  size_t num_vrs = 1;
  baryon_vr_t *out_vrs[] = { &apuc->vrs[out_vp] };
  baryon_vr_t *mrk_vrs[] = {&apuc->vrs[mrk_vp]};

  baryon_rsp16_t *src = baryon_inv_rsp16(apuc);
  baryon_src_t src_type = BARYON_SRC_INV_RSP16;

  baryon_randomize_vr(&apuc->vrs[out_vp], out_seed);
  baryon_randomize_vr(&apuc->vrs[mrk_vp], mrk_seed);
  baryon_randomize_rl(&apuc->rl, rl_seed);

  baryon_vr_t *expected = (baryon_vr_t *) malloc(sizeof(baryon_vr_t));
  baryon_foreach_masked_section(mask, section, {
    memcpy(&(*expected)[section],
           &apuc->vrs[mrk_vp][section],
           BARYON_WORDLINE_SIZE);
  });
  baryon_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section],
           &apuc->vrs[out_vp][section],
           BARYON_WORDLINE_SIZE);
  });

  baryon_rl_from_sb(apuc, mask, mrk_vrs, num_vrs);
  baryon_rwinh_set(apuc, mask);

  baryon_sb_from_src(apuc, mask, out_vrs, num_vrs, src, src_type);

  baryon_rwinh_rst(apuc, mask, false);

  RC_ASSERT(baryon_vr_eq(&apuc->vrs[out_vp], expected));

  baryon_free_vr(expected);
  baryon_free_rsp16(src);
}
