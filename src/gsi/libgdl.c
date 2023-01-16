#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libgdl.h"

// Ours

void error(char *msg) {
    printf("Error: %s\n", msg);
    printf("Aborting.\n");
    exit(1);
}

// Init/Exit

int gdl_init(void) {
    printf("gdl_init()\n");
    return 0;
}

int gdl_exit(void) {
    printf("gdl_exit()\n");
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
    strcpy(ctx_desc->parent_device_name, "Lepton emulator");
    ctx_desc->ctx_id = 1;
    ctx_desc->num_apucs = 4;
    ctx_desc->num_apus = 1;
    ctx_desc->status = 0;
    ctx_desc->mem_size = 1073741824;
    ctx_desc->hw_general_info = 0;
    return 0;
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

