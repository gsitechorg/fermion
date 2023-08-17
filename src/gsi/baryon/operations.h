/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__OPERATIONS_H__
#define __GSI__BARYON__OPERATIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "apuc.h"
#include "constants.h"

baryon_wordline_t *baryon_right_in_place(baryon_wordline_t *lhs,
                                         baryon_wordline_t *rhs,
                                         baryon_wordline_t *result);
baryon_wordline_t *baryon_right(baryon_wordline_t *lhs,
                                baryon_wordline_t *rhs);

baryon_wordline_t *baryon_inv_right_in_place(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs,
                                             baryon_wordline_t *result);
baryon_wordline_t *baryon_inv_right(baryon_wordline_t *lhs,
                                    baryon_wordline_t *rhs);

baryon_wordline_t *baryon_left_or_right_in_place(baryon_wordline_t *lhs,
                                                 baryon_wordline_t *rhs,
                                                 baryon_wordline_t *result);
baryon_wordline_t *baryon_left_or_right(baryon_wordline_t *lhs,
                                        baryon_wordline_t *rhs);

baryon_wordline_t *baryon_left_or_inv_right_in_place(baryon_wordline_t *lhs,
                                                     baryon_wordline_t *rhs,
                                                     baryon_wordline_t *result);
baryon_wordline_t *baryon_left_or_inv_right(baryon_wordline_t *lhs,
                                            baryon_wordline_t *rhs);

baryon_wordline_t *baryon_left_and_right_in_place(baryon_wordline_t *lhs,
                                                  baryon_wordline_t *rhs,
                                                  baryon_wordline_t *result);
baryon_wordline_t *baryon_left_and_right(baryon_wordline_t *lhs,
                                         baryon_wordline_t *rhs);

baryon_wordline_t *baryon_left_and_inv_right_in_place(baryon_wordline_t *lhs,
                                                      baryon_wordline_t *rhs,
                                                      baryon_wordline_t *result);
baryon_wordline_t *baryon_left_and_inv_right(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs);

baryon_wordline_t *baryon_left_xor_right_in_place(baryon_wordline_t *lhs,
                                                  baryon_wordline_t *rhs,
                                                  baryon_wordline_t *result);
baryon_wordline_t *baryon_left_xor_right(baryon_wordline_t *lhs,
                                         baryon_wordline_t *rhs);

baryon_wordline_t *baryon_left_xor_inv_right_in_place(baryon_wordline_t *lhs,
                                                      baryon_wordline_t *rhs,
                                                      baryon_wordline_t *result);
baryon_wordline_t *baryon_left_xor_inv_right(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs);

baryon_wordline_t *baryon_inv_left_and_right_in_place(baryon_wordline_t *lhs,
                                                      baryon_wordline_t *rhs,
                                                      baryon_wordline_t *result);
baryon_wordline_t *baryon_inv_left_and_right(baryon_wordline_t *lhs,
                                             baryon_wordline_t *rhs);

baryon_wordline_t *baryon_inv_left_and_inv_right_in_place(baryon_wordline_t *lhs,
                                                          baryon_wordline_t *rhs,
                                                          baryon_wordline_t *result);
baryon_wordline_t *baryon_inv_left_and_inv_right(baryon_wordline_t *lhs,
                                                 baryon_wordline_t *rhs);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__OPERATIONS_H__
