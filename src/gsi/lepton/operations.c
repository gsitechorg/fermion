#include <stdbool.h>
#include <string.h>

#include "gsi/lepton/apuc.h"
#include "gsi/lepton/operations.h"

lepton_wordline_t *lepton_right_in_place(lepton_wordline_t *lhs,
                                         lepton_wordline_t *rhs,
                                         lepton_wordline_t *result)
{
  memcpy(result, rhs, LEPTON_WORDLINE_SIZE);
  return result;
}

lepton_wordline_t *lepton_right(lepton_wordline_t *lhs,
                                lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_inv_right_in_place(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs,
                                             lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = !(*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_inv_right(lepton_wordline_t *lhs,
                                    lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_inv_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_left_or_right_in_place(lepton_wordline_t *lhs,
                                                 lepton_wordline_t *rhs,
                                                 lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] | (*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_left_or_right(lepton_wordline_t *lhs,
                                        lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_left_or_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_left_or_inv_right_in_place(lepton_wordline_t *lhs,
                                                     lepton_wordline_t *rhs,
                                                     lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] | !(*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_left_or_inv_right(lepton_wordline_t *lhs,
                                            lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_left_or_inv_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_left_and_right_in_place(lepton_wordline_t *lhs,
                                                  lepton_wordline_t *rhs,
                                                  lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] & (*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_left_and_right(lepton_wordline_t *lhs,
                                         lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_left_and_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_left_and_inv_right_in_place(lepton_wordline_t *lhs,
                                                      lepton_wordline_t *rhs,
                                                      lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] & !(*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_left_and_inv_right(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_left_and_inv_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_left_xor_right_in_place(lepton_wordline_t *lhs,
                                                  lepton_wordline_t *rhs,
                                                  lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] ^ (*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_left_xor_right(lepton_wordline_t *lhs,
                                         lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_left_xor_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_left_xor_inv_right_in_place(lepton_wordline_t *lhs,
                                                      lepton_wordline_t *rhs,
                                                      lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] ^ !(*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_left_xor_inv_right(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_left_xor_inv_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_inv_left_and_right_in_place(lepton_wordline_t *lhs,
                                                      lepton_wordline_t *rhs,
                                                      lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = !(*lhs)[plat] & (*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_inv_left_and_right(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_inv_left_and_right_in_place(lhs, rhs, result);
}

lepton_wordline_t *lepton_inv_left_and_inv_right_in_place(lepton_wordline_t *lhs,
                                                          lepton_wordline_t *rhs,
                                                          lepton_wordline_t *result)
{
  for (size_t plat = 0; plat < LEPTON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = !(*lhs)[plat] & !(*rhs)[plat];
  }
  return result;
}

lepton_wordline_t *lepton_inv_left_and_inv_right(lepton_wordline_t *lhs,
                                                 lepton_wordline_t *rhs)
{
  lepton_wordline_t *result = malloc(sizeof(lepton_wordline_t));
  return lepton_inv_left_and_inv_right_in_place(lhs, rhs, result);
}
