#ifndef __LEPTON_TEST_LIBGVML_H__
#define __LEPTON_TEST_LIBGVML_H__

#include <stdio.h>

#include <gsi/libgvml.h>

#include "../lepton_test.h"
#include "lepton/lepton_test_apuc.h"

#define LEPTON_RUN_GVML_TEST(test_fn)                                          \
  {                                                                            \
    LEPTON_TEST_PASSED = true;                                                 \
    LEPTON_NUM_TESTS += 1;                                                     \
    gvml_init();                                                               \
    test_fn();                                                                 \
    if (LEPTON_TEST_PASSED) {                                                  \
      printf("[SUCCESS] " #test_fn "\n");                                      \
    } else {                                                                   \
      printf("[FAILURE] " #test_fn "\n");                                      \
      LEPTON_NUM_FAILED_TESTS += 1;                                            \
    }                                                                          \
    gvml_exit();                                                               \
  }

void lepton_test_libgvml(void);

#endif // __LEPTON_TEST_LIBGVML_H__
