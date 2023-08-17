/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__TEST__UTILS_H__
#define __GSI__BARYON__TEST__UTILS_H__

#include <vector>

#include <gsi/baryon/apuc.h>

baryon_re_t baryon_collect_re_mask(const std::vector<size_t> &row_nums);

baryon_ewe_t baryon_collect_ewe_mask(const std::vector<size_t> &row_nums);

#endif // __GSI__BARYON__TEST__UTILS_H__
