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

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <gsi/gal-fast-funcs.h>
#include <gsi/baryon/constants.h>
#include <gsi/libgal.h>
#include <gsi/libgdl.h>
#include <gsi/libgvml.h>
#include <gsi/libgvml_element_wise.h>
#include <gsi/libgvml_memory.h>

#include <gtest/gtest.h>

#include "test_matvec.h"

#define _32K 32768
#define _16K 16384
#define _8K 8192
#define _4K 4096
#define _2K 2048
#define _1K 1024
#define MAX_NUM_VMRS GVML_VM_47

static struct gdl_context_desc contexts_desc[GDL_MAX_NUM_CONTEXTS];

enum {
  _32k_16b_elem = _32K * sizeof(uint16_t),
  _16k_16b_elem = _16K * sizeof(uint16_t)
};

static inline __attribute__((always_inline)) void
my_dma_l4_to_l2_16k(int apc_id, uint16_t *p16) {
  struct gal_fast_l2dma_l4_l2_transaction txn = {
      .num_steps = 1,
      .step_size_num_512b_chunk = _16k_16b_elem / 512,
      .l4_addr = p16,
      .l2_mode = GAL_L2T_MODE_64,
      .l2_col_group = 0,
  };
  gal_fast_l2dma_mem_to_l2_start(apc_id, 1, &txn, GAL_L2DMA_L2_READY_SET);
}

static inline __attribute__((always_inline)) void
my_dma_l4_to_l2_32k(uint16_t *p16) {
  my_dma_l4_to_l2_16k(0, p16);
  my_dma_l4_to_l2_16k(1, p16 + _16K);
  gal_fast_l2dma_async_memcpy_end(0);
  gal_fast_l2dma_async_memcpy_end(1);
}

static inline __attribute__((always_inline)) void
my_dma_l2_to_l1_32k(enum gvml_vm_reg vmr) {
  gal_fast_l2dma_l2_ready_rst_all();
  for (uint8_t bank = 0; bank < 4; bank++)
    gvml_load_vmr_16(vmr, bank, bank == (4 - 1), bank << 1);
}

static inline __attribute__((always_inline)) void
my_dma_l2_to_l4_16k(int apc_id, uint16_t *p16) {
  struct gal_fast_l2dma_l4_l2_transaction txn = {
      .num_steps = 1,
      .step_size_num_512b_chunk = _16k_16b_elem / 512,
      .l4_addr = p16,
      .l2_mode = GAL_L2T_MODE_64,
      .l2_col_group = 0,
  };
  gal_fast_l2dma_l2_to_mem_start(apc_id, 1, &txn, GAL_L2DMA_L2_READY_SET);
}

static inline __attribute__((always_inline)) void
my_dma_l2_to_l4_32k(uint16_t *p16) {
  my_dma_l2_to_l4_16k(0, p16);
  my_dma_l2_to_l4_16k(1, p16 + _16K);
  gal_fast_l2dma_async_memcpy_end(0);
  gal_fast_l2dma_async_memcpy_end(1);
}

static inline __attribute__((always_inline))
void my_dma_l1_to_l2_32k(enum gvml_vm_reg vmr)
{
  gal_fast_l2dma_l2_ready_rst_all();
  for (uint8_t bank = 0; bank < 4; bank++)
    gvml_store_vmr_16(vmr, bank, bank == (4 - 1), bank * 2);

}

static inline __attribute__((always_inline)) void
my_dma_l1_to_l4(uint16_t *p16, uint16_t num_vmrs, enum gvml_vm_reg vm_start) {
  for (uint16_t i = 0; i < num_vmrs; i++) {
    my_dma_l1_to_l2_32k(static_cast<enum gvml_vm_reg>(vm_start + i));
    my_dma_l2_to_l4_32k(p16 + _32K * i);
  }
}

uint16_t r_analytic(size_t i) {
  uint16_t A = 5;
  uint16_t B = -50;
  uint16_t C = 285;
  uint16_t l = i % 10;
  return A * (l * l) + B * l + C;
}

void *increment_p_i16(void *p, uint32_t n32s) {
  uint16_t *result = (uint16_t *)p;
  result += n32s;
  return result;
}

uint16_t indirect_p_i16(void *p, uint32_t index32) {
  uint16_t *temp = (uint16_t *)p;
  uint16_t result = temp[index32];
  return result;
}

uint16_t *alloc_i16s(unsigned int count) {
  uint16_t *xs = (uint16_t *) malloc(count * sizeof(uint16_t));
  return xs;
}

uint16_t *alloc_random_i16s(unsigned int count) {
  uint16_t *xs = alloc_i16s(count);
  for (size_t i = 0; i < count; ++i) {
    xs[i] = (uint16_t) random() % 16;
  }
  return xs;
}

gsi_prod_status_t baryon_test_matvec_device(void *in_buf, void *out_buf) {
  gvml_init_once();

  struct common_dev_host *p = (struct common_dev_host *) in_buf;

  size_t k = p->k;

  gal_mem_handle_t a_ptr = (gal_mem_handle_t) p->in_mem_hndl1;
  gal_mem_handle_t b_ptr = (gal_mem_handle_t) p->in_mem_hndl2;
  gal_mem_handle_t c_ptr = (gal_mem_handle_t) p->out_mem_hndl1;

  void *A_l4 = gal_mem_handle_to_apu_ptr(a_ptr);
  void *B_l4 = gal_mem_handle_to_apu_ptr(b_ptr);
  void *C_l4 = gal_mem_handle_to_apu_ptr(c_ptr);

  enum gvml_vr16 B_vr = GVML_VR16_1;
  enum gvml_vr16 C_vr = GVML_VR16_2;
  enum gvml_vr16 T_vr = GVML_VR16_3;

  gvml_cpy_imm_16(C_vr, 0x0000);

  enum gvml_vm_reg L1_reg_B = GVML_VM_0;
  enum gvml_vm_reg L1_reg_C = GVML_VM_2;

  for (size_t k_ = 0; k_ < k; k_ += 1) {
    my_dma_l4_to_l2_32k(static_cast<uint16_t *>(B_l4));
    B_l4 = increment_p_i16(B_l4, BARYON_NUM_PLATS_PER_APUC);
    my_dma_l2_to_l1_32k(L1_reg_B);
    gvml_load_16(B_vr, L1_reg_B);
    uint16_t Ak_ = indirect_p_i16(A_l4, k_);
    gvml_cpy_imm_16(T_vr, Ak_);
    gvml_mul_u16(T_vr, T_vr, B_vr);
    gvml_add_u16(C_vr, C_vr, T_vr);
  }
  gvml_store_16(L1_reg_C, C_vr);
  my_dma_l1_to_l4(static_cast<uint16_t *>(C_l4), 1, L1_reg_C);
  gvml_exit();
  return 0;
}

void initialize_A(uint32_t k, uint16_t *a) {
  for (size_t i = 0; i < k; i++) {
    a[i] = i;
  }
}

void initialize_B(uint32_t k, uint32_t n, uint16_t *B) {
  for (size_t j = 0; j < k; j++) {
    for (size_t i = 0; i < n; i++) {
      B[j * n + i] = (i + j) % 10;
    }
  }
}

TEST(matvec, test_matvec) {
  size_t k = 10;
  size_t n = BARYON_NUM_PLATS_PER_APUC;

  size_t a_size = k * sizeof(uint16_t);
  size_t b_size = k * n * sizeof(uint16_t);
  size_t c_size = n * sizeof(uint16_t);

  uint16_t *a = (uint16_t *) malloc(a_size);
  initialize_A(k, a);

  uint16_t *b = (uint16_t *) malloc(b_size);
  initialize_B(k, n, b);

  uint16_t *c = (uint16_t *) malloc(c_size);

  gsi_libsys_init("MatVec host!", true);
  gdl_init();

  uint32_t num_ctxs;
  gdl_context_count_get(&num_ctxs);
  gdl_context_desc_get(contexts_desc, num_ctxs);

  struct gdl_context_desc *context_desc = &contexts_desc[0];
  uint64_t ctx_id = context_desc->ctx_id;

  ASSERT_FALSE(gdl_context_alloc(ctx_id, 0, NULL, NULL))
      << "Failed to allocate gdl_context";

  gdl_mem_handle_t a_handle =
      gdl_mem_alloc_nonull(ctx_id, a_size, GDL_CONST_MAPPED_POOL);

  gdl_mem_handle_t b_handle =
      gdl_mem_alloc_nonull(ctx_id, b_size, GDL_CONST_MAPPED_POOL);

  gdl_mem_handle_t c_handle =
      gdl_mem_alloc_nonull(ctx_id, c_size, GDL_CONST_MAPPED_POOL);

  gdl_mem_handle_t cmn_struct_mem_handle = gdl_mem_alloc_nonull(
      ctx_id,
      sizeof(struct common_dev_host),
      GDL_CONST_MAPPED_POOL);

  struct common_dev_host *cmn_pointer =
      (struct common_dev_host *)gdl_mem_handle_to_host_ptr(
          cmn_struct_mem_handle);

  cmn_pointer->k = (uint16_t) k;
  cmn_pointer->n = (uint16_t) n;
  cmn_pointer->in_mem_hndl1 = (uint64_t) a_handle;
  cmn_pointer->in_mem_hndl2 = (uint64_t) b_handle;
  cmn_pointer->out_mem_hndl1 = (uint64_t) c_handle;

  gdl_mem_cpy_to_dev(a_handle, a, a_size);
  gdl_mem_cpy_to_dev(b_handle, b, b_size);

  // NOTE: segfaults ...
  /* gdl_run_task_timeout(ctx_id, */
  /*                      (uintptr_t) baryon_test_matvec_device, */
  /*                      cmn_struct_mem_handle, */
  /*                      GDL_MEM_HANDLE_NULL, */
  /*                      GDL_TEMPORARY_DEFAULT_MEM_BUF, */
  /*                      GDL_TEMPORARY_DEFAULT_MEM_BUF_SIZE, */
  /*                      GDL_TEMPORARY_DEFAULT_CORE_INDEX, */
  /*                      NULL, */
  /*                      200, */
  /*                      GDL_USER_MAPPING); */

  ASSERT_FALSE(baryon_test_matvec_device((void *)cmn_struct_mem_handle,
                                         (void *)GDL_MEM_HANDLE_NULL))
      << "Failed to run baryon_test_matvec_device";

  gdl_mem_cpy_from_dev(c, c_handle, c_size);

  bool success = true;
  for (size_t i = 0; i < n; i += 1) {
    uint16_t actual_value = c[i];
    uint16_t expected_value = r_analytic(i);
    ASSERT_EQ(actual_value, expected_value)
        << "(HOST) Error in C computation in element " << i
        << ", Ref[i] = " << expected_value
        << ", C[i] = " << actual_value;
  }

  gdl_mem_free(a_handle);
  gdl_mem_free(b_handle);
  gdl_mem_free(c_handle);
  gdl_mem_free(cmn_struct_mem_handle);

  gdl_exit();
  gsi_sim_destroy_simulator();
  /* gsi_libsys_exit(); */

  free(c);
  free(b);
  free(a);
}
