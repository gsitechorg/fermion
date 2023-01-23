#include "utils.h"

lepton_re_t lepton_collect_re_mask(const std::vector<size_t> &row_nums) {
  lepton_re_t re_mask = 0x000000;
  for (const size_t &row_num : row_nums) {
    re_mask |= (1 << row_num);
  }
  return re_mask;
}

lepton_ewe_t lepton_collect_ewe_mask(const std::vector<size_t> &row_nums) {
  lepton_ewe_t ewe_mask = 0x000;

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
