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

#include <stdlib.h>

#include <gsi/baryon/operations.h>
#include <gsi/baryon/apuc.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "generators.h"

RC_GTEST_PROP(operations, right, ()) {
  baryon_wordline_t *lhs =
    (baryon_wordline_t *) malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *) malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *) malloc(sizeof(baryon_wordline_t));
  memcpy(expected, rhs, BARYON_WORDLINE_SIZE);

  baryon_wordline_t *actual = baryon_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, inv_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *) malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *) malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *) malloc(sizeof(baryon_wordline_t));
  baryon_foreach_wordline_plat(plat, (*expected)[plat] = !(*rhs)[plat]);

  baryon_wordline_t *actual = baryon_inv_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, left_or_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] | (*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_left_or_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_left_or_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, left_or_inv_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] | !(*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_left_or_inv_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_left_or_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, left_and_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] & (*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_left_and_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_left_and_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, left_and_inv_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] & !(*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_left_and_inv_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_left_and_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, left_xor_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] ^ (*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_left_xor_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_left_xor_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, left_xor_inv_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] ^ !(*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_left_xor_inv_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_left_xor_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, inv_left_and_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = !(*lhs)[plat] & (*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_inv_left_and_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_inv_left_and_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}

RC_GTEST_PROP(operations, inv_left_and_inv_right, ()) {
  baryon_wordline_t *lhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(lhs, baryon_gen_seed());

  baryon_wordline_t *rhs =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));
  baryon_randomize_wordline(rhs, baryon_gen_seed());

  baryon_wordline_t *expected =
      (baryon_wordline_t *)malloc(sizeof(baryon_wordline_t));

  baryon_foreach_wordline_plat(plat, {
    (*expected)[plat] = !(*lhs)[plat] & !(*rhs)[plat];
  });

  baryon_wordline_t *actual = baryon_inv_left_and_inv_right(lhs, rhs);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_randomize_wordline(actual, baryon_gen_seed());
  baryon_inv_left_and_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(baryon_wordline_eq(actual, expected));

  baryon_free_wordline(actual);
  baryon_free_wordline(expected);
  baryon_free_wordline(rhs);
  baryon_free_wordline(lhs);
}
