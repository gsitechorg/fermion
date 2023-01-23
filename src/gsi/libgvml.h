#ifndef BARYON_GSI_LIBGVML_H
#define BARYON_GSI_LIBGVML_H

#include "baryon/apuc.h"
#include "baryon/seu_layer.h"

#ifdef __cplusplus
extern "C" {
#endif

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

extern baryon_apuc_t apuc;
extern baryon_seu_layer_t seu_layer;

void baryon_init(void);
void baryon_exit(void);

int gvml_apl_init(void);
void gvml_init(void);
void gvml_init_once(void);
void gvml_exit(void);

#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_LIBGVML_H
