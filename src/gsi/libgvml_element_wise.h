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

#ifndef __GSI__BARYON__LIBGVML_ELEMENT_WISE_H__
#define __GSI__BARYON__LIBGVML_ELEMENT_WISE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "libgvml.h"

void gvml_cpy_imm_16(enum gvml_vr16 vdst, uint16_t val);

void gvml_add_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1,
                  enum gvml_vr16 vsrc2);

void gvml_mul_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1,
                  enum gvml_vr16 vsrc2);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBGVML_ELEMENT_WISE_H__
