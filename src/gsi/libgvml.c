#include <stdio.h>

#include <gsi/libgvml_element_wise.h>
#include <gsi/libgvml_memory.h>

/*
# MMB registers
vr_registers[r][i]:
r ... register index 0..23 (gvml_vr16)
i ... column in a register 0..32K-1
Each column (16-bit) is represented as uint16_t
The 32K size is 2048 (per half-bank) x 16 (half-banks)
*/
#define REGS 24
#define COLUMNS 32768
uint16_t vr_registers[REGS][COLUMNS];

/*
# L1 memory
l1_vmr_registers[r][i]:
r ... register index 0..47 (gvml_vm_reg)
i ... column in a register 0..32K-1
Each column (16-bit) is represented as uint16_t
*/
uint16_t l1_vmr_registers[2*REGS][COLUMNS];

/*
# L2 memory length 32K, lives on MMB
Each column (16-bit) is represented as uint16_t
*/
uint16_t l2_memory[COLUMNS];

void gvml_add_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1, enum gvml_vr16 vsrc2) {
    for (uint32_t i=0; i < COLUMNS; i++) {
        vr_registers[vdst][i] = vr_registers[vsrc1][i]+vr_registers[vsrc2][i];
    }
}

void gvml_cpy_imm_16(enum gvml_vr16 vdst, uint16_t val) {
    for (uint32_t i=0; i < COLUMNS; i++) {
        vr_registers[vdst][i] = val;
    }
}

void gvml_mul_u16(enum gvml_vr16 vdst, enum gvml_vr16 vsrc1, enum gvml_vr16 vsrc2) {
    for (uint32_t i=0; i < COLUMNS; i++) {
        vr_registers[vdst][i] = vr_registers[vsrc1][i]*vr_registers[vsrc2][i];
    }
}

void gvml_load_16(enum gvml_vr16 dst, enum gvml_vm_reg vm_reg) {
    for (uint32_t i=0; i < COLUMNS; i++) {
        vr_registers[dst][i] = l1_vmr_registers[vm_reg][i];
    }
}

void gvml_store_16(enum gvml_vm_reg vmdst, enum gvml_vr16 vsrc) {
    for (uint32_t i=0; i < COLUMNS; i++) {
        l1_vmr_registers[vmdst][i] = vr_registers[vsrc][i];
    }
}

void gvml_load_vmr_16(enum gvml_vm_reg vmdst, unsigned int bank, bool l2_ready_set, unsigned int l2_start_byte) {
    // TODO: for now we copy everything for bank=0, and ignore the rest,
    // which works, but we should do exactly what the APU does here
    if (bank == 0) {
        for (uint32_t i=0; i < COLUMNS; i++) {
            l1_vmr_registers[vmdst][i] = l2_memory[i];
        }
    }
}


void gvml_store_vmr_16(enum gvml_vm_reg vmsrc, unsigned int bank, bool l2_ready_set, unsigned int l2_start_byte) {
    // TODO: for now we copy everything for bank=0, and ignore the rest,
    // which works, but we should do exactly what the APU does here
    if (bank == 0) {
        for (uint32_t i=0; i < COLUMNS; i++) {
            l2_memory[i] = l1_vmr_registers[vmsrc][i];
        }
    }
}
