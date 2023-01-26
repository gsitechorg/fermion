#ifndef BARYON_GSI_LIBGAL_H
#define BARYON_GSI_LIBGAL_H

#include <inttypes.h>

#include "libsys.h"

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_LIBGAL_H
