#ifndef __GSI__LEPTON__TEST__UTILS_H__
#define __GSI__LEPTON__TEST__UTILS_H__

#include <vector>

#include <gsi/lepton/apuc.h>

lepton_re_t lepton_collect_re_mask(const std::vector<size_t> &row_nums);

lepton_ewe_t lepton_collect_ewe_mask(const std::vector<size_t> &row_nums);

#endif // __GSI__LEPTON__TEST__UTILS_H__
