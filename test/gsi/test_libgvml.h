#ifndef __LEPTON_TEST_LIBGVML_H__
#define __LEPTON_TEST_LIBGVML_H__

#include <gtest/gtest.h>

class LeptonGVMLTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
};

#endif // __LEPTON_TEST_LIBGVML_H__
