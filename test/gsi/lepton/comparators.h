#ifndef __GSI__LEPTON__TEST__COMPARATORS_H__
#define __GSI__LEPTON__TEST__COMPARATORS_H__

#include <stdbool.h>

#include <gsi/lepton/apuc.h>

bool lepton_wordline_eq(lepton_wordline_t *lhs, lepton_wordline_t *rhs);

bool lepton_vr_eq(lepton_vr_t *lhs, lepton_vr_t *rhs);

#define lepton_rl_eq lepton_vr_eq

bool lepton_vr_eq_gl(lepton_vr_t *lhs, lepton_gl_t *rhs);

#define lepton_rl_eq_gl lepton_vr_eq_gl

bool lepton_vr_eq_ggl(lepton_vr_t *lhs, lepton_ggl_t *rhs);

#define lepton_rl_eq_ggl lepton_vr_eq_ggl

bool lepton_vr_eq_rsp16(lepton_vr_t *lhs, lepton_rsp16_t *rhs);

#define lepton_rl_eq_rsp16 lepton_vr_eq_rsp16

bool lepton_ggl_eq(lepton_ggl_t *lhs, lepton_ggl_t *rhs);

#define lepton_l1_eq lepton_ggl_eq

bool lepton_gl_eq(lepton_gl_t *lhs, lepton_gl_t *rhs);

bool lepton_l2_eq(lepton_l2_t *lhs, lepton_l2_t *rhs);

#define lepton_lgl_eq lepton_l2_eq

bool lepton_rsp16_eq(lepton_rsp16_t *lhs, lepton_rsp16_t *rhs);

bool lepton_rsp16_eq_rsp256(lepton_rsp16_t *lhs, lepton_rsp256_t *rhs);

bool lepton_rsp256_eq_rsp16(lepton_rsp256_t *lhs, lepton_rsp16_t *rhs);

bool lepton_rsp256_eq_rsp2k(lepton_rsp256_t *lhs, lepton_rsp2k_t *rhs);

bool lepton_rsp2k_eq_rsp256(lepton_rsp2k_t *lhs, lepton_rsp256_t *rhs);

bool lepton_rsp2k_eq_rsp32k(lepton_rsp2k_t *lhs, lepton_rsp32k_t *rhs);

bool lepton_rsp32k_eq_rsp2k(lepton_rsp32k_t *lhs, lepton_rsp2k_t *rhs);

#endif // __GSI__LEPTON__TEST__COMPARATORS_H__
