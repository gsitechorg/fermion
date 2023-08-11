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
