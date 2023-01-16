#include <stdlib.h>
#include <string.h>

#include "seu_layer.h"

void lepton_init_seu_layer(lepton_seu_layer_t *seu_layer) {
  // nothing to do
}

void lepton_free_seu_layer(lepton_seu_layer_t *seu_layer) {
  if (seu_layer != NULL) {
    free(seu_layer);
  }
}

size_t lepton_count_re_rows(lepton_re_t re_val) {
  size_t num_rows = 0;
  lepton_foreach_re_row(re_val, row, num_rows += 1);
  return num_rows;
}

size_t lepton_count_ewe_rows(lepton_re_t ewe_val) {
  size_t num_rows = 0;
  lepton_foreach_ewe_row(ewe_val, row, num_rows += 1);
  return num_rows;
}

void lepton_set_rn_reg(lepton_seu_layer_t *seu_layer, size_t rn_reg,
                       size_t val) {
  seu_layer->rn_regs[rn_reg] = val;
}

void lepton_set_sm_reg(lepton_seu_layer_t *seu_layer, size_t sm_reg,
                       lepton_sm_t sm_val) {
  seu_layer->sm_regs[sm_reg] = sm_val;
}

void lepton_set_re_reg(lepton_seu_layer_t *seu_layer, size_t re_reg,
                       lepton_re_t re_val) {
  seu_layer->re_regs[re_reg] = re_val;
}

void lepton_set_ewe_reg(lepton_seu_layer_t *seu_layer, size_t ewe_reg,
                        lepton_ewe_t ewe_val) {
  seu_layer->ewe_regs[ewe_reg] = ewe_val;
}

void lepton_set_l1_reg(lepton_seu_layer_t *seu_layer, size_t l1_reg,
                       size_t l1_addr) {
  seu_layer->l1_regs[l1_reg] = l1_addr;
}

void lepton_set_l1_reg_ext(lepton_seu_layer_t *seu_layer, size_t l1_reg,
                           size_t bank, size_t group, size_t row) {
  size_t l1_addr = (bank << 11) | (group << 9) | row;
  lepton_set_l1_reg(seu_layer, l1_reg, l1_addr);
}

void lepton_set_l2_reg(lepton_seu_layer_t *seu_layer, size_t l2_reg,
                       size_t l2_addr) {
  seu_layer->l2_regs[l2_reg] = l2_addr;
}
