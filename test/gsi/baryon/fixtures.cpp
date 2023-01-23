#include "fixtures.h"

void BaryonAPUCTest::SetUp() {
  apuc = (baryon_apuc_t *) malloc(sizeof(baryon_apuc_t));
  baryon_init_apuc(apuc);
}

void BaryonAPUCTest::TearDown() {
  baryon_free_apuc(apuc);
}

void BaryonSEULayerTest::SetUp() {
  seu_layer = (baryon_seu_layer_t *)malloc(sizeof(baryon_seu_layer_t));
  baryon_init_seu_layer(seu_layer);
}

void BaryonSEULayerTest::TearDown() {
  baryon_free_seu_layer(seu_layer);
}
