/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__LIBGVML_ELEMENT_WISE_H__
#define __GSI__BARYON__LIBGVML_ELEMENT_WISE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

#include "libgvml.h"

void gvml_cpy_imm_16(enum gvml_vr16 vdst, uint16_t val);

void gvml_add_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1,
                  enum gvml_vr16 vsrc2);

void gvml_mul_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1,
                  enum gvml_vr16 vsrc2);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBGVML_ELEMENT_WISE_H__
