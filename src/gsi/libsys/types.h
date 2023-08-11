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

#ifndef __GSI__BARYON__LIBSYS__TYPES_H__
#define __GSI__BARYON__LIBSYS__TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GSI_PACKED __attribute__((packed))

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif // MAX

#define likely(x) __builtin_expect((x), true)
#define unlikely(x) __builtin_expect((x), false)

typedef uint16_t u16;
typedef int gsi_status_t;
typedef signed int gsi_prod_int_t;
typedef gsi_prod_int_t gsi_prod_status_t;

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBSYS__TYPES_H__
