/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__RSP_H__
#define __GSI__BARYON__RSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void rsp_outstanding_pushn(uint32_t count);

void rsp_outstanding_push(void);

void rsp_outstanding_pop(void);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__RSP_H__
