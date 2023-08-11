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

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp16_from_rsp256, ()) {
  uint32_t rsp16_seed = baryon_gen_seed();
  uint32_t rsp256_seed = baryon_gen_seed();

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  baryon_rsp16_from_rsp256(apuc);
  RC_ASSERT(baryon_rsp16_eq_rsp256(&apuc->rsp16, &apuc->rsp256));

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);

  apuc->in_place = false;
  baryon_rsp16_t *patch = baryon_rsp16_from_rsp256(apuc);
  baryon_patch_rsp16(apuc, patch);
  baryon_free_rsp16(patch);
  apuc->in_place = true;
  RC_ASSERT(baryon_rsp16_eq_rsp256(&apuc->rsp16, &apuc->rsp256));
}
