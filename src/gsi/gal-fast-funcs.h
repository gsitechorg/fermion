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

#ifndef __GSI__BARYON__GAL_FAST_FUNCS_H__
#define __GSI__BARYON__GAL_FAST_FUNCS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "libgal.h"

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

static inline __attribute__((always_inline))
bool gal_fast_l2dma_sync(gal_l2dma_hndl_t *ioxs, uint32_t apc_id, bool do_blocking)
{
    return true;
}

static inline __attribute__((always_inline))
void gal_fast_l2dma_async_memcpy_init(uint32_t apc_id)
{
    return;
}

static inline __attribute__((always_inline))
int gal_fast_cache_dcache_invalidate_mlines(uint32_t start_addr, uint32_t size)
{
    return 0;
}

static inline __attribute__((always_inline))
void gal_fast_sync_many_blocking(gal_l2dma_hndl_t **ioxs, int count)
{
    return;
}

static inline __attribute__((always_inline))
int gal_fast_cache_dcache_flush_mlines(uint32_t start_addr, uint32_t size)
{
    return 0;
}

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__GAL_FAST_FUNCS_H__
