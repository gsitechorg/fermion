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
