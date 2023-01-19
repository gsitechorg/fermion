#include "libapl.h"
#include "lepton/apuc.h"
#include "lepton/seu_layer.h"

extern lepton_apuc_t apuc;
extern lepton_seu_layer_t seu_layer;

void apl_set_sm_reg(uint32_t sm_reg, uint32_t val) {
  lepton_set_sm_reg(&seu_layer, sm_reg, val);
}

void apl_set_rn_reg(uint32_t rn_reg, uint32_t val) {
  lepton_set_rn_reg(&seu_layer, rn_reg, val);
}

void apl_set_re_reg(uint32_t re_reg, uint32_t val) {
  lepton_set_re_reg(&seu_layer, re_reg, val);
}

void apl_set_ewe_reg(uint32_t ewe_reg, uint32_t val) {
  lepton_set_ewe_reg(&seu_layer, ewe_reg, val);
}

void apl_set_l1_reg(uint32_t l1_reg, uint32_t val) {
  lepton_set_l1_reg(&seu_layer, l1_reg, val);
}

void apl_set_l1_reg_ext(uint32_t reg_idx, uint32_t bank_id, uint32_t grp_id,
                        uint32_t grp_row) {
  lepton_set_l1_reg_ext(&seu_layer, reg_idx, bank_id, grp_id, grp_row);
}

void apl_set_l2_reg(uint32_t l2_reg, uint32_t val) {
  lepton_set_l2_reg(&seu_layer, l2_reg, val);
}
