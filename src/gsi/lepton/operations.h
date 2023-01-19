#ifndef __GSI__LEPTON__OPERATIONS_H__
#define __GSI__LEPTON__OPERATIONS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "apuc.h"
#include "constants.h"

lepton_wordline_t *lepton_right_in_place(lepton_wordline_t *lhs,
                                         lepton_wordline_t *rhs,
                                         lepton_wordline_t *result);
lepton_wordline_t *lepton_right(lepton_wordline_t *lhs,
                                lepton_wordline_t *rhs);

lepton_wordline_t *lepton_inv_right_in_place(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs,
                                             lepton_wordline_t *result);
lepton_wordline_t *lepton_inv_right(lepton_wordline_t *lhs,
                                    lepton_wordline_t *rhs);

lepton_wordline_t *lepton_left_or_right_in_place(lepton_wordline_t *lhs,
                                                 lepton_wordline_t *rhs,
                                                 lepton_wordline_t *result);
lepton_wordline_t *lepton_left_or_right(lepton_wordline_t *lhs,
                                        lepton_wordline_t *rhs);

lepton_wordline_t *lepton_left_or_inv_right_in_place(lepton_wordline_t *lhs,
                                                     lepton_wordline_t *rhs,
                                                     lepton_wordline_t *result);
lepton_wordline_t *lepton_left_or_inv_right(lepton_wordline_t *lhs,
                                            lepton_wordline_t *rhs);

lepton_wordline_t *lepton_left_and_right_in_place(lepton_wordline_t *lhs,
                                                  lepton_wordline_t *rhs,
                                                  lepton_wordline_t *result);
lepton_wordline_t *lepton_left_and_right(lepton_wordline_t *lhs,
                                         lepton_wordline_t *rhs);

lepton_wordline_t *lepton_left_and_inv_right_in_place(lepton_wordline_t *lhs,
                                                      lepton_wordline_t *rhs,
                                                      lepton_wordline_t *result);
lepton_wordline_t *lepton_left_and_inv_right(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs);

lepton_wordline_t *lepton_left_xor_right_in_place(lepton_wordline_t *lhs,
                                                  lepton_wordline_t *rhs,
                                                  lepton_wordline_t *result);
lepton_wordline_t *lepton_left_xor_right(lepton_wordline_t *lhs,
                                         lepton_wordline_t *rhs);

lepton_wordline_t *lepton_left_xor_inv_right_in_place(lepton_wordline_t *lhs,
                                                      lepton_wordline_t *rhs,
                                                      lepton_wordline_t *result);
lepton_wordline_t *lepton_left_xor_inv_right(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs);

lepton_wordline_t *lepton_inv_left_and_right_in_place(lepton_wordline_t *lhs,
                                                      lepton_wordline_t *rhs,
                                                      lepton_wordline_t *result);
lepton_wordline_t *lepton_inv_left_and_right(lepton_wordline_t *lhs,
                                             lepton_wordline_t *rhs);

lepton_wordline_t *lepton_inv_left_and_inv_right_in_place(lepton_wordline_t *lhs,
                                                          lepton_wordline_t *rhs,
                                                          lepton_wordline_t *result);
lepton_wordline_t *lepton_inv_left_and_inv_right(lepton_wordline_t *lhs,
                                                 lepton_wordline_t *rhs);

#ifdef __cplusplus
}
#endif

#endif // __GSI__LEPTON__OPERATIONS_H__
