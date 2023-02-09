#ifndef __BARYON__GSI__LIBAPL_H__
#define __BARYON__GSI__LIBAPL_H__

#include <stdint.h>

enum sm_regs {
  SM_REG_0 = 0,
  SM_REG_1 = 1,
  SM_REG_2 = 2,
  SM_REG_3 = 3,
  SM_REG_4 = 4,
  SM_REG_5 = 5,
  SM_REG_6 = 6,
  SM_REG_7 = 7,
  SM_REG_8 = 8,
  SM_REG_9 = 9,
  SM_REG_10 = 10,
  SM_REG_11 = 11,
  SM_REG_12 = 12,
  SM_REG_13 = 13,
  SM_REG_14 = 14,
  SM_REG_15 = 15,

  NUM_SM_REGS,
};

enum rownum_regs {
  RN_REG_0 = 0,
  RN_REG_1 = 1,
  RN_REG_2 = 2,
  RN_REG_3 = 3,
  RN_REG_4 = 4,
  RN_REG_5 = 5,
  RN_REG_6 = 6,
  RN_REG_7 = 7,
  RN_REG_8 = 8,
  RN_REG_9 = 9,
  RN_REG_10 = 10,
  RN_REG_11 = 11,
  RN_REG_12 = 12,
  RN_REG_13 = 13,
  RN_REG_14 = 14,
  RN_REG_15 = 15,

  NUM_RN_REGS = 16,
};

enum rowmask_regs {
  RE_REG_0 = 0,
  RE_REG_1 = 1,
  RE_REG_2 = 2,
  RE_REG_3 = 3,
  NUM_RE_REGS = 4,

  EWE_REG_0 = 0,
  EWE_REG_1 = 1,
  EWE_REG_2 = 2,
  EWE_REG_3 = 3,
  NUM_EWE_REGS = 4,
};

enum l1_addr_regs {
  L1_ADDR_REG_0 = 0,
  L1_ADDR_REG_1 = 1,
  L1_ADDR_REG_2 = 2,
  L1_ADDR_REG_3 = 3,

  NUM_L1_ADDR_REGS,
};

enum gal_l2_addr_regs {
  L2_ADDR_REG_0 = 0,
  GAL_NUM_L2_ADDR_REGS,
};

enum section_bits {
  SB_0 = 0,
  SB_1 = 1,
  SB_2 = 2,
  SB_3 = 3,
  SB_4 = 4,
  SB_5 = 5,
  SB_6 = 6,
  SB_7 = 7,
  SB_8 = 8,
  SB_9 = 9,
  SB_10 = 10,
  SB_11 = 11,
  SB_12 = 12,
  SB_13 = 13,
  SB_14 = 14,
  SB_15 = 15,
  SB_16 = 16,
  SB_17 = 17,
  SB_18 = 18,
  SB_19 = 19,
  SB_20 = 20,
  SB_21 = 21,
  SB_22 = 22,
  SB_23 = 23,

  NUM_SBS = 16,

};

enum sm_bits {
  SM_BIT_0 = 0,
  SM_BIT_1 = 1,
  SM_BIT_2 = 2,
  SM_BIT_3 = 3,
  SM_BIT_4 = 4,
  SM_BIT_5 = 5,
  SM_BIT_6 = 6,
  SM_BIT_7 = 7,
  SM_BIT_8 = 8,
  SM_BIT_9 = 9,
  SM_BIT_10 = 10,
  SM_BIT_11 = 11,
  SM_BIT_12 = 12,
  SM_BIT_13 = 13,
  SM_BIT_14 = 14,
  SM_BIT_15 = 15,

};

enum gsi_apc_defs {
  GSI_APC_NUM_COLS = 4096,
  GSI_APC_NUM_HALF_BANKS = 2,                             /* number of half banks in a bank */
  GSI_APC_NUM_HALF_BANK_COLS = GSI_APC_NUM_COLS / GSI_APC_NUM_HALF_BANKS,
  GSI_APC_CBUS_BITS = 64,

  GSI_APC_PARITY_SET_BITS = 3,
  GSI_APC_PARITY_SET = 1 << GSI_APC_PARITY_SET_BITS,      /* 1 parity bit per 8 data bits */
  GSI_APC_PARITY_SET_MASK = GSI_APC_PARITY_SET - 1,
};

enum gsi_l1_defs {
  GSI_L1_NUM_BANKS = 4,
  GSI_L1_NUM_GRPS = 4,
  GSI_L1_NUM_DATA_ROWS_PER_GRP = 192,
  GSI_L1_NUM_PARITY_ROWS_PER_GRP = GSI_L1_NUM_DATA_ROWS_PER_GRP / GSI_APC_PARITY_SET,
  GSI_L1_NUM_PHYS_ROWS_PER_GRP = GSI_L1_NUM_DATA_ROWS_PER_GRP + GSI_L1_NUM_PARITY_ROWS_PER_GRP,
  GSI_L1_CTL_ROW_IN_SET_ADDR_BITS = 4,    /* Select 1 of 9 rows to be read or written in the selected L1 Byte */
  GSI_L1_CTL_SET_ADDR_BITS = 5,   /* Select 1 of 24 sets of 9-row L1 Bytes */
  GSI_L1_CTL_ROW_ADDR_BITS = GSI_L1_CTL_ROW_IN_SET_ADDR_BITS + GSI_L1_CTL_SET_ADDR_BITS,
  GSI_L1_CTL_GRP_ADDR_BITS = 2,   /* Select 1 of 4 L1 Groups in the selected L1 Bank */
  GSI_L1_CTL_BANK_ADDR_BITS = 2,  /* Select 1 of 4 L1 Banks */
  GSI_L1_L2_CTL_L1_ADDR_BITS = GSI_L1_CTL_ROW_ADDR_BITS + GSI_L1_CTL_GRP_ADDR_BITS + GSI_L1_CTL_BANK_ADDR_BITS,
  GSI_L1_VA_SET_DATA_ADDR_BITS = GSI_APC_PARITY_SET_BITS,
  GSI_L1_VA_SET_DATA_ROWS = 1 << GSI_L1_VA_SET_DATA_ADDR_BITS,
  GSI_L1_VA_SET_PARITY_ADDR_BITS = 1,
  GSI_L1_VA_SET_PARITY_ROWS = 1,
  GSI_L1_VA_SET_ADDR_BITS = GSI_L1_VA_SET_DATA_ADDR_BITS + GSI_L1_VA_SET_PARITY_ADDR_BITS,
  GSI_L1_VA_SET_ADDR_ROWS = 1 << GSI_L1_VA_SET_ADDR_BITS,
  GSI_L1_VA_NUM_SETS = GSI_L1_NUM_DATA_ROWS_PER_GRP / (1 << GSI_L1_VA_SET_DATA_ADDR_BITS),
  GSI_L1_VA_NUM_ROWS = GSI_L1_VA_SET_ADDR_ROWS * GSI_L1_VA_NUM_SETS,
};

enum gsi_l2_defs {
  GSI_L2_CTL_ROW_ADDR_BIT_IDX_BITS = 4,
  GSI_L2_CTL_ROW_ADDR_BIT_IDX_MASK = (1 << GSI_L2_CTL_ROW_ADDR_BIT_IDX_BITS) - 1,
  GSI_L2_CTL_ROW_ADDR_BYTE_IDX_BITS = 3,
  GSI_L2_CTL_ROW_ADDR_BYTE_IDX_MASK = (1 << GSI_L2_CTL_ROW_ADDR_BYTE_IDX_BITS) - 1,
  GSI_L2_CTL_ROW_ADDR_BITS = GSI_L2_CTL_ROW_ADDR_BIT_IDX_BITS + GSI_L2_CTL_ROW_ADDR_BYTE_IDX_BITS,
  GSI_L2_CTL_ROW_ADDR_MASK = (1 << GSI_L2_CTL_ROW_ADDR_BITS) - 1,
  GSI_L1_L2_CTL_L2_ADDR_BITS = GSI_L2_CTL_ROW_ADDR_BITS,
};

/* rownum registers used for function parameters */
#define RN_REG_G0 RN_REG_0
#define RN_REG_G1 RN_REG_1
#define RN_REG_G2 RN_REG_2
#define RN_REG_G3 RN_REG_3
#define RN_REG_G4 RN_REG_4
#define RN_REG_G5 RN_REG_5
#define RN_REG_G6 RN_REG_6
#define RN_REG_G7 RN_REG_7

/* rownum registers to hold predefined temporary vector-registers.
* These rownum registers shouldn't change during program execution.
*/
#define RN_REG_T0 RN_REG_8
#define RN_REG_T1 RN_REG_9
#define RN_REG_T2 RN_REG_10
#define RN_REG_T3 RN_REG_11
#define RN_REG_T4 RN_REG_12
#define RN_REG_T5 RN_REG_13
#define RN_REG_T6 RN_REG_14

/* rownum register to hold pre-defined flags vector-registers.
* This rownum register shouldn't change during program execution.
*/
#define RN_REG_FLAGS RN_REG_15


/* l1_addr registers used for function parameters */
#define L1_ADDR_REG0 L1_ADDR_REG_0
#define L1_ADDR_REG1 L1_ADDR_REG_1

/* l1_addr registers holding predefined values */
#define L1_ADDR_REG_RESERVED L1_ADDR_REG_2
#define L1_ADDR_REG_INDEX L1_ADDR_REG_3

#define L2_ADDR_REG0 L2_ADDR_REG_0

#define RE_REG_G0 RE_REG_0
#define RE_REG_G1 RE_REG_1
#define RE_REG_T0 RE_REG_2
#define RE_REG_NO_RE RE_REG_3

#define EWE_REG_G0 EWE_REG_0
#define EWE_REG_G1 EWE_REG_1
#define EWE_REG_T0 EWE_REG_2
#define EWE_REG_NO_EWE EWE_REG_3


/* general purpose smaps registers */
#define SM_REG0 SM_REG_0
#define SM_REG1 SM_REG_1
#define SM_REG2 SM_REG_2
#define SM_REG3 SM_REG_3

/* smaps registers to hold predefined section maps.
* These smaps registers shouldn't change during program execution.
*/
#define SM_0XFFFF SM_REG_4
#define SM_0X0001 SM_REG_5
#define SM_0X1111 SM_REG_6
#define SM_0X0101 SM_REG_7
#define SM_0X000F SM_REG_8
#define SM_0X0F0F SM_REG_9
#define SM_0X0707 SM_REG_10
#define SM_0X5555 SM_REG_11
#define SM_0X3333 SM_REG_12
#define SM_0X00FF SM_REG_13
#define SM_0X001F SM_REG_14
#define SM_0X003F SM_REG_15


/* Flag IDs (in flags Vector Register) */
/* pre-defined flags for the flags vector-register */
#define C_FLAG SM_BIT_0         /* Carry in/out flag */
#define B_FLAG SM_BIT_1         /* Borrow in/out flag */
#define OF_FLAG SM_BIT_2        /* Overflow flag */
#define PE_FLAG SM_BIT_3        /* Parity error */
#define M16_FLAG SM_BIT_4       /* marker with 1 set for (each vector-register-index % 16) == 0 */
#define M256_FLAG SM_BIT_5      /* marker with 1 set for (each vector-register-index % 256) == 0 */
#define M2K_FLAG SM_BIT_6       /* marker with 1 set for (each vector-register-index % 2048) == 0 */

/* Markers for general purpose usage Callee must preserve */
#define GP0_FLAG SM_BIT_7
#define GP1_FLAG SM_BIT_8
#define GP2_FLAG SM_BIT_9
#define GP3_FLAG SM_BIT_10
#define GP4_FLAG SM_BIT_11

/* Markers for general purpose usage Callee may overwrite preserve */
#define TMP0_FLAG SM_BIT_12
#define TMP1_FLAG SM_BIT_13
#define TMP2_FLAG SM_BIT_14
#define TMP3_FLAG SM_BIT_15

/* L1 addressing */
#define APL_VM_ROWS_PER_U16 4

void apl_set_sm_reg(uint32_t sm_reg, uint32_t val);
void apl_set_rn_reg(uint32_t rn_reg, uint32_t val);
void apl_set_re_reg(uint32_t re_reg, uint32_t val);
void apl_set_ewe_reg(uint32_t ewe_reg, uint32_t val);
void apl_set_l1_reg(uint32_t l1_reg, uint32_t val);
void apl_set_l1_reg_ext(uint32_t reg_idx, uint32_t bank_id, uint32_t grp_id,
                        uint32_t grp_row);
void apl_set_l2_reg(uint32_t l2_reg, uint32_t val);

#endif // __BARYON__GSI__LIBAPL_H__
