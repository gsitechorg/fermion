#include "libapl.h"
#include "baryon/fifo.h"
#include "baryon/apuc.h"
#include "baryon/seu_layer.h"

extern baryon_apuc_rsp_fifo_t apuc_rsp_fifo;
extern baryon_apuc_t apuc;
extern baryon_seu_layer_t seu_layer;

void apl_set_sm_reg(uint32_t sm_reg, uint32_t val) {
  baryon_set_sm_reg(&seu_layer, sm_reg, val);
}

void apl_set_rn_reg(uint32_t rn_reg, uint32_t val) {
  baryon_set_rn_reg(&seu_layer, rn_reg, val);
}

void apl_set_re_reg(uint32_t re_reg, uint32_t val) {
  baryon_set_re_reg(&seu_layer, re_reg, val);
}

void apl_set_ewe_reg(uint32_t ewe_reg, uint32_t val) {
  baryon_set_ewe_reg(&seu_layer, ewe_reg, val);
}

void apl_set_l1_reg(uint32_t l1_reg, uint32_t val) {
  baryon_set_l1_reg(&seu_layer, l1_reg, val);
}

void apl_set_l1_reg_ext(uint32_t reg_idx, uint32_t bank_id, uint32_t grp_id,
                        uint32_t grp_row) {
  baryon_set_l1_reg_ext(&seu_layer, reg_idx, bank_id, grp_id, grp_row);
}

void apl_set_l2_reg(uint32_t l2_reg, uint32_t val) {
  baryon_set_l2_reg(&seu_layer, l2_reg, val);
}

void apl_rsp_rd(unsigned int apc_id) {
  baryon_apuc_rsp_rd(&apuc_rsp_fifo, apc_id);
}

unsigned int apl_rd_rsp2k_reg(unsigned int bank_id) {
  return baryon_rd_rsp2k_reg(&apuc_rsp_fifo, bank_id);
}

unsigned char apl_rd_rsp32k_reg() {
  return baryon_rd_rsp32k_reg(&apuc_rsp_fifo);
}
