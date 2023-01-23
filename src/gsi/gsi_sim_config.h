#ifndef BARYON_GSI_SIM_CONFIG_H
#define BARYON_GSI_SIM_CONFIG_H

#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

struct gsi_sim_contexts {
    unsigned long long mem_size;
    unsigned int apu_count;
    unsigned int apucs_per_apu;
};


#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_SIM_CONFIG_H
