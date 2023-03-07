#ifndef __GSI__BARYON__LIBSYS_H__
#define __GSI__BARYON__LIBSYS_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <inttypes.h>

#include "libsys/assert.h"
#include "libsys/debug.h"
#include "libsys/error.h"
#include "libsys/libc.h"
#include "libsys/log.h"
#include "libsys/types.h"

gsi_status_t gsi_libsys_init(const char *argv0, bool log_to_screen);

void gsi_libsys_exit(void);

int gsi_sim_destroy_simulator(void);

const char *gsi_status_errorstr(gsi_status_t status);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBSYS_H__
