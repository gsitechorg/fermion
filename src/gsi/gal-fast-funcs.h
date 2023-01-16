#ifndef LEPTON_GSI_GAL_FAST_FUNCS_H
#define LEPTON_GSI_GAL_FAST_FUNCS_H

#include "libgal.h"

#ifdef __cplusplus
extern "C" {
#endif

struct gal_fast_l2dma_l4_l2_transaction {
    uint64_t num_steps;
    uint64_t step_size_num_512b_chunk;
    void *l4_addr;
    int8_t l2_mode;
    int8_t l2_col_group;
};

void gal_fast_l2dma_async_memcpy_end(uint32_t apc_id);
void gal_fast_l2dma_l2_ready_rst_all();
void gal_fast_l2dma_l2_to_mem_start(uint32_t apc_id,
    uint32_t num_transactions,
    struct gal_fast_l2dma_l4_l2_transaction *transactions,
    enum gal_l2dma_cmd_attr l2_ready_attr);
void gal_fast_l2dma_mem_to_l2_start(uint32_t apc_id,
    uint32_t num_transactions,
    struct gal_fast_l2dma_l4_l2_transaction *transactions,
    enum gal_l2dma_cmd_attr l2_ready_attr);


#ifdef __cplusplus
}
#endif

#endif // LEPTON_GSI_GAL_FAST_FUNCS_H
