#include <stddef.h>
#include <stdio.h>

#include <gsi/baryon/gvml_fragments.h>

#include "libapl.h"
#include "libgvml.h"
#include "libgvml_element_wise.h"
#include "libgvml_memory.h"

baryon_apuc_t apuc;
baryon_seu_layer_t seu_layer;

void baryon_init() {
  /* apuc = malloc(sizeof(baryon_apuc_t)); */
  baryon_init_apuc(&apuc);

  /* seu_layer = malloc(sizeof(baryon_seu_layer_t)); */
  baryon_init_seu_layer(&seu_layer);
}

int gvml_apl_init() {
  apl_set_sm_reg(SM_REG_4, 0xFFFF);
  apl_set_sm_reg(SM_REG_5, 0x0001);
  apl_set_sm_reg(SM_REG_6, 0x1111);
  apl_set_sm_reg(SM_REG_7, 0x0101);
  apl_set_sm_reg(SM_REG_8, 0x000F);
  apl_set_sm_reg(SM_REG_9, 0x0F0F);
  apl_set_sm_reg(SM_REG_10, 0x0707);
  apl_set_sm_reg(SM_REG_11, 0x5555);
  apl_set_sm_reg(SM_REG_12, 0x3333);
  apl_set_sm_reg(SM_REG_13, 0x00FF);
  apl_set_sm_reg(SM_REG_14, 0x001F);
  apl_set_sm_reg(SM_REG_15, 0x003F);

  apl_set_rn_reg(RN_REG_8, VR16_T0);
  apl_set_rn_reg(RN_REG_9, VR16_T1);
  apl_set_rn_reg(RN_REG_10, VR16_T2);
  apl_set_rn_reg(RN_REG_11, VR16_T3);
  apl_set_rn_reg(RN_REG_12, VR16_T4);
  apl_set_rn_reg(RN_REG_13, VR16_T5);
  apl_set_rn_reg(RN_REG_14, VR16_T6);
  apl_set_rn_reg(RN_REG_15, VR16_FLAGS);

  return 0;
}

void gvml_init() {
  baryon_init();
  gvml_apl_init();
}

static bool init_done = false;

void gvml_init_once() {
  if (!init_done) {
    init_done = true;
    gvml_init();
  }
}

void baryon_exit() {
  /* printf("baryon_free_apuc(apuc)\n"); */
  /* baryon_free_apuc(apuc); */
  /* apuc = (baryon_apuc_t *) NULL; */

  /* printf("baryon_free_seu_layer(seu_layer)\n"); */
  /* baryon_free_seu_layer(seu_layer); */
  /* seu_layer = (baryon_seu_layer_t *) NULL; */
}

void gvml_exit() {
  baryon_exit();
  init_done = false;
}

void gvml_add_u16(enum gvml_vr16 res, enum gvml_vr16 x, enum gvml_vr16 y) {
  apl_set_rn_reg(RN_REG_G0, x);
  apl_set_rn_reg(RN_REG_G1, y);
  apl_set_rn_reg(RN_REG_G2, res);
  add_u16(RN_REG_G2, RN_REG_G0, RN_REG_G1);
}

void gvml_cpy_imm_16(enum gvml_vr16 vdst, uint16_t val) {
  apl_set_rn_reg(RN_REG_0, vdst);
  apl_set_sm_reg(SM_REG_0, val);
  cpy_imm_16(RN_REG_0, SM_REG_0);
}

void gvml_mul_u16(enum gvml_vr16 res, enum gvml_vr16 x, enum gvml_vr16 y) {
  uint32_t i;

  apl_set_rn_reg(RN_REG_G0, x);
  apl_set_rn_reg(RN_REG_G1, y);
  init_mul_16_7tmp(RN_REG_G0, RN_REG_G1, RN_REG_T4, RN_REG_T0, RN_REG_T1,
                   RN_REG_T2, RN_REG_T5, RN_REG_T6);

  apl_set_rn_reg(RN_REG_G3, res);
  apl_set_sm_reg(SM_REG1, 0x3fff);
  apl_set_sm_reg(SM_REG0, 1 << 1);
  for (i = 1; i < 13; i += 2) {
    apl_set_sm_reg(SM_REG0, 1 << i);
    _3to2_mul_16_7tmp(RN_REG_T3, RN_REG_T4, RN_REG_T0, RN_REG_T1, RN_REG_T2,
                      RN_REG_T5, RN_REG_G3, RN_REG_T6, SM_REG0, SM_REG1);
    apl_set_sm_reg(SM_REG0, 2 << i);
    _3to2_mul_16_7tmp(RN_REG_T3, RN_REG_T0, RN_REG_T4, RN_REG_T1, RN_REG_T5,
                      RN_REG_T2, RN_REG_G3, RN_REG_T6, SM_REG0, SM_REG1);
  }
  _3to2_mul_16_7tmp_iter_msk_13(RN_REG_T3, RN_REG_T4, RN_REG_T0, RN_REG_T1,
                                RN_REG_T2, RN_REG_T5, RN_REG_G3, RN_REG_T6,
                                SM_REG1);
  apl_set_sm_reg(SM_REG0, 2 << i);
  _3to2_mul_16_7tmp_last(RN_REG_T3, RN_REG_T0, RN_REG_T4, RN_REG_T1, RN_REG_T5,
                         RN_REG_T2, RN_REG_G3, RN_REG_T6, SM_REG1);

  apl_set_rn_reg(RN_REG_G2, res);
  mul_u16_u16xu16_7t(RN_REG_T6, RN_REG_T3, RN_REG_G2, RN_REG_T5, RN_REG_T4);
}

static inline __attribute__((always_inline)) uint8_t
belex_gal_encode_l2_addr(uint32_t byte_idx, uint32_t bit_idx) {
  return (uint8_t)((byte_idx << GSI_L2_CTL_ROW_ADDR_BIT_IDX_BITS) | bit_idx);
}

static inline __attribute__((always_inline)) uint16_t
belex_gal_vm_reg_to_set_ext(size_t vm_reg, uint32_t *parity_grp_p,
                            uint32_t *parity_row_p) {
  uint32_t parity_set = vm_reg >> 1;
  uint32_t parity_grp = vm_reg & 1;
  uint32_t row = parity_set * GSI_L1_VA_SET_ADDR_ROWS;
  *parity_row_p = row + (2 * APL_VM_ROWS_PER_U16);
  row += APL_VM_ROWS_PER_U16 * parity_grp;
  *parity_grp_p = parity_grp;
  return (uint16_t) row;
}

static inline __attribute__((always_inline)) uint16_t
load_16_parity_mask(bool parity_grp) {
  return (uint16_t)(0x0808 << parity_grp);
}

static inline __attribute__((always_inline)) uint16_t
store_16_parity_mask(bool parity_grp) {
  return (uint16_t)(0x0001 << (4 * parity_grp));
}

static inline __attribute__((always_inline)) uint32_t
bank_group_row_to_addr(uint32_t bank_id, uint32_t group_id, uint32_t row_id) {
  return (bank_id << 11) | (group_id << 9) | row_id;
}

void gvml_load_16(enum gvml_vr16 dst, enum gvml_vm_reg vm_reg) {
  uint32_t parity_grp, parity_src;
  uint16_t src = belex_gal_vm_reg_to_set_ext(vm_reg,
                                             &parity_grp,
                                             &parity_src);
  uint16_t parity_mask = load_16_parity_mask(parity_grp);

  apl_set_rn_reg(RN_REG_G0, dst);
  apl_set_l1_reg(L1_ADDR_REG0, src);
  apl_set_l1_reg(L1_ADDR_REG1, parity_src);
  apl_set_sm_reg(SM_REG0, parity_mask);

  load_16_t0(RN_REG_G0, L1_ADDR_REG0, L1_ADDR_REG1, SM_REG0);
}

void gvml_store_16(enum gvml_vm_reg vm_reg, enum gvml_vr16 src) {
  uint32_t parity_grp, parity_dst;
  uint16_t dst = belex_gal_vm_reg_to_set_ext(vm_reg,
                                             &parity_grp,
                                             &parity_dst);
  uint16_t parity_mask = store_16_parity_mask(parity_grp);

  apl_set_rn_reg(RN_REG_G0, src);
  apl_set_l1_reg(L1_ADDR_REG0, dst);
  apl_set_l1_reg(L1_ADDR_REG1, parity_dst);
  apl_set_sm_reg(SM_REG0, parity_mask);

  store_16_t0(L1_ADDR_REG0, L1_ADDR_REG1, SM_REG0, RN_REG_G0);
}

void belex_copy_l2_to_l1_byte(uint32_t dst, uint32_t parity_dst, uint32_t src) {
  apl_set_l1_reg(L1_ADDR_REG_0, dst);
  apl_set_l1_reg(L1_ADDR_REG_1, parity_dst);
  apl_set_l2_reg(L2_ADDR_REG_0, src);
  copy_l2_to_l1_byte(L1_ADDR_REG_0, L1_ADDR_REG_1, L2_ADDR_REG_0);
}

static inline __attribute__((always_inline))
void _copy_N_l2_to_l1(uint8_t l1_bank_id,
                      uint32_t vm_reg,
                      uint32_t l1_grp,
                      size_t num_bytes,
                      bool l2_ready_set,
                      uint8_t l2_start_byte)
{
  size_t i;
  uint32_t l1_parity_grp, l1_parity_row;
  uint32_t l1_grp_row = belex_gal_vm_reg_to_set_ext(vm_reg,
                                                &l1_parity_grp,
                                                &l1_parity_row);
  uint8_t l2_addr;

  for (i = 0; i < num_bytes; i++, l1_grp += 2, l1_parity_grp += 2) {
    if (l1_grp >= GSI_L1_NUM_GRPS) {
      l1_grp = 0;
      vm_reg++;
      l1_grp_row = belex_gal_vm_reg_to_set_ext(vm_reg,
                                               &l1_parity_grp,
                                               &l1_parity_row);
    }
    l2_addr = belex_gal_encode_l2_addr(l2_start_byte + i, 0);

    uint32_t dst_addr = bank_group_row_to_addr(l1_bank_id,
                                               l1_grp,
                                               l1_grp_row);

    uint32_t parity_dst_addr = bank_group_row_to_addr(l1_bank_id,
                                                      l1_parity_grp,
                                                      l1_parity_row);

    belex_copy_l2_to_l1_byte(dst_addr,
                             parity_dst_addr,
                             l2_addr);
  }

  if (l2_ready_set) {
    l2_end();
  }
}


void gvml_load_vmr_16(enum gvml_vm_reg vm_reg, unsigned int l1_bank_id,
                      bool l2_ready_set, unsigned int l2_start_byte) {
  _copy_N_l2_to_l1(l1_bank_id, vm_reg, 0, 2, l2_ready_set, l2_start_byte);
}

void belex_copy_l1_to_l2_byte(uint32_t dst, uint32_t src, uint32_t parity_src) {
  apl_set_l2_reg(L2_ADDR_REG_0, dst);
  apl_set_l1_reg(L1_ADDR_REG_0, src);
  apl_set_l1_reg(L1_ADDR_REG_1, parity_src);
  copy_l1_to_l2_byte(L2_ADDR_REG_0, L1_ADDR_REG_0, L1_ADDR_REG_1);
}

static inline __attribute__((always_inline))
void _copy_N_l1_to_l2(uint8_t l1_bank_id,
                      uint32_t vm_reg,
                      uint32_t l1_grp,
                      size_t num_bytes,
                      bool l2_ready_set,
                      uint8_t l2_start_byte)
{
  size_t i;
  uint32_t l1_parity_grp, l1_parity_row;
  uint32_t l1_grp_row = belex_gal_vm_reg_to_set_ext(vm_reg,
                                                &l1_parity_grp,
                                                &l1_parity_row);
  uint8_t l2_addr;

  for (i = 0; i < num_bytes; i++, l1_grp += 2, l1_parity_grp += 2) {
    if (l1_grp >= GSI_L1_NUM_GRPS) {
      l1_grp = 0;
      vm_reg++;
      l1_grp_row = belex_gal_vm_reg_to_set_ext(vm_reg,
                                               &l1_parity_grp,
                                               &l1_parity_row);
    }
    l2_addr = belex_gal_encode_l2_addr(l2_start_byte + i, 0);

    uint32_t src_addr = bank_group_row_to_addr(l1_bank_id,
                                               l1_grp,
                                               l1_grp_row);

    uint32_t parity_src_addr = bank_group_row_to_addr(l1_bank_id,
                                                      l1_parity_grp,
                                                      l1_parity_row);

    belex_copy_l1_to_l2_byte(l2_addr,
                             src_addr,
                             parity_src_addr);
  }

  if (l2_ready_set) {
    l2_end();
  }
}

void gvml_store_vmr_16(enum gvml_vm_reg vm_reg, unsigned int l1_bank_id,
                       bool l2_ready_set, unsigned int l2_start_byte) {
  _copy_N_l1_to_l2(l1_bank_id, vm_reg, 0, 2, l2_ready_set, l2_start_byte);
}
