#include <gsi/libgvml.h>

#include "test_libgvml.h"

void LeptonGVMLTest::SetUp() {
  gvml_init();
}

void LeptonGVMLTest::TearDown() {
  gvml_exit();
}
