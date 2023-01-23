#ifndef BARYON_GSI_LIBGVML_ELEMENT_WISE_H
#define BARYON_GSI_LIBGVML_ELEMENT_WISE_H

#include <inttypes.h>

#include "libgvml.h"

#ifdef __cplusplus
extern "C" {
#endif

void gvml_add_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1, enum gvml_vr16 vsrc2);
void gvml_cpy_imm_16(enum gvml_vr16 vdst, uint16_t val);
void gvml_mul_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1, enum gvml_vr16 vsrc2);

#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_LIBGVML_ELEMENT_WISE_H
