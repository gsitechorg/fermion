#include <gsi/libgvml.h>

#include "fixtures.h"

void LeptonGVMLTest::SetUp() {
  gvml_init();
}

void LeptonGVMLTest::TearDown() {
  gvml_exit();
}
