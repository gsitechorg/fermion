#ifndef LEPTON_GSI_LIBGAL_H
#define LEPTON_GSI_LIBGAL_H

#include <inttypes.h>

#include <gsi/libsys.h>

#ifdef __cplusplus
extern "C" {
#endif

enum gal_l2t_mode_type {
    GAL_L2T_MODE_8 = 0,
    GAL_L2T_MODE_16 = 1,
    GAL_L2T_MODE_32 = 2,
    GAL_L2T_MODE_64 = 3,
};

enum gal_l2dma_cmd_attr {
    GAL_L2DMA_L2_READY_NOP = 0,
    GAL_L2DMA_L2_READY_RST = 2,
    GAL_L2DMA_L2_READY_SET = 3,
};

typedef uint64_t gal_mem_handle_t;

void *gal_mem_handle_to_apu_ptr(gal_mem_handle_t handle);

#define GAL_INCLUDE_INIT_TASK

#define GAL_TASK_ENTRY_POINT(name, in, out)                                    \
    gsi_prod_status_t name(void* in, void* out);                        \
    gsi_prod_status_t (*GSI_TASK_##name)(void*,void*) = name;                  \
    gsi_prod_status_t name(void* in __attribute__((unused)),            \
                                  void* out __attribute__((unused)))




#ifdef __cplusplus
}
#endif

#endif // LEPTON_GSI_LIBGAL_H
