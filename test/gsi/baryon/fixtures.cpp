#include "fixtures.h"

void BaryonAPUCTest::SetUp() {
  rsp32k_fifo = (baryon_rsp32k_fifo_t *) malloc(sizeof(baryon_rsp32k_fifo_t));
  baryon_init_rsp32k_fifo(rsp32k_fifo);

  rsp2k_fifo = (baryon_rsp2k_fifo_t *)malloc(sizeof(baryon_rsp2k_fifo_t));
  baryon_init_rsp2k_fifo(rsp2k_fifo);

  apuc = (baryon_apuc_t *) malloc(sizeof(baryon_apuc_t));
  baryon_init_apuc(apuc, rsp32k_fifo, rsp2k_fifo);
}

void BaryonAPUCTest::TearDown() {
  baryon_free_apuc(apuc);
  baryon_free_rsp32k_fifo(rsp32k_fifo);
  baryon_free_rsp2k_fifo(rsp2k_fifo);
}

void BaryonSEULayerTest::SetUp() {
  seu_layer = (baryon_seu_layer_t *)malloc(sizeof(baryon_seu_layer_t));
  baryon_init_seu_layer(seu_layer);
}

void BaryonSEULayerTest::TearDown() {
  baryon_free_seu_layer(seu_layer);
}
