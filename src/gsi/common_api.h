#ifndef __GSI__BARYON__COMMON_API_H__
#define __GSI__BARYON__COMMON_API_H__

#include "baryon/apuc.h"
#include "baryon/seu_layer.h"

extern baryon_apuc_t apuc;
extern baryon_seu_layer_t seu_layer;

void baryon_init(void);
void baryon_exit(void);

#endif // __GSI__BARYON__COMMON_API_H__
