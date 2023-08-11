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

#ifndef __BARYON_TEST_MATVEC_H__
#define __BARYON_TEST_MATVEC_H__

#include <stddef.h>
#include <stdint.h>

#include <gtest/gtest.h>

#include <gsi/libsys.h>

struct common_dev_host {
  char buffer[64];
  uint16_t k;
  uint16_t n;
  uint64_t in_mem_hndl1;
  uint64_t in_mem_hndl2;
  uint64_t out_mem_hndl1;
  uint64_t counter;
} __attribute__((packed));

uint16_t r_analytic(size_t i);
void *increment_p_i16(void *p, uint32_t n32s);
uint16_t indirect_p_i16(void *p, uint32_t index32);
uint16_t *alloc_i16s(unsigned int count);
uint16_t *alloc_random_i16s(unsigned int count);
void initialize_A(uint32_t k, uint16_t *a);
void initialize_B(uint32_t k, uint32_t n, uint16_t *B);

gsi_prod_status_t baryon_test_matvec_device(void *in_buf, void *out_buf);

#endif // __BARYON_TEST_MATVEC_H__
