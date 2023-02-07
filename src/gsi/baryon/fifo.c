#include <stdlib.h>
#include <string.h>

#include "fifo.h"

void baryon_init_rsp32k_fifo(baryon_rsp32k_fifo_t *rsp32k_fifo) {
  rsp32k_fifo->length = 0;
}

void baryon_init_rsp2k_fifo(baryon_rsp2k_fifo_t *rsp2k_fifo) {
  rsp2k_fifo->length = 0;
}

void baryon_free_rsp32k_fifo(baryon_rsp32k_fifo_t *rsp32k_fifo) {
  if (rsp32k_fifo != NULL) {
    free(rsp32k_fifo);
  }
}

void baryon_free_rsp2k_fifo(baryon_rsp2k_fifo_t *rsp2k_fifo) {
  if (rsp2k_fifo != NULL) {
    free(rsp2k_fifo);
  }
}

int baryon_rsp32k_fifo_enqueue(baryon_rsp32k_fifo_t *rsp32k_fifo,
                               uint16_t value) {
  if (rsp32k_fifo->length == BARYON_FIFO_SIZE) {
    return 1;
  }
  rsp32k_fifo->buffer[rsp32k_fifo->length] = value;
  rsp32k_fifo->length += 1;
  return 0;
}

int baryon_rsp2k_fifo_enqueue(baryon_rsp2k_fifo_t *rsp2k_fifo,
                              uint16_t value[BARYON_NUM_HALF_BANKS_PER_APUC]) {
  if (rsp2k_fifo->length == BARYON_FIFO_SIZE) {
    return 1;
  }
  memcpy(rsp2k_fifo->buffer[rsp2k_fifo->length], value, BARYON_RSP2K_FIFO_SIZE);
  rsp2k_fifo->length += 1;
  return 0;
}

int baryon_rsp32k_fifo_deque(baryon_rsp32k_fifo_t *rsp32k_fifo,
                             uint16_t *value) {
  if (rsp32k_fifo->length == BARYON_FIFO_SIZE) {
    return 1;
  }
  rsp32k_fifo->length -= 1;
  *value = rsp32k_fifo->buffer[rsp32k_fifo->length];
  return 0;
}

int baryon_rsp2k_fifo_deque(baryon_rsp2k_fifo_t *rsp2k_fifo,
                            uint16_t value[BARYON_NUM_HALF_BANKS_PER_APUC]) {
  if (rsp2k_fifo->length == BARYON_FIFO_SIZE) {
    return 1;
  }
  rsp2k_fifo->length -= 1;
  memcpy(value, rsp2k_fifo->buffer[rsp2k_fifo->length],
         BARYON_RSP2K_FIFO_SIZE);
  return 0;
}
