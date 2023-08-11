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

#include "fixtures.h"

void BaryonAPUCTest::SetUp() {
  apuc_rsp_fifo =
    (baryon_apuc_rsp_fifo_t *)malloc(sizeof(baryon_apuc_rsp_fifo_t));
  baryon_init_apuc_rsp_fifo(apuc_rsp_fifo);

  apuc = (baryon_apuc_t *) malloc(sizeof(baryon_apuc_t));
  baryon_init_apuc(apuc, apuc_rsp_fifo);
}

void BaryonAPUCTest::TearDown() {
  baryon_free_apuc(apuc);
  baryon_free_apuc_rsp_fifo(apuc_rsp_fifo);
}

void BaryonSEULayerTest::SetUp() {
  seu_layer = (baryon_seu_layer_t *)malloc(sizeof(baryon_seu_layer_t));
  baryon_init_seu_layer(seu_layer);
}

void BaryonSEULayerTest::TearDown() {
  baryon_free_seu_layer(seu_layer);
}
