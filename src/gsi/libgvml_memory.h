/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__LIBGVML_MEMORY_H__
#define __GSI__BARYON__LIBGVML_MEMORY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "libgvml.h"

void gvml_load_16(enum gvml_vr16 dst, enum gvml_vm_reg vm_reg);
void gvml_load_vmr_16(enum gvml_vm_reg vmdst, unsigned int bank, bool l2_ready_set, unsigned int l2_start_byte);

void gvml_store_16(enum gvml_vm_reg vmdst, enum gvml_vr16 vsrc);
void gvml_store_vmr_16(enum gvml_vm_reg vmsrc, unsigned int bank, bool l2_ready_set, unsigned int l2_start_byte);


#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBGVML_MEMORY_H__
