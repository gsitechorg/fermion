/* By Dylon Edwards
 */

#ifndef __GSI__GVML__FIXTURES_H__
#define __GSI__GVML__FIXTURES_H__

#include <gtest/gtest.h>

class BaryonGVMLTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
};

#endif // __GSI__GVML__FIXTURES_H__
