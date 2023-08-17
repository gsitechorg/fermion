/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <gsi/baryon/apuc.h>
#include <gsi/common_api.h>
#include <gsi/libgvml.h>

TEST(gvml_init, test_is_gvml_init) {
  EXPECT_FALSE(is_gvml_init());
  gvml_init_once();
  EXPECT_TRUE(is_gvml_init());
  gvml_exit();
  EXPECT_FALSE(is_gvml_init());
}
