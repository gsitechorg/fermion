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

#include <gsi/baryon/apuc.h>
#include <gsi/common_api.h>
#include <gsi/libgvml_memory.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "baryon/generators.h"
#include "fixtures.h"

RC_GTEST_FIXTURE_PROP(BaryonGVMLTest, gvml_store_load_16, ()) {
  srand(baryon_gen_seed());
  baryon_randomize_vr(&apuc.vrs[0], rand());
  baryon_randomize_vr(&apuc.vrs[1], rand());
  for (size_t i = 0; i < 9; i += 1) {
    baryon_randomize_l1(&apuc.l1[i], rand());
  }
  gvml_store_16(GVML_VM_0, GVML_VR16_1);
  gvml_load_16(GVML_VR16_0, GVML_VM_0);
  baryon_foreach_vr_section_plat(section, plat, {
    bool actual_value = apuc.vrs[GVML_VR16_0][section][plat];
    bool expected_value = apuc.vrs[GVML_VR16_1][section][plat];
    RC_ASSERT(actual_value == expected_value);
  });
}
