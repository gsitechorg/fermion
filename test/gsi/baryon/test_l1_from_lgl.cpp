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

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, l1_from_lgl, ()) {
  size_t l1_addr = baryon_gen_l1_addr();

  size_t bank, group, row;
  baryon_bank_group_row(l1_addr, &bank, &group, &row);

  uint32_t l1_seed = baryon_gen_seed();
  uint32_t lgl_seed = baryon_gen_seed();

  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  baryon_l1_from_lgl(apuc, l1_addr);

  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    RC_ASSERT(apuc->l1[row][group][l1_plat] == apuc->lgl[lgl_plat]);
  });

  baryon_randomize_l1(&apuc->l1[l1_addr], l1_seed);
  baryon_randomize_lgl(&apuc->lgl, lgl_seed);

  apuc->in_place = false;
  baryon_l1_patch_t *patch = baryon_l1_from_lgl(apuc, l1_addr);
  baryon_patch_l1(apuc, patch);
  baryon_free_l1_patch(patch);
  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    RC_ASSERT(apuc->l1[row][group][l1_plat] == apuc->lgl[lgl_plat]);
  });
  apuc->in_place = true;
}
