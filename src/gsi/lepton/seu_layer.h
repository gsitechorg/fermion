#ifndef __GSI__LEPTON__SEU_LAYER_H__
#define __GSI__LEPTON__SEU_LAYER_H__

#include <stdint.h>

#include "apuc.h"
#include "constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#define lepton_foreach_rn_reg(rn_reg, block)                                   \
  lepton_foreach_range(rn_reg, LEPTON_NUM_RN_REGS, block)

#define lepton_foreach_sm_reg(sm_reg, block) \
  lepton_foreach_range(sm_reg, LEPTON_NUM_SM_REGS, block)

#define lepton_foreach_re_reg(re_reg, block) \
  lepton_foreach_range(re_reg, LEPTON_NUM_RE_REGS, block)

#define lepton_foreach_ewe_reg(ewe_reg, block) \
  lepton_foreach_range(ewe_reg, LEPTON_NUM_EWE_REGS, block)

#define lepton_foreach_l1_reg(l1_reg, block) \
  lepton_foreach_range(l1_reg, LEPTON_NUM_L1_REGS, block)

#define lepton_foreach_l2_reg(l2_reg, block) \
  lepton_foreach_range(l2_reg, LEPTON_NUM_L2_REGS, block)

#define lepton_foreach_re_row(re_val, row_number, block) \
  lepton_foreach_range(row_number, LEPTON_NUM_SBS, {     \
    if ((1 << row_number) & (re_val)) {                  \
      block;                                             \
    }                                                    \
  })

#define lepton_foreach_ewe_row(ewe_val, row_number, block)             \
  {                                                                    \
    size_t group = (ewe_val >> 8);                                     \
    size_t offset = LEPTON_NUM_EWE_GROUPS * group;                     \
    size_t mask = (ewe_val & 0xFF);                                    \
    lepton_foreach_range(group_number, LEPTON_NUM_VRS_PER_EWE_GROUP, { \
      if ((1 << group_number) & (mask)) {                              \
        size_t row_number = offset + group_number;                     \
        block;                                                         \
      }                                                                \
    });                                                                \
  }

typedef struct lepton_seu_layer_t {
  size_t rn_regs[LEPTON_NUM_RN_REGS];
  uint16_t sm_regs[LEPTON_NUM_SM_REGS];
  uint32_t re_regs[LEPTON_NUM_RE_REGS];
  uint16_t ewe_regs[LEPTON_NUM_EWE_REGS];
  size_t l1_regs[LEPTON_NUM_L1_REGS];
  size_t l2_regs[LEPTON_NUM_L2_REGS];
} lepton_seu_layer_t;

void lepton_init_seu_layer(lepton_seu_layer_t *seu_layer);

size_t lepton_count_re_rows(lepton_re_t re_val);

size_t lepton_count_ewe_rows(lepton_re_t ewe_val);

void lepton_free_seu_layer(lepton_seu_layer_t *seu_layer);

void lepton_set_rn_reg(lepton_seu_layer_t *seu_layer,
                       size_t rn_reg, size_t val);

void lepton_set_sm_reg(lepton_seu_layer_t *seu_layer,
                       size_t sm_reg, lepton_sm_t sm_val);

void lepton_set_re_reg(lepton_seu_layer_t *seu_layer,
                       size_t re_reg, lepton_re_t re_val);

void lepton_set_ewe_reg(lepton_seu_layer_t *seu_layer,
                        size_t ewe_reg, lepton_ewe_t ewe_val);

void lepton_set_l1_reg(lepton_seu_layer_t *seu_layer,
                       size_t l1_reg, size_t l1_addr);

void lepton_set_l1_reg_ext(lepton_seu_layer_t *seu_layer,
                           size_t l1_reg, size_t bank, size_t group, size_t row);

void lepton_set_l2_reg(lepton_seu_layer_t *seu_layer,
                       size_t l2_reg, size_t l2_addr);

#ifdef __cplusplus
}
#endif

#endif // __GSI__LEPTON__SEU_LAYER_H__
