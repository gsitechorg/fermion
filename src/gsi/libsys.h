#ifndef BARYON_GSI_LIBSYS_H
#define BARYON_GSI_LIBSYS_H

#include <stdbool.h>
#include <inttypes.h>

#include <gsi/libsys/assert.h>
#include <gsi/libsys/log.h>

#ifdef __cplusplus
extern "C" {
#endif

// TODO: we should figure out how to move this out of public header files:
typedef uint16_t u16;

typedef int gsi_status_t;
typedef signed int gsi_prod_int_t;
typedef gsi_prod_int_t gsi_prod_status_t;

gsi_status_t gsi_libsys_init(const char *argv0, bool log_to_screen);
void gsi_libsys_exit(void);

int gsi_sim_destroy_simulator(void);

#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_LIBSYS_H
