#include "fixtures.h"

void LeptonAPUCTest::SetUp() {
  apuc = (lepton_apuc_t *) malloc(sizeof(lepton_apuc_t));
  lepton_init_apuc(apuc);
}

void LeptonAPUCTest::TearDown() {
  lepton_free_apuc(apuc);
}
