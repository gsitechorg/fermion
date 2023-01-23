#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, brsp16, ()) {
  uint32_t rsp16_seed = baryon_gen_seed();
  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_brsp16_t *brsp16 = baryon_brsp16(&apuc->rsp16);
  baryon_foreach_rsp16_section_plat(section, step, {
    size_t lower = step * 16;
    size_t upper = lower + 16;
    baryon_foreach_range(plat, lower, upper, {
      RC_ASSERT((*brsp16)[section][plat] == apuc->rsp16[section][step]);
    });
  });
}
