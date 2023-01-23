#include <gsi/libgvml.h>

#include "fixtures.h"

void BaryonGVMLTest::SetUp() {
  gvml_init();
}

void BaryonGVMLTest::TearDown() {
  gvml_exit();
}
