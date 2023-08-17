/* By Dylon Edwards
 */

#include <stdbool.h>
#include <string.h>

#include "apuc.h"
#include "operations.h"

baryon_wordline_t *baryon_right_in_place(baryon_wordline_t *lhs,
                                         baryon_wordline_t *rhs,
                                         baryon_wordline_t *result)
{
  memcpy(result, rhs, BARYON_WORDLINE_SIZE);
  return result;
}

baryon_wordline_t *baryon_right(baryon_wordline_t *lhs,
                                baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_inv_right_in_place(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs,
                                             baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = !(*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_inv_right(baryon_wordline_t *lhs,
                                    baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_inv_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_left_or_right_in_place(baryon_wordline_t *lhs,
                                                 baryon_wordline_t *rhs,
                                                 baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] | (*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_left_or_right(baryon_wordline_t *lhs,
                                        baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_left_or_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_left_or_inv_right_in_place(baryon_wordline_t *lhs,
                                                     baryon_wordline_t *rhs,
                                                     baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] | !(*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_left_or_inv_right(baryon_wordline_t *lhs,
                                            baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_left_or_inv_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_left_and_right_in_place(baryon_wordline_t *lhs,
                                                  baryon_wordline_t *rhs,
                                                  baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] & (*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_left_and_right(baryon_wordline_t *lhs,
                                         baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_left_and_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_left_and_inv_right_in_place(baryon_wordline_t *lhs,
                                                      baryon_wordline_t *rhs,
                                                      baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] & !(*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_left_and_inv_right(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_left_and_inv_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_left_xor_right_in_place(baryon_wordline_t *lhs,
                                                  baryon_wordline_t *rhs,
                                                  baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] ^ (*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_left_xor_right(baryon_wordline_t *lhs,
                                         baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_left_xor_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_left_xor_inv_right_in_place(baryon_wordline_t *lhs,
                                                      baryon_wordline_t *rhs,
                                                      baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = (*lhs)[plat] ^ !(*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_left_xor_inv_right(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_left_xor_inv_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_inv_left_and_right_in_place(baryon_wordline_t *lhs,
                                                      baryon_wordline_t *rhs,
                                                      baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = !(*lhs)[plat] & (*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_inv_left_and_right(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_inv_left_and_right_in_place(lhs, rhs, result);
}

baryon_wordline_t *baryon_inv_left_and_inv_right_in_place(baryon_wordline_t *lhs,
                                                          baryon_wordline_t *rhs,
                                                          baryon_wordline_t *result)
{
  for (size_t plat = 0; plat < BARYON_NUM_PLATS_PER_APUC; plat += 1) {
    (*result)[plat] = !(*lhs)[plat] & !(*rhs)[plat];
  }
  return result;
}

baryon_wordline_t *baryon_inv_left_and_inv_right(baryon_wordline_t *lhs,
                                                 baryon_wordline_t *rhs)
{
  baryon_wordline_t *result = malloc(sizeof(baryon_wordline_t));
  return baryon_inv_left_and_inv_right_in_place(lhs, rhs, result);
}
