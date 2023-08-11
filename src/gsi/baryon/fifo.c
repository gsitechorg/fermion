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

#include <stdlib.h>
#include <string.h>

#include "fifo.h"

void baryon_init_apc_rsp_fifo(baryon_apc_rsp_fifo_t *apc_rsp_fifo) {
  apc_rsp_fifo->length = 1;
  apc_rsp_fifo->cursor = -1;
}

void baryon_init_apuc_rsp_fifo(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo) {
  baryon_init_apc_rsp_fifo(&apuc_rsp_fifo->queues[0]);
  baryon_init_apc_rsp_fifo(&apuc_rsp_fifo->queues[1]);
  apuc_rsp_fifo->active = NULL;
}

void baryon_free_apc_rsp_fifo(baryon_apc_rsp_fifo_t *apc_rsp_fifo) {
  if (apc_rsp_fifo != NULL) {
    free(apc_rsp_fifo);
  }
}

void baryon_free_apuc_rsp_fifo(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo) {
  if (apuc_rsp_fifo != NULL) {
    free(apuc_rsp_fifo);
  }
}

int baryon_apc_rsp_fifo_enqueue(baryon_apc_rsp_fifo_t *apc_rsp_fifo,
                                baryon_rsp_fifo_msg_t *rsp_fifo_msg) {
  // NOTE: Add 1 to BARYON_FIFO_CAPACITY for the initial offset
  if (apc_rsp_fifo->length == BARYON_FIFO_CAPACITY + 1) {
    return 1;
  }
  size_t index =
      (apc_rsp_fifo->cursor + apc_rsp_fifo->length) % BARYON_FIFO_CAPACITY;
  memcpy(&apc_rsp_fifo->buffer[index], rsp_fifo_msg,
         sizeof(baryon_rsp_fifo_msg_t));
  apc_rsp_fifo->length += 1;
  return 0;
}

int baryon_apuc_rsp_rd(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo, size_t apc_id) {
  baryon_apc_rsp_fifo_t *apc_rsp_fifo = &apuc_rsp_fifo->queues[apc_id];
  if (apc_rsp_fifo->length == 0) {
    return 1;
  }
  apc_rsp_fifo->length -= 1;
  apc_rsp_fifo->cursor = (apc_rsp_fifo->cursor + 1) % BARYON_FIFO_CAPACITY;
  apuc_rsp_fifo->active = apc_rsp_fifo;
  return 0;
}

uint32_t baryon_rd_rsp2k_reg(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo,
                             size_t bank_id) {
  baryon_apc_rsp_fifo_t *apc_rsp_fifo = apuc_rsp_fifo->active;
  baryon_rsp_fifo_msg_t *rsp_fifo_msg =
    &apc_rsp_fifo->buffer[apc_rsp_fifo->cursor];
  size_t lower_half_bank = bank_id;
  size_t upper_half_bank = lower_half_bank + 4;
  uint32_t value = (rsp_fifo_msg->rsp2k[upper_half_bank] << 16)
    | rsp_fifo_msg->rsp2k[lower_half_bank];
  return value;
}

uint8_t baryon_rd_rsp32k_reg(baryon_apuc_rsp_fifo_t *apuc_rsp_fifo) {
  baryon_apc_rsp_fifo_t *apc_rsp_fifo = apuc_rsp_fifo->active;
  baryon_rsp_fifo_msg_t *rsp_fifo_msg =
      &apc_rsp_fifo->buffer[apc_rsp_fifo->cursor];
  return rsp_fifo_msg->rsp32k;
}
