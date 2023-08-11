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

#ifndef __GSI__BARYON__FIFO_H__
#define __GSI__BARYON__FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>

#include "constants.h"

#define BARYON_FIFO_CAPACITY 16

typedef struct baryon_rsp_fifo_msg_t {
  uint8_t rsp32k;
  uint16_t rsp2k[BARYON_NUM_HALF_BANKS_PER_APC];
} baryon_rsp_fifo_msg_t;

typedef struct baryon_apc_rsp_fifo_t {
  size_t length;
  ssize_t cursor;
  baryon_rsp_fifo_msg_t buffer[BARYON_FIFO_CAPACITY];
} baryon_apc_rsp_fifo_t;

typedef struct baryon_apuc_rsp_fifo_t {
  baryon_apc_rsp_fifo_t queues[BARYON_NUM_APCS_PER_APUC];
  baryon_apc_rsp_fifo_t *active;
} baryon_apuc_rsp_fifo_t;

void baryon_init_apc_rsp_fifo(baryon_apc_rsp_fifo_t *apc_rsp_fifo);

void baryon_init_apuc_rsp_fifo(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo);

void baryon_free_apc_rsp_fifo(baryon_apc_rsp_fifo_t *apc_rsp_fifo);

void baryon_free_apuc_rsp_fifo(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo);

int baryon_apc_rsp_fifo_enqueue(baryon_apc_rsp_fifo_t *apc_rsp_fifo,
                                baryon_rsp_fifo_msg_t *message);

int baryon_apuc_rsp_rd(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo, size_t apc_id);

uint32_t baryon_rd_rsp2k_reg(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo,
                             size_t bank_id);

uint8_t baryon_rd_rsp32k_reg(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__FIFO_H__
