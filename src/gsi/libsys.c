#include <stdio.h>
#include <string.h>

#include "libsys.h"

gsi_status_t gsi_libsys_init(const char *argv0, bool log_to_screen) {
    printf("gsi_libsys_init()\n");
    return 0;
}

int gsi_sim_destroy_simulator(void) {
    printf("gsi_sim_destroy_simulator()\n");
    return 0;
}

void gsi_libsys_exit(void) {
  // nothing
}

const char *gsi_status_errorstr(gsi_status_t status)
{
  if (!status)
    return "success";
  if (status > 0)
    return "positive";
  if (!GSI_IS_ERR(status))
    return "unknown";

  return strerror(-status);
}
