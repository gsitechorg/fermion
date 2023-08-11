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

#ifndef __GSI__BARYON__TEST__COMPARATORS_H__
#define __GSI__BARYON__TEST__COMPARATORS_H__

#include <stdbool.h>

#include <gsi/baryon/apuc.h>

bool baryon_wordline_eq(baryon_wordline_t *lhs, baryon_wordline_t *rhs);

bool baryon_vr_eq(baryon_vr_t *lhs, baryon_vr_t *rhs);

#define baryon_rl_eq baryon_vr_eq

bool baryon_vr_eq_gl(baryon_vr_t *lhs, baryon_gl_t *rhs);

#define baryon_rl_eq_gl baryon_vr_eq_gl

bool baryon_vr_eq_ggl(baryon_vr_t *lhs, baryon_ggl_t *rhs);

#define baryon_rl_eq_ggl baryon_vr_eq_ggl

bool baryon_vr_eq_rsp16(baryon_vr_t *lhs, baryon_rsp16_t *rhs);

#define baryon_rl_eq_rsp16 baryon_vr_eq_rsp16

bool baryon_ggl_eq(baryon_ggl_t *lhs, baryon_ggl_t *rhs);

#define baryon_l1_eq baryon_ggl_eq

bool baryon_gl_eq(baryon_gl_t *lhs, baryon_gl_t *rhs);

bool baryon_l2_eq(baryon_l2_t *lhs, baryon_l2_t *rhs);

#define baryon_lgl_eq baryon_l2_eq

bool baryon_rsp16_eq(baryon_rsp16_t *lhs, baryon_rsp16_t *rhs);

bool baryon_rsp16_eq_rl(baryon_rsp16_t *lhs, baryon_rl_t *rhs);

bool baryon_rsp16_eq_rsp256(baryon_rsp16_t *lhs, baryon_rsp256_t *rhs);

bool baryon_rsp256_eq_rsp16(baryon_rsp256_t *lhs, baryon_rsp16_t *rhs);

bool baryon_rsp256_eq_rsp2k(baryon_rsp256_t *lhs, baryon_rsp2k_t *rhs);

bool baryon_rsp2k_eq_rsp256(baryon_rsp2k_t *lhs, baryon_rsp256_t *rhs);

bool baryon_rsp2k_eq_rsp32k(baryon_rsp2k_t *lhs, baryon_rsp32k_t *rhs);

bool baryon_rsp32k_eq_rsp2k(baryon_rsp32k_t *lhs, baryon_rsp2k_t *rhs);

#endif // __GSI__BARYON__TEST__COMPARATORS_H__
