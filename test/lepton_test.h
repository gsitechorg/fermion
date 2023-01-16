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

#endif // __TEST_LEPTON_H__
