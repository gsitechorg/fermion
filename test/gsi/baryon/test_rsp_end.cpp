/* By Dylon Edwards
 *
 * Copyright 2019 - 2023 GSI Technology, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp_end, ()) {
  uint32_t rsp16_seed = baryon_gen_seed();
  uint32_t rsp256_seed = baryon_gen_seed();
  uint32_t rsp2k_seed = baryon_gen_seed();
  uint32_t rsp32k_seed = baryon_gen_seed();

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  baryon_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  baryon_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);

  baryon_rsp_end(apuc);

  baryon_foreach_rsp16_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp16[section][plat]);
  });
  baryon_foreach_rsp256_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp256[section][plat]);
  });
  baryon_foreach_rsp2k_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp2k[section][plat]);
  });
  baryon_foreach_rsp32k_section(section, {
    RC_ASSERT(!apuc->rsp32k[section]);
  });

  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  baryon_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  baryon_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);

  apuc->in_place = false;
  baryon_rsp_patches_t *patch = baryon_rsp_end(apuc);
  baryon_patch_rsps(apuc, patch);
  baryon_free_rsp_patches(patch);
  apuc->in_place = true;

  baryon_foreach_rsp16_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp16[section][plat]);
  });
  baryon_foreach_rsp256_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp256[section][plat]);
  });
  baryon_foreach_rsp2k_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp2k[section][plat]);
  });
  baryon_foreach_rsp32k_section(section, {
    RC_ASSERT(!apuc->rsp32k[section]);
  });
}
