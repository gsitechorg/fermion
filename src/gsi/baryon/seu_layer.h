#ifndef __GSI__BARYON__SEU_LAYER_H__
#define __GSI__BARYON__SEU_LAYER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "apuc.h"
#include "constants.h"

#define baryon_foreach_rn_reg(rn_reg, block)                                   \
  baryon_foreach_range(rn_reg, BARYON_NUM_RN_REGS, block)

#define baryon_foreach_sm_reg(sm_reg, block) \
  baryon_foreach_range(sm_reg, BARYON_NUM_SM_REGS, block)

#define baryon_foreach_re_reg(re_reg, block) \
  baryon_foreach_range(re_reg, BARYON_NUM_RE_REGS, block)

#define baryon_foreach_ewe_reg(ewe_reg, block) \
  baryon_foreach_range(ewe_reg, BARYON_NUM_EWE_REGS, block)

#define baryon_foreach_l1_reg(l1_reg, block) \
  baryon_foreach_range(l1_reg, BARYON_NUM_L1_REGS, block)

#define baryon_foreach_l2_reg(l2_reg, block) \
  baryon_foreach_range(l2_reg, BARYON_NUM_L2_REGS, block)

#define baryon_foreach_re_row(re_val, row_number, block)                       \
  baryon_foreach_range(row_number, BARYON_NUM_SBS, {                           \
    if ((1 << row_number) & (re_val)) {                                        \
      block;                                                                   \
    }                                                                          \
  })

#define baryon_foreach_ewe_row(ewe_val, row_number, block)                     \
  {                                                                            \
    size_t group = (ewe_val) >> 8;                                             \
    size_t offset = group * 8;                                                 \
    size_t mask = (ewe_val) & 0xFF;                                            \
    baryon_foreach_range(group_number, BARYON_NUM_VRS_PER_EWE_GROUP, {         \
      if ((1 << group_number) & (mask)) {                                      \
        size_t row_number = offset + group_number;                             \
        block;                                                                 \
      }                                                                        \
    });                                                                        \
  }

typedef struct baryon_seu_layer_t {
  size_t rn_regs[BARYON_NUM_RN_REGS];
  uint16_t sm_regs[BARYON_NUM_SM_REGS];
  uint32_t re_regs[BARYON_NUM_RE_REGS];
  uint16_t ewe_regs[BARYON_NUM_EWE_REGS];
  size_t l1_regs[BARYON_NUM_L1_REGS];
  size_t l2_regs[BARYON_NUM_L2_REGS];
} baryon_seu_layer_t;

void baryon_init_seu_layer(baryon_seu_layer_t *seu_layer);

size_t baryon_count_re_rows(baryon_re_t re_val);

size_t baryon_count_ewe_rows(baryon_re_t ewe_val);

void baryon_free_seu_layer(baryon_seu_layer_t *seu_layer);

void baryon_set_rn_reg(baryon_seu_layer_t *seu_layer,
                       size_t rn_reg, size_t val);

void baryon_set_sm_reg(baryon_seu_layer_t *seu_layer,
                       size_t sm_reg, baryon_sm_t sm_val);

void baryon_set_re_reg(baryon_seu_layer_t *seu_layer,
                       size_t re_reg, baryon_re_t re_val);

void baryon_set_ewe_reg(baryon_seu_layer_t *seu_layer,
                        size_t ewe_reg, baryon_ewe_t ewe_val);

void baryon_set_l1_reg(baryon_seu_layer_t *seu_layer,
                       size_t l1_reg, size_t l1_addr);

void baryon_set_l1_reg_ext(baryon_seu_layer_t *seu_layer,
                           size_t l1_reg, size_t bank, size_t group, size_t row);

void baryon_set_l2_reg(baryon_seu_layer_t *seu_layer,
                       size_t l2_reg, size_t l2_addr);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__SEU_LAYER_H__
