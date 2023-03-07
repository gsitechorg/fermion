#ifndef __GSI__BARYON__LIBSYS__ERROR_H__
#define __GSI__BARYON__LIBSYS__ERROR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

#define GSI_ENOMEM     12   /* Out of memory */
#define GSI_EINVAL     22   /* Invalid argument */
#define GSI_EHOSTDOWN  112  /* Host is down */
#define gsi_status(err) (-GSI_ ## err)

#define __gsi_is_err(_type_, _status_) ((_type_)(_status_) < 0)

static inline bool GSI_IS_ERR(gsi_status_t e)
{
  return __gsi_is_err(gsi_status_t, e);
}

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBSYS__ERROR_H__
