#ifndef __GSI__LEPTON__TEST__COMPARATORS_H__
#define __GSI__LEPTON__TEST__COMPARATORS_H__

#include <stdbool.h>

#include <gsi/lepton/apuc.h>

bool lepton_wordline_eq(lepton_wordline_t *actual, lepton_wordline_t *expected);

bool lepton_vr_eq(lepton_vr_t *actual, lepton_vr_t *expected);

#define lepton_rl_eq lepton_vr_eq

bool lepton_vr_eq_gl(lepton_vr_t *actual, lepton_gl_t *expected);

#define lepton_rl_eq_gl lepton_vr_eq_gl

bool lepton_vr_eq_ggl(lepton_vr_t *actual, lepton_ggl_t *expected);

#define lepton_rl_eq_ggl lepton_vr_eq_ggl

bool lepton_vr_eq_rsp16(lepton_vr_t *actual, lepton_rsp16_t *expected);

#define lepton_rl_eq_rsp16 lepton_vr_eq_rsp16

bool lepton_ggl_eq(lepton_ggl_t *actual, lepton_ggl_t *expected);

#define lepton_l1_eq lepton_ggl_eq

bool lepton_gl_eq(lepton_gl_t *actual, lepton_gl_t *expected);

bool lepton_l2_eq(lepton_l2_t *actual, lepton_l2_t *expected);

#define lepton_lgl_eq lepton_l2_eq

bool lepton_rsp16_eq(lepton_rsp16_t *actual, lepton_rsp16_t *expected);

#endif // __GSI__LEPTON__TEST__COMPARATORS_H__
