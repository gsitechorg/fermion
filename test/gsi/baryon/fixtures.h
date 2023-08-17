/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__FIXTURES_H__
#define __GSI__BARYON__FIXTURES_H__

#include <gsi/baryon/fifo.h>
#include <gsi/baryon/apuc.h>
#include <gsi/baryon/seu_layer.h>

#include <gtest/gtest.h>

class BaryonAPUCTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  baryon_apuc_rsp_fifo_t *apuc_rsp_fifo;
  baryon_apuc_t *apuc;
};

class BaryonSEULayerTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  baryon_seu_layer_t *seu_layer;
};

#endif // __GSI__BARYON__FIXTURES_H__
