#ifndef __GSI__LEPTON__FIXTURES_H__
#define __GSI__LEPTON__FIXTURES_H__

#include <gsi/lepton/apuc.h>

#include <gtest/gtest.h>

class LeptonAPUCTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  lepton_apuc_t *apuc;
};

#endif // __GSI__LEPTON__FIXTURES_H__
