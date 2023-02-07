#ifndef __GSI__BARYON__FIFO_H__
#define __GSI__BARYON__FIFO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>

#include "constants.h"

#define BARYON_FIFO_SIZE 16
#define BARYON_RSP32K_FIFO_SIZE sizeof(uint16_t)
#define BARYON_RSP2K_FIFO_SIZE \
  BARYON_NUM_HALF_BANKS_PER_APUC * sizeof(uint16_t)

typedef struct baryon_rsp32k_fifo_t {
  size_t length;
  uint16_t buffer[BARYON_FIFO_SIZE];
} baryon_rsp32k_fifo_t;

typedef struct baryon_rsp2k_fifo_t {
  size_t length;
  uint16_t buffer[BARYON_FIFO_SIZE][BARYON_NUM_HALF_BANKS_PER_APUC];
} baryon_rsp2k_fifo_t;

void baryon_init_rsp32k_fifo(baryon_rsp32k_fifo_t *rsp32k_fifo);

void baryon_init_rsp2k_fifo(baryon_rsp2k_fifo_t *rsp2k_fifo);

void baryon_free_rsp32k_fifo(baryon_rsp32k_fifo_t *rsp32k_fifo);

void baryon_free_rsp2k_fifo(baryon_rsp2k_fifo_t *rsp2k_fifo);

int baryon_rsp32k_fifo_enqueue(baryon_rsp32k_fifo_t *rsp32k_fifo,
                               uint16_t value);

int baryon_rsp2k_fifo_enqueue(baryon_rsp2k_fifo_t *rsp2k_fifo,
                              uint16_t value[BARYON_NUM_HALF_BANKS_PER_APUC]);

int baryon_rsp32k_fifo_deque(baryon_rsp32k_fifo_t *rsp32k_fifo,
                             uint16_t *value);

int baryon_rsp2k_fifo_deque(baryon_rsp2k_fifo_t *rsp2k_fifo,
                            uint16_t value[BARYON_NUM_HALF_BANKS_PER_APUC]);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__FIFO_H__
