#ifndef __GSI__LEPTON__FIXTURES_H__
#define __GSI__LEPTON__FIXTURES_H__

#include <gsi/lepton/apuc.h>
#include <gsi/lepton/seu_layer.h>

#include <gtest/gtest.h>

class LeptonAPUCTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  lepton_apuc_t *apuc;
};

class LeptonSEULayerTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  lepton_seu_layer_t *seu_layer;
};

#endif // __GSI__LEPTON__FIXTURES_H__
