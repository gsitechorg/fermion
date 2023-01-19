#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "gsi/lepton/lepton_test_apuc.h"
#include "gsi/lepton_test_libgvml.h"
#include "gsi/lepton_test_libgal.h"
#include "lepton_test_matvec.h"
#include "lepton_test.h"

size_t LEPTON_NUM_TESTS = 0;
size_t LEPTON_NUM_FAILED_TESTS = 0;
bool LEPTON_TEST_PASSED = true;

int main(int argc, char *argv[]) {
  lepton_test_apuc();
  lepton_test_libgvml();
  lepton_test_libgal();
  LEPTON_RUN_TEST(lepton_test_matvec);

  if (LEPTON_NUM_FAILED_TESTS > 0) {
    printf("%zu out of %zu test(s) failed.\n",
           LEPTON_NUM_FAILED_TESTS, LEPTON_NUM_TESTS);
    return 1;
  }
  else {
    printf("%zu test(s) passed!\n", LEPTON_NUM_TESTS);
    return 0;
  }
}
