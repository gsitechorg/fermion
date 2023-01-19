#ifndef LEPTON_GSI_LIBGDL_H
#define LEPTON_GSI_LIBGDL_H

#include <inttypes.h>

#include "libsys.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    GSI_DRV_MAX_BOARDS                    = 16,

    GSI_SYS_MAX_CONTEXTS_PER_BOARD        = 8,
    GSI_SYS_MAX_STREAMS_PER_CONTEXT       = 32,

    GSI_MAX_APUCS_PER_APU                 = 4,

    GSI_MAX_APU_COUNT                     = 1,
    GSI_MAX_APUC_COUNT                    = GSI_MAX_APU_COUNT * GSI_MAX_APUCS_PER_APU,
    GSI_TASK_QUEUE_PER_APUC               = 8,
    GSI_TASK_QUEUE_COUNT                  = GSI_MAX_APUC_COUNT * GSI_TASK_QUEUE_PER_APUC,
    GSI_TASK_DESC_POOL_COUNT              = GSI_MAX_APUC_COUNT * GSI_TASK_QUEUE_PER_APUC * 2,

    GSI_MAX_APU_COUNT_SIM                 = 8,
    GSI_MAX_APUC_COUNT_SIM                = GSI_MAX_APU_COUNT_SIM * GSI_MAX_APUCS_PER_APU,
    GSI_TASK_QUEUE_COUNT_SIM              = GSI_MAX_APUC_COUNT_SIM * GSI_TASK_QUEUE_PER_APUC,
};


#define GDL_MAX_NUM_CONTEXTS GSI_DRV_MAX_BOARDS
#define GDL_MAX_DEVICE_NAME_LENGTH 64
#define GDL_TEMPORARY_DEFAULT_MEM_BUF NULL
#define GDL_TEMPORARY_DEFAULT_MEM_BUF_SIZE 0
#define GDL_TEMPORARY_DEFAULT_CORE_INDEX 0



typedef uintptr_t gdl_context_handle_t;
typedef uintptr_t gdl_mem_handle_t;

#define GDL_MEM_HANDLE_NULL ((const gdl_mem_handle_t){ 0 })

typedef enum {
    GDL_CONTEXT_READY,
    GDL_CONTEXT_BUSY,
    GDL_CONTEXT_INVALID,
} gdl_context_status_t;



struct gdl_context_desc {
    char parent_device_name[GDL_MAX_DEVICE_NAME_LENGTH];
    gdl_context_handle_t ctx_id;
    unsigned int num_apucs;
    unsigned int num_apus;
    gdl_context_status_t status;
    unsigned long long  mem_size;
    unsigned int hw_general_info;
};

typedef enum {
    GDL_CONST_MAPPED_POOL,
    GDL_DYNAMIC_MAPPED_POOL,
} gdl_mem_pools;

typedef enum {
    GDL_TASK_GENERAL_ERROR,
    GDL_TASK_COMPLETED,
    GDL_TASK_TIMEDOUT,
    GDL_TASK_DMA_ERROR,
    GDL_TASK_BUS_ERROR,
    GDL_TASK_KFAULT_ERROR,
    GDL_TASK_TEMPERATURE_ERROR,
    GDL_TASK_UBUS_ERROR,
} gdl_task_comp_status;

typedef enum {
    GDL_USER_MAPPING,
} gdl_mapping_type;

struct gdl_mem_buffer {
    gdl_mem_handle_t ptr;
    unsigned int size;
};


int gdl_context_count_get(unsigned int *count);
int gdl_context_desc_get(struct gdl_context_desc *ctx_desc, unsigned int count);
int gdl_context_alloc(gdl_context_handle_t ctx_handler,
                        const unsigned long long const_mapped_size_req,
                        unsigned long long *const_mapped_size_recv,
                        unsigned long long *dynamic_mapped_size_recv);
gdl_mem_handle_t gdl_mem_alloc_nonull(gdl_context_handle_t ctx_handler, unsigned long long size, gdl_mem_pools pool);
void gdl_mem_free(gdl_mem_handle_t buffer);

uint32_t ptr_to_u32(void *p);
void* u32_to_ptr(uint32_t p);
//uint32_t GDL_TASK(gsi_prod_status_t (*name)(void*, void*));
//#define GDL_TASK(name)
//    gsi_prod_status_t name(void*, void*);
//unsigned int gdl_task_lookup(const unsigned int **pptr, const char *sym_name);
//#define GDL_TASK_LOOKUP(ptr) (ptr ? *ptr : gdl_task_lookup(&ptr, #ptr))
#define GDL_TASK(name) ptr_to_u32((void*)GSI_TASK_##name)


int gdl_run_task_timeout(gdl_context_handle_t ctx_handler,
                        unsigned int code_offset,
                        gdl_mem_handle_t inp,
                        gdl_mem_handle_t outp,
                        struct gdl_mem_buffer *mem_buf,
                        unsigned int buf_size,
                        unsigned int apuc_idx,
                        gdl_task_comp_status *comp,
                        unsigned int ms_timeout,
                        gdl_mapping_type map_type);


int gdl_context_free(gdl_context_handle_t ctx_handler);
int gdl_init(void);
int gdl_exit(void);
int gdl_mem_cpy_from_dev(void *dst, gdl_mem_handle_t src, unsigned long long size);
int gdl_mem_cpy_to_dev(gdl_mem_handle_t dst, const void *src, unsigned long long size);
void *gdl_mem_handle_to_host_ptr(gdl_mem_handle_t handle);



#ifdef __cplusplus
}
#endif

#endif // LEPTON_GSI_LIBGDL_H
