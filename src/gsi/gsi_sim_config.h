#ifndef __GSI__BARYON__SIM_CONFIG_H__
#define __GSI__BARYON__SIM_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

struct gsi_sim_contexts {
    unsigned long long mem_size;
    unsigned int apu_count;
    unsigned int apucs_per_apu;
};

int gsi_sim_create_simulator(unsigned int num_ctxs,
                             struct gsi_sim_contexts *ctxs);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__SIM_CONFIG_H__
