#include <gtest/gtest.h>

#include "rapidcheck_parser.h"

int main(int argc, char *argv[]) {
  ::baryon::init_rapidcheck(argv[0]);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
