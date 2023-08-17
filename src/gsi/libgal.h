/* By Dylon Edwards
 */

#ifndef __GSI__BARYON_LIBGAL_H__
#define __GSI__BARYON_LIBGAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "libsys.h"

#define GAL_L2DMA_APC_ID_0 0
#define GAL_L2DMA_APC_ID_1 1

enum gal_l2t_mode_type {
    GAL_L2T_MODE_8 = 0,
    GAL_L2T_MODE_16 = 1,
    GAL_L2T_MODE_32 = 2,
    GAL_L2T_MODE_64 = 3,
};

enum gal_l2dma_cmd_attr {
    GAL_L2DMA_L2_READY_NOP = 0,
    GAL_L2DMA_L2_READY_RST = 2,
    GAL_L2DMA_L2_READY_SET = 3,
};

enum gal_l2dma_dma_mode {
    GAL_L2DMA_MODE_DIRECT = 0,
    GAL_L2DMA_MODE_INDIRECT = 1,
};

struct gal_l2dma_l2_addr {
    uint8_t l2_col_group;  /* column groups in 64 l2 columns resolution (values 0 - 63) */
    uint8_t l2_byte_row;  /* rows in byte resolution (values 0 - 7) */
} __attribute__((packed));

struct gal_l2dma_l4_l2_transaction {
    uint32_t num_steps;
    uint32_t step_size_num_64b_chunk;  /* number of chunks - each chunk is 64 bytes */
    void *l4_addr;
    int l4_step_stride;  /* in bytes */
    uint8_t l2_mode;
    uint8_t l2_step_col_group;  /* column group step size */
    uint8_t l2_rep_colgrp_stride;
    struct gal_l2dma_l2_addr l2_addr;
  } __attribute__((packed));;

typedef uint64_t gal_mem_handle_t;

typedef void gal_l2dma_hndl_t;

void *gal_mem_handle_to_apu_ptr(gal_mem_handle_t handle);

#define GAL_INCLUDE_INIT_TASK

#define GAL_TASK_ENTRY_POINT(name, in, out)                                    \
    gsi_prod_status_t name(void* in, void* out);                        \
    gsi_prod_status_t (*GSI_TASK_##name)(void*,void*) = name;                  \
    gsi_prod_status_t name(void* in __attribute__((unused)),            \
                                  void* out __attribute__((unused)))

void gal_init(void);
void gal_exit(void);

int gal_set_l2dma_dma_mode(enum gal_l2dma_dma_mode dma_mode);
void *gal_malloc(uint32_t size);
void gal_free(const void *p);

void gal_pm_start(void);
void gal_pm_stop(void);
unsigned long long gal_get_pm_cycle_count(bool is_live);
unsigned long long gal_get_pm_inst_count(bool is_live);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON_LIBGAL_H__
