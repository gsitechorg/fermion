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

#include <stdio.h>

#include "baryon/apuc.h"
#include "baryon/constants.h"
#include "libgal.h"
#include "gal-fast-funcs.h"

extern baryon_apuc_t apuc;

void gal_fast_l2dma_async_memcpy_end(uint32_t apc_id) {
  // nothing to do
}

void gal_fast_l2dma_l2_ready_rst_all() {
  // nothing to do
}

void *gal_malloc(uint32_t size)
{
  return malloc(size);
}

void gal_free(const void *p)
{
  free((void *)p);
}

void gal_fast_l2dma_l2_to_mem_start(uint32_t apc_id,
                uint32_t num_transactions,
                struct gal_fast_l2dma_l4_l2_transaction *transactions,
                enum gal_l2dma_cmd_attr l2_ready_attr) {
    // TODO: this is a special case that is used in my_dma_l2_to_l4_32k()
    uint16_t *p = transactions->l4_addr;
    for (size_t l2_byte = 0; l2_byte < 8; l2_byte += 1) {
        size_t bank = l2_byte / 2;
        size_t lower_l4_plat = (bank * BARYON_NUM_PLATS_PER_HALF_BANK * 2);
        size_t upper_l4_plat =
            lower_l4_plat + (BARYON_NUM_PLATS_PER_HALF_BANK * 2);
        for (size_t l2_offset = 0; l2_offset < 8; l2_offset += 1) {
            size_t l2_addr = l2_byte * 16 + l2_offset;
            size_t group = 2 * (l2_byte % 2) + (l2_offset / 4);
            size_t row = l2_offset % 4;
            size_t section = group * 4 + row;
            for (size_t l4_plat = lower_l4_plat,
                        l2_plat = apc_id * BARYON_NUM_PLATS_PER_HALF_BANK * 2;
                 l4_plat < upper_l4_plat; l4_plat += 1, l2_plat += 1) {
              p[l4_plat] = (p[l4_plat] ^ (p[l4_plat] & (1 << section))) |
                           (apuc.l2[l2_addr][l2_plat] << section);
            }
        }
    }
}

void gal_fast_l2dma_mem_to_l2_start(uint32_t apc_id,
                uint32_t num_transactions,
                struct gal_fast_l2dma_l4_l2_transaction *transactions,
                enum gal_l2dma_cmd_attr l2_ready_attr) {
    // TODO: this is a special case that is used in my_dma_l4_to_l2_32k()
    uint16_t *p = transactions->l4_addr;
    for (size_t l2_byte = 0; l2_byte < 8; l2_byte += 1) {
        size_t bank = l2_byte / 2;
        size_t lower_l4_plat = (bank * BARYON_NUM_PLATS_PER_HALF_BANK * 2);
        size_t upper_l4_plat =
            lower_l4_plat + (BARYON_NUM_PLATS_PER_HALF_BANK * 2);

        for (size_t l2_offset = 0; l2_offset < 8; l2_offset += 1) {
          size_t l2_addr = l2_byte * 16 + l2_offset;
          size_t group = 2 * (l2_byte % 2) + (l2_offset / 4);
          size_t row = l2_offset % 4;
          size_t section = group * 4 + row;
          for (size_t l4_plat = lower_l4_plat,
                      l2_plat = apc_id * BARYON_NUM_PLATS_PER_HALF_BANK * 2;
               l4_plat < upper_l4_plat; l4_plat += 1, l2_plat += 1) {
            apuc.l2[l2_addr][l2_plat] = (p[l4_plat] & (1 << section));
          }
        }
    }
}

void *gal_mem_handle_to_apu_ptr(gal_mem_handle_t handle) {
    return (void*)handle;
}

void gal_init(void) {
  // empty
}

void gal_exit(void) {
  // empty
}

int gal_set_l2dma_dma_mode(enum gal_l2dma_dma_mode dma_mode) {
  return 0;
}

void gal_pm_start() {
  return;
}

void gal_pm_stop() {
  return;
}

unsigned long long gal_get_pm_cycle_count(bool is_live) {
  return apuc.num_instructions;
}

unsigned long long gal_get_pm_inst_count(bool is_live) {
  return apuc.num_instructions;
}
