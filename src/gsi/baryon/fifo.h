/* By Dylon Edwards
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
