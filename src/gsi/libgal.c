#include <stdio.h>

#include <gsi/libgal.h>
#include <gsi/gal-fast-funcs.h>

#define COLUMNS 32768
extern uint16_t l2_memory[COLUMNS];

void gal_fast_l2dma_async_memcpy_end(uint32_t apc_id) {
}

void gal_fast_l2dma_l2_ready_rst_all() {
}

void gal_fast_l2dma_l2_to_mem_start(uint32_t apc_id,
                uint32_t num_transactions,
                struct gal_fast_l2dma_l4_l2_transaction *transactions,
                enum gal_l2dma_cmd_attr l2_ready_attr) {
    // TODO: this is a special case that is used in my_dma_l2_to_l4_32k()
    uint16_t *p = transactions->l4_addr;
    for (uint32_t i=0; i < COLUMNS/2; i++) {
        p[i] = l2_memory[i+apc_id*COLUMNS/2];
    }
}

void gal_fast_l2dma_mem_to_l2_start(uint32_t apc_id,
                uint32_t num_transactions,
                struct gal_fast_l2dma_l4_l2_transaction *transactions,
                enum gal_l2dma_cmd_attr l2_ready_attr) {
    // TODO: this is a special case that is used in my_dma_l4_to_l2_32k()
    uint16_t *p = transactions->l4_addr;
    for (uint32_t i=0; i < COLUMNS/2; i++) {
        l2_memory[i+apc_id*COLUMNS/2] = p[i];
    }
}

void *gal_mem_handle_to_apu_ptr(gal_mem_handle_t handle) {
    return (void*)handle;
}
