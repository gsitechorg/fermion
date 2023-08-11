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
#include <gsi/libgvml.h>
#include <gsi/libgvml_element_wise.h>

#include <gtest/gtest.h>

#include "fixtures.h"

TEST_F(BaryonGVMLTest, gvml_cpy_imm_16) {
  gvml_cpy_imm_16(GVML_VR16_0, 0xBEEF);
  baryon_foreach_vr_plat(plat, {
    uint16_t value = 0x0000;
    baryon_foreach_vr_section(section, {
      value |= (apuc.vrs[GVML_VR16_0][section][plat] << section);
    });
    ASSERT_EQ(value, 0xBEEF) << "Expected apuc.vrs[0][:][" << plat
                             << "] to be 0xBEEF but was " << value;
  });
}
