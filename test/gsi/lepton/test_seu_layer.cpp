#include <stdlib.h>

#include <set>

#include <gsi/lepton/seu_layer.h>

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"
#include "utils.h"

RC_GTEST_FIXTURE_PROP(LeptonSEULayerTest, foreach_re_row, ()) {
  std::vector<size_t> row_nums = lepton_gen_row_nums();
  lepton_re_t re_mask = lepton_collect_re_mask(row_nums);
  RC_ASSERT(lepton_count_re_rows(re_mask) == row_nums.size());

  std::set<size_t> visited;
  lepton_foreach_re_row(re_mask, row_num, {
    RC_ASSERT(visited.find(row_num) == visited.end());
    visited.insert(row_num);
  });

  RC_ASSERT(visited.size() == row_nums.size());

  for (const size_t &row_num : row_nums) {
    visited.erase(row_num);
  }

  RC_ASSERT(visited.empty());
}

RC_GTEST_FIXTURE_PROP(LeptonSEULayerTest, foreach_ewe_row, ()) {
  std::vector<size_t> row_nums = lepton_gen_writable_row_nums();
  lepton_ewe_t ewe_mask = lepton_collect_ewe_mask(row_nums);
  RC_ASSERT(lepton_count_ewe_rows(ewe_mask) == row_nums.size());

  std::set<size_t> visited;
  lepton_foreach_ewe_row(ewe_mask, row_num, {
    RC_ASSERT(visited.find(row_num) == visited.end());
    visited.insert(row_num);
  });

  RC_ASSERT(visited.size() == row_nums.size());

  for (const size_t &row_num : row_nums) {
    visited.erase(row_num);
  }

  RC_ASSERT(visited.empty());
}
