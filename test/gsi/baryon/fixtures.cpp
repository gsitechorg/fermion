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
