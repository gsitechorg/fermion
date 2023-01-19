#ifndef __TEST_LEPTON_H__
#define __TEST_LEPTON_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

extern size_t LEPTON_NUM_TESTS;
extern size_t LEPTON_NUM_FAILED_TESTS;
extern bool LEPTON_TEST_PASSED;

#define LEPTON_FAIL_TEST(message, ...)                                         \
  {                                                                            \
    printf("%s:%d: " message, __FILE__, __LINE__, __VA_ARGS__);                \
    LEPTON_TEST_PASSED = false;                                                \
  }

#define LEPTON_RUN_TEST(test_fn)                                               \
  {                                                                            \
    LEPTON_NUM_TESTS += 1;                                                     \
    LEPTON_TEST_PASSED = true;                                                 \
    test_fn();                                                                 \
    if (LEPTON_TEST_PASSED) {                                                  \
      printf("[SUCCESS] " #test_fn "\n");                                      \
    } else {                                                                   \
      LEPTON_NUM_FAILED_TESTS += 1;                                            \
      printf("[FAILURE] " #test_fn "\n");                                      \
    }                                                                          \
  }

#endif // __TEST_LEPTON_H__
