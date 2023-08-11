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

#include "utils.h"

baryon_re_t baryon_collect_re_mask(const std::vector<size_t> &row_nums) {
  baryon_re_t re_mask = 0x000000;
  for (const size_t &row_num : row_nums) {
    re_mask |= (1 << row_num);
  }
  return re_mask;
}

baryon_ewe_t baryon_collect_ewe_mask(const std::vector<size_t> &row_nums) {
  baryon_ewe_t ewe_mask = 0x000;

  if (row_nums.size() == 0) {
    return ewe_mask;
  }

  size_t group = row_nums[0] / 8;
  size_t offset = group * 8;

  ewe_mask |= (group << 8);
  for (const size_t &row_num : row_nums) {
    ewe_mask |= (1 << (row_num - offset));
  }

  return ewe_mask;
}
