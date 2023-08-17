/* By Dylon Edwards
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if __linux__
#include <sys/sysinfo.h>
#elif __APPLE__
#include <sys/sysctl.h>
#include <sys/types.h>
#endif

#include "libgdl.h"

// Ours

void error(char *msg) {
    printf("Error: %s\n", msg);
    printf("Aborting.\n");
    exit(1);
}

// Init/Exit

static bool gdl_initialized;

int gdl_init(void) {
    printf("gdl_init()\n");
    gdl_initialized = true;
    return 0;
}

int gdl_exit(void) {
    printf("gdl_exit()\n");
    gdl_initialized = false;
    return 0;
}

// GDL Context

int gdl_context_alloc(gdl_context_handle_t ctx_handler,
                        const unsigned long long const_mapped_size_req,
                        unsigned long long *const_mapped_size_recv,
                        unsigned long long *dynamic_mapped_size_recv) {
    printf("gdl_context_alloc()\n");
    return 0;
}

int gdl_context_free(gdl_context_handle_t ctx_handler) {
    printf("gdl_context_free()\n");
    return 0;
}

int gdl_context_count_get(unsigned int *count) {
    *count = 1;
    return 0;
}

int gdl_context_desc_get(struct gdl_context_desc *ctx_desc, unsigned int count){
    if (count != 1) {
        error("The count ID must be equal to 1");
    }
    strcpy(ctx_desc->parent_device_name, "Baryon emulator");
    ctx_desc->ctx_id = 1;
    ctx_desc->num_apucs = 4;
    ctx_desc->num_apus = 1;
    ctx_desc->status = 0;
    ctx_desc->mem_size = 1073741824;
    ctx_desc->hw_general_info = 0;
    return 0;
}

int gdl_context_property_get(gdl_context_handle_t ctx_handler,
                             gdl_context_property_t property, long *value) {
  switch (property) {
  case GDL_CONTEXT_MEM_SIZE: {
#ifdef __linux__
    struct sysinfo info;
    if (sysinfo(&info) == -1) {
      error("failed to collect sysinfo");
    }
    *value = info.totalram * info.mem_unit;
#elif __APPLE__
    int mib[2];
    size_t length;
    mib[0] = CTL_HW;
    mib[1] = HW_MEMSIZE;
    length = sizeof(int64_t);
    sysctl(mib, 2, value, &length, NULL, 0);
#else
    error("unsupported OS");
#endif
    break;
  }
  case GDL_CONTEXT_NUM_APUCS:
    *value = 4;
    break;
  case GDL_CONTEXT_STATUS:
    *value = GDL_CONTEXT_READY;
    break;
  case GDL_CONTEXT_NUM_APUS:
    *value = 1;
    break;
  case GDL_CONTEXT_HW_GENERAL_INFO:
    // FIXME: Fill this in ...
    error("not implemented: GDL_CONTEXT_HW_GENERAL_INFO");
    break;
  default:
    error("unsupported GDL context property");
  }
}

// GDL Memory

gdl_mem_handle_t gdl_mem_alloc_nonull(gdl_context_handle_t ctx_handler,
    unsigned long long size, gdl_mem_pools pool) {
    if (ctx_handler != 1) {
        error("gdl_mem_alloc_nonull: The ctx_handler must be equal to 1");
    }
    if (pool != GDL_CONST_MAPPED_POOL) {
        error("gdl_mem_alloc_nonull: pool must be equal to GDL_CONST_MAPPED_POOL");
    }
    void *mem = malloc(size);
    if (mem == NULL) {
        error("gdl_mem_alloc_nonull: malloc failed");
    }
    return (uintptr_t)mem;
}

gdl_mem_handle_t gdl_mem_alloc_aligned(gdl_context_handle_t ctx_handler,
                                       unsigned long long size,
                                       gdl_mem_pools pool,
                                       gdl_alloc_alignment alignment) {
  return gdl_mem_alloc_nonull(ctx_handler, size, pool);
}

void gdl_mem_free(gdl_mem_handle_t buffer) {
    free((void*)buffer);
}

int gdl_mem_cpy_from_dev(void *dst, gdl_mem_handle_t src, unsigned long long
        size) {
    memcpy(dst, (void*)src, size);
    return 0;
}

int gdl_mem_cpy_to_dev(gdl_mem_handle_t dst, const void *src, unsigned long
        long size) {
    memcpy((void*)dst, src, size);
    return 0;
}

void *gdl_mem_handle_to_host_ptr(gdl_mem_handle_t handle) {
    return (void*)handle;
}

// GDL Task

// Creates a 32bit offset from `memory_start`;
int memory_start;
uint32_t ptr_to_u32(void *p) {
    uint64_t p64 = (uint64_t)p;
    //printf("PPP1: %llu\n", p64);
    uint64_t q64 = (uint64_t)(&memory_start);
    uint64_t d64, d32;
    if (p64 > q64) {
        d64 = p64 - q64;
        d32 = (uint32_t)d64;
        if (d32 != d64) {
            error("The pointer offset does not fit into 32bits");
        }
    } else {
        d64 = q64 - p64;
        d32 = (uint32_t)d64;
        if (d32 != d64) {
            error("The pointer offset does not fit into 32bits");
        }
        d32 = -d32;
    }
    /*
    printf("%llu\n", q64);
    printf("%llu\n", p64);
    printf("%u\n", p32);
    */
    return d32;
}

void* u32_to_ptr(uint32_t p) {
    int32_t d32 = (int32_t)p;
    uint64_t q64 = (uint64_t)(&memory_start);
    uint64_t p64 = (int64_t)q64+(int64_t)d32;
    /*
    printf("PPPAB: %llu %d\n", q64, d32);
    printf("PPP2: %llu\n", p64);
    */
    return (void*)p64;
}

int gdl_run_task_timeout(gdl_context_handle_t ctx_handler,
                        unsigned int code_offset,
                        gdl_mem_handle_t inp,
                        gdl_mem_handle_t outp,
                        struct gdl_mem_buffer *mem_buf,
                        unsigned int buf_size,
                        unsigned int apuc_idx,
                        gdl_task_comp_status *comp,
                        unsigned int ms_timeout,
                        gdl_mapping_type map_type) {
    if (ctx_handler != 1) {
        error("gdl_run_task_timeout: The ctx_handler must be equal to 1");
    }
    void *ptr = u32_to_ptr(code_offset);
    /*
    printf("XXXXXXXX: %u\n", code_offset);
    printf("XXXXXXXX: %llu\n", (uint64_t)ptr);
    */
    if (ptr == NULL) {
        error("gdl_run_task_timeout: code_offset resolved into a NULL");
    }
    gsi_prod_status_t (*task)(void*, void*) = ptr;
    printf("Starting task:\n");
    gsi_prod_status_t r = task((void*)inp, (void*)outp);
    printf("Done task.\n");
    return r;
}

int gdl_mem_handle_is_null(gdl_mem_handle_t handle)
{
  return (void *) handle == NULL;
}
