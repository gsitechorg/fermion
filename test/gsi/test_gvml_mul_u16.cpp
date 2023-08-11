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
#include <gsi/libgvml_element_wise.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "baryon/generators.h"
#include "fixtures.h"

RC_GTEST_FIXTURE_PROP(BaryonGVMLTest, gvml_mul_u16, ()) {
  srand(baryon_gen_seed());
  baryon_randomize_vr(&apuc.vrs[0], rand());
  baryon_randomize_vr(&apuc.vrs[1], rand());
  baryon_randomize_vr(&apuc.vrs[2], rand());
  gvml_mul_u16(GVML_VR16_0, GVML_VR16_1, GVML_VR16_2);
  baryon_foreach_vr_plat(plat, {
    uint16_t lhs = 0x0000;
    uint16_t rhs = 0x0000;
    uint16_t expected = 0x0000;
    uint16_t actual = 0x0000;
    baryon_foreach_vr_section(section, {
      lhs |= (apuc.vrs[GVML_VR16_1][section][plat] << section);
      rhs |= (apuc.vrs[GVML_VR16_2][section][plat] << section);
      actual |= (apuc.vrs[GVML_VR16_0][section][plat] << section);
    });
    expected = (uint16_t)(((uint32_t)lhs * (uint32_t)rhs) & 0xFFFF);
    RC_ASSERT(actual == expected);
  });
}
