#ifndef __GSI__BARYON__COMMON_API_H__
#define __GSI__BARYON__COMMON_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "baryon/fifo.h"
#include "baryon/apuc.h"
#include "baryon/seu_layer.h"

extern baryon_apuc_rsp_fifo_t apuc_rsp_fifo;
extern baryon_apuc_t apuc;
extern baryon_seu_layer_t seu_layer;

void baryon_init(void);
void baryon_exit(void);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__COMMON_API_H__
