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
  if (apc_rsp_fifo->length == BARYON_FIFO_CAPACITY) {
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
  size_t lower_half_bank = bank_id * 2;
  size_t upper_half_bank = lower_half_bank + 1;
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
