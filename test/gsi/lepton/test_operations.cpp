#include <stdlib.h>

#include <gsi/lepton/operations.h>
#include <gsi/lepton/apuc.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "generators.h"

RC_GTEST_PROP(operations, right, ()) {
  lepton_wordline_t *lhs =
    (lepton_wordline_t *) malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *) malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *) malloc(sizeof(lepton_wordline_t));
  memcpy(expected, rhs, LEPTON_WORDLINE_SIZE);

  lepton_wordline_t *actual = lepton_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, inv_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *) malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *) malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *) malloc(sizeof(lepton_wordline_t));
  lepton_foreach_wordline_plat(plat, (*expected)[plat] = !(*rhs)[plat]);

  lepton_wordline_t *actual = lepton_inv_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, left_or_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] | (*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_left_or_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_left_or_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, left_or_inv_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] | !(*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_left_or_inv_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_left_or_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, left_and_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] & (*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_left_and_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_left_and_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, left_and_inv_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] & !(*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_left_and_inv_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_left_and_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, left_xor_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] ^ (*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_left_xor_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_left_xor_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, left_xor_inv_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = (*lhs)[plat] ^ !(*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_left_xor_inv_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_left_xor_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, inv_left_and_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = !(*lhs)[plat] & (*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_inv_left_and_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_inv_left_and_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}

RC_GTEST_PROP(operations, inv_left_and_inv_right, ()) {
  lepton_wordline_t *lhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(lhs, lepton_gen_seed());

  lepton_wordline_t *rhs =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));
  lepton_randomize_wordline(rhs, lepton_gen_seed());

  lepton_wordline_t *expected =
      (lepton_wordline_t *)malloc(sizeof(lepton_wordline_t));

  lepton_foreach_wordline_plat(plat, {
    (*expected)[plat] = !(*lhs)[plat] & !(*rhs)[plat];
  });

  lepton_wordline_t *actual = lepton_inv_left_and_inv_right(lhs, rhs);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  lepton_randomize_wordline(actual, lepton_gen_seed());
  lepton_inv_left_and_inv_right_in_place(lhs, rhs, actual);
  RC_ASSERT(lepton_wordline_eq(actual, expected));

  free(actual);
  free(expected);
  free(rhs);
  free(lhs);
}
