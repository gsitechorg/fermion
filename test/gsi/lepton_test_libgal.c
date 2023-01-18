#include <gsi/gal-fast-funcs.h>
#include <gsi/libgal.h>
#include <gsi/libgvml_memory.h>
#include <stdint.h>

#include "lepton_test_libgvml.h"
#include "lepton_test_libgal.h"

static inline __attribute__((always_inline))
void my_dma_l2_to_l1_32k(enum gvml_vm_reg vmr)
{
  gal_fast_l2dma_l2_ready_rst_all();
  for (uint8_t bank = 0; bank < 4; bank++) {
    gvml_load_vmr_16(vmr, bank, bank == (4 - 1), bank << 1);
  }
}

static inline __attribute__((always_inline))
void my_dma_l1_to_l2_32k(enum gvml_vm_reg vmr)
{
  gal_fast_l2dma_l2_ready_rst_all();
  for (uint8_t bank = 0; bank < 4; bank++) {
    gvml_store_vmr_16(vmr, bank, bank == (4 - 1), bank * 2);
  }
}

void lepton_test_gal_mem_to_l2_to_mem() {
  struct gal_fast_l2dma_l4_l2_transaction transactions;

  uint16_t *p = malloc(LEPTON_NUM_PLATS_PER_APUC * sizeof(uint16_t));
  for (size_t i = 0; i < LEPTON_NUM_PLATS_PER_APUC; i += 1) {
    p[i] = (i & 0xFFFF);
  }

  transactions.l4_addr = p;
  gal_fast_l2dma_mem_to_l2_start(0, 1, &transactions, GAL_L2DMA_L2_READY_SET);
  gal_fast_l2dma_mem_to_l2_start(1, 1, &transactions, GAL_L2DMA_L2_READY_SET);

  my_dma_l2_to_l1_32k(GVML_VM_0);
  gvml_load_16(GVML_VR16_0, GVML_VM_0);
  gvml_store_16(GVML_VM_1, GVML_VR16_0);
  my_dma_l1_to_l2_32k(GVML_VM_1);

  uint16_t *q = malloc(LEPTON_NUM_PLATS_PER_APUC * sizeof(uint16_t));
  transactions.l4_addr = q;
  gal_fast_l2dma_l2_to_mem_start(0, 1, &transactions, GAL_L2DMA_L2_READY_SET);
  gal_fast_l2dma_l2_to_mem_start(1, 1, &transactions, GAL_L2DMA_L2_READY_SET);

  for (size_t i = 0; i < LEPTON_NUM_PLATS_PER_APUC; i += 1) {
    if (p[i] != q[i]) {
      LEPTON_FAIL_TEST("Expected q[%zu] to be 0x%04X but was 0x%04X\n",
                       i, p[i], q[i]);
      break;
    }
  }

  free(p);
  free(q);
}

void lepton_test_libgal() {
  LEPTON_RUN_GVML_TEST(lepton_test_gal_mem_to_l2_to_mem);
}
