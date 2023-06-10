#ifndef __GSI__BARYON_LIBGVML_H__
#define __GSI__BARYON_LIBGVML_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "baryon/apuc.h"
#include "baryon/seu_layer.h"
#include "libapl.h"

#define APL_RSP_RD apl_rsp_rd
#define APL_RD_RSP32K_REG apl_rd_rsp32k_reg
#define APL_RD_RSP2K_REG apl_rd_rsp2k_reg
#define FREE_RSP_FIFO(apuc_id) APL_RSP_RD(apuc_id);

enum gvml_vr16 {
    GVML_VR16_0 = 0,
    GVML_VR16_1 = 1,
    GVML_VR16_2 = 2,
    GVML_VR16_3 = 3,
    GVML_VR16_4 = 4,
    GVML_VR16_5 = 5,
    GVML_VR16_6 = 6,
    GVML_VR16_7 = 7,
    GVML_VR16_8 = 8,
    GVML_VR16_9 = 9,
    GVML_VR16_10    = 10,
    GVML_VR16_11    = 11,
    GVML_VR16_12    = 12,
    GVML_VR16_13    = 13,
    GVML_VR16_14    = 14,
    GVML_VR16_IDX   = 15,
};

/* Flag IDs (in flags Vector Register) */
enum gvml_flgs {
    /* pre-defined flags for the flags vector-register */
    C_FLAG          = SM_BIT_0,             /* Carry in/out flag */
    B_FLAG          = SM_BIT_1,             /* Borrow in/out flag */
    OF_FLAG         = SM_BIT_2,             /* Overflow flag */
    PE_FLAG         = SM_BIT_3,             /* Parity error */
    M16_FLAG        = SM_BIT_4,             /* marker with 1 set for (each vector-register-index % 16) == 0 */
    M256_FLAG       = SM_BIT_5,             /* marker with 1 set for (each vector-register-index % 256) == 0 */
    M2K_FLAG        = SM_BIT_6,             /* marker with 1 set for (each vector-register-index % 2048) == 0 */

    /* Markers for general purpose usage Callee must preserve */
    GP0_FLAG        = SM_BIT_7,
    GP1_FLAG        = SM_BIT_8,
    GP2_FLAG        = SM_BIT_9,
    GP3_FLAG        = SM_BIT_10,
    GP4_FLAG        = SM_BIT_11,

    /* Markers for general purpose usage Callee may overwrite preserve */
    TMP0_FLAG       = SM_BIT_12,
    TMP1_FLAG       = SM_BIT_13,
    TMP2_FLAG       = SM_BIT_14,
    TMP3_FLAG       = SM_BIT_15,
};

/* MMB Flag IDs (in flags Vector Register) */
enum mmb_flgs {
    /* pre-defined flags for the flags vector-register */
    /* C_FLAG          = SM_BIT_0,             /\* Carry in/out flag *\/ */
    /* B_FLAG          = SM_BIT_1,             /\* Borrow in/out flag *\/ */
    /* OF_FLAG         = SM_BIT_2,             /\* Overflow flag *\/ */
    /* PE_FLAG         = SM_BIT_3,             /\* Parity error *\/ */

    /* Markers for general purpose usage Callee must preserve */
    GP0_MRK         = SM_BIT_4,
    GP1_MRK         = SM_BIT_5,
    GP2_MRK         = SM_BIT_6,
    GP3_MRK         = SM_BIT_7,
    GP4_MRK         = SM_BIT_8,
    GP5_MRK         = SM_BIT_9,
    GP6_MRK         = SM_BIT_10,
    GP7_MRK         = SM_BIT_11,

    /* Markers for general purpose usage Callee may overwrite preserve */
    TMP0_MRK        = SM_BIT_12,
    TMP1_MRK        = SM_BIT_13,
    TMP2_MRK        = SM_BIT_14,
    TMP3_MRK        = SM_BIT_15,

    /* General purpose vector-markers */
    FIRST_GP0_MRK = GP0_MRK,
    LAST_GP7_MRK = GP7_MRK,

    /* Temporary vector-markers */
    FIRST_TMP0_MRK = TMP0_MRK,
    LAST_TMP3_MRK = TMP3_MRK
};


/* Flag bitmasks (correspond to enum gvml_flgs flag IDs) */
enum gvml_mrks_n_flgs {
    GVML_C_FLAG     = 1 << C_FLAG,          /* Carry in/out flag */
    GVML_B_FLAG     = 1 << B_FLAG,          /* Borrow in/out flag */
    GVML_OF_FLAG    = 1 << OF_FLAG,         /* Overflow flag */
    GVML_PE_FLAG    = 1 << PE_FLAG,         /* Parity error flag */
    GVML_16B_MRK    = 1 << M16_FLAG,        /* marker with 1 set for each (vector-register-index % 16) == 0 */
    GVML_256B_MRK   = 1 << M256_FLAG,       /* marker with 1 set for each (vector-register-index % 256) == 0 */
    GVML_2KB_MRK    = 1 << M2K_FLAG,        /* marker with 1 set for each (vector-register-index % 2048) == 0 */
    GVML_MRK0       = 1 << GP0_FLAG,        /* General purpose marker */
    GVML_MRK1       = 1 << GP1_FLAG,        /* General purpose marker */
    GVML_MRK2       = 1 << GP2_FLAG,        /* General purpose marker */
    GVML_MRK3       = 1 << GP3_FLAG,        /* General purpose marker */
    GVML_MRK4       = 1 << GP4_FLAG,        /* General purpose marker */
};

enum mmb_vr16 {
  VR16_G0 = GVML_VR16_0,
  VR16_G1 = GVML_VR16_1,
  VR16_G2 = GVML_VR16_2,
  VR16_G3 = GVML_VR16_3,
  VR16_G4 = GVML_VR16_4,
  VR16_G5 = GVML_VR16_5,
  VR16_G6 = GVML_VR16_6,
  VR16_G7 = GVML_VR16_7,
  VR16_G8 = GVML_VR16_8,
  VR16_G9 = GVML_VR16_9,
  VR16_G10 = GVML_VR16_10,
  VR16_G11 = GVML_VR16_11,
  VR16_G12 = GVML_VR16_12,
  VR16_G13 = GVML_VR16_13,
  VR16_G14 = GVML_VR16_14,
  VR16_M4_IDX = 15,
  VR16_T0 = 16,
  VR16_T1 = 17,
  VR16_T2 = 18,
  VR16_T3 = 19,
  VR16_T4 = 20,
  VR16_T5 = 21,
  VR16_T6 = 22,
  VR16_FLAGS = 23,

  VR16_G_FIRST = VR16_G0,
  VR16_G_LAST = VR16_G14,
  VR16_T_FIRST = VR16_T0,
  VR16_T_LAST = VR16_T6,

  APL_INVAL_ROWNUM = 0xff,
};

enum gvml_power2_sizes {
    GVML_P2_1       = 0,
    GVML_P2_2       = 1,
    GVML_P2_4       = 2,
    GVML_P2_8       = 3,
    GVML_P2_16      = 4,
    GVML_P2_32      = 5,
    GVML_P2_64      = 6,
    GVML_P2_128     = 7,
    GVML_P2_256     = 8,
    GVML_P2_512     = 9,
    GVML_P2_1K      = 10,
    GVML_P2_2K      = 11,
    GVML_P2_4K      = 12,
    GVML_P2_8K      = 13,
    GVML_P2_16K     = 14,
    GVML_P2_32K     = 15,
};

enum gvml_vm_reg {
    GVML_VM_0   = 0,
    GVML_VM_1   = 1,
    GVML_VM_2   = 2,
    GVML_VM_3   = 3,
    GVML_VM_4   = 4,
    GVML_VM_5   = 5,
    GVML_VM_6   = 6,
    GVML_VM_7   = 7,
    GVML_VM_8   = 8,
    GVML_VM_9   = 9,
    GVML_VM_10  = 10,
    GVML_VM_11  = 11,
    GVML_VM_12  = 12,
    GVML_VM_13  = 13,
    GVML_VM_14  = 14,
    GVML_VM_15  = 15,
    GVML_VM_16  = 16,
    GVML_VM_17  = 17,
    GVML_VM_18  = 18,
    GVML_VM_19  = 19,
    GVML_VM_20  = 20,
    GVML_VM_21  = 21,
    GVML_VM_22  = 22,
    GVML_VM_23  = 23,
    GVML_VM_24  = 24,
    GVML_VM_25  = 25,
    GVML_VM_26  = 26,
    GVML_VM_27  = 27,
    GVML_VM_28  = 28,
    GVML_VM_29  = 29,
    GVML_VM_30  = 30,
    GVML_VM_31  = 31,
    GVML_VM_32  = 32,
    GVML_VM_33  = 33,
    GVML_VM_34  = 34,
    GVML_VM_35  = 35,
    GVML_VM_36  = 36,
    GVML_VM_37  = 37,
    GVML_VM_38  = 38,
    GVML_VM_39  = 39,
    GVML_VM_40  = 40,
    GVML_VM_41  = 41,
    GVML_VM_42  = 42,
    GVML_VM_43  = 43,
    GVML_VM_44  = 44,
    GVML_VM_45  = 45,
    GVML_VM_46  = 46,
    GVML_VM_47  = 47,
};

int gvml_apl_init(void);
void gvml_init(void);
void gvml_init_once(void);
void gvml_exit(void);
bool is_gvml_init(void);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON_LIBGVML_H__
