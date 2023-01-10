#include <stdio.h>

#include <gsi/libsys.h>

gsi_status_t gsi_libsys_init(const char *argv0, bool log_to_screen) {
    printf("gsi_libsys_init()\n");
    return 0;
}

int gsi_sim_destroy_simulator(void) {
    printf("gsi_sim_destroy_simulator()\n");
    return 0;
}
