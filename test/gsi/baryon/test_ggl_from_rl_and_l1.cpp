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

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, ggl_from_rl, ()) {
  baryon_sm_t mask = baryon_gen_mask();

  uint32_t ggl_seed = baryon_gen_seed();
  uint32_t rl_seed = baryon_gen_seed();

  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_randomize_vr(&apuc->rl, rl_seed);

  baryon_ggl_t *expected = (baryon_ggl_t *)malloc(sizeof(baryon_ggl_t));
  memset(expected, true, BARYON_GGL_SIZE);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      (*expected)[section / BARYON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });

  baryon_ggl_from_rl(apuc, mask);
  RC_ASSERT(baryon_ggl_eq(&apuc->ggl, expected));

  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_randomize_vr(&apuc->rl, rl_seed);

  apuc->in_place = false;
  baryon_ggl_t *patch = baryon_ggl_from_rl(apuc, mask);
  baryon_patch_ggl(apuc, patch);
  baryon_free_ggl(patch);
  RC_ASSERT(baryon_ggl_eq(&apuc->ggl, expected));
  apuc->in_place = true;

  baryon_free_ggl(expected);
}
