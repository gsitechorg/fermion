/* By Dylon Edwards
 *
 * Copyright 2019 - 2023 GSI Technology, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdlib.h>
#include <string.h>

#include "seu_layer.h"

void baryon_init_seu_layer(baryon_seu_layer_t *seu_layer) {
  // nothing to do
}

void baryon_free_seu_layer(baryon_seu_layer_t *seu_layer) {
  if (seu_layer != NULL) {
    free(seu_layer);
  }
}

size_t baryon_count_re_rows(baryon_re_t re_val) {
  size_t num_rows = 0;
  baryon_foreach_re_row(re_val, row, num_rows += 1);
  return num_rows;
}

size_t baryon_count_ewe_rows(baryon_re_t ewe_val) {
  size_t num_rows = 0;
  baryon_foreach_ewe_row(ewe_val, row, num_rows += 1);
  return num_rows;
}

void baryon_set_rn_reg(baryon_seu_layer_t *seu_layer, size_t rn_reg,
                       size_t val) {
  seu_layer->rn_regs[rn_reg] = val;
}

void baryon_set_sm_reg(baryon_seu_layer_t *seu_layer, size_t sm_reg,
                       baryon_sm_t sm_val) {
  seu_layer->sm_regs[sm_reg] = sm_val;
}

void baryon_set_re_reg(baryon_seu_layer_t *seu_layer, size_t re_reg,
                       baryon_re_t re_val) {
  seu_layer->re_regs[re_reg] = re_val;
}

void baryon_set_ewe_reg(baryon_seu_layer_t *seu_layer, size_t ewe_reg,
                        baryon_ewe_t ewe_val) {
  seu_layer->ewe_regs[ewe_reg] = ewe_val;
}

void baryon_set_l1_reg(baryon_seu_layer_t *seu_layer, size_t l1_reg,
                       size_t l1_addr) {
  seu_layer->l1_regs[l1_reg] = l1_addr;
}

void baryon_set_l1_reg_ext(baryon_seu_layer_t *seu_layer, size_t l1_reg,
                           size_t bank, size_t group, size_t row) {
  size_t l1_addr = (bank << 11) | (group << 9) | row;
  baryon_set_l1_reg(seu_layer, l1_reg, l1_addr);
}

void baryon_set_l2_reg(baryon_seu_layer_t *seu_layer, size_t l2_reg,
                       size_t l2_addr) {
  seu_layer->l2_regs[l2_reg] = l2_addr;
}
