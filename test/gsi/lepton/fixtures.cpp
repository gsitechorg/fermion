#include "fixtures.h"

void LeptonAPUCTest::SetUp() {
  apuc = (lepton_apuc_t *) malloc(sizeof(lepton_apuc_t));
  lepton_init_apuc(apuc);
}

void LeptonAPUCTest::TearDown() {
  lepton_free_apuc(apuc);
}

void LeptonSEULayerTest::SetUp() {
  seu_layer = (lepton_seu_layer_t *)malloc(sizeof(lepton_seu_layer_t));
  lepton_init_seu_layer(seu_layer);
}

void LeptonSEULayerTest::TearDown() {
  lepton_free_seu_layer(seu_layer);
}
