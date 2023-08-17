/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__TEST__GENERATORS_H__
#define __GSI__BARYON__TEST__GENERATORS_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <vector>

#include <gsi/baryon/apuc.h>

bool baryon_gen_weighted_bool(uint32_t prob_true);

bool baryon_gen_bool();

uint32_t baryon_gen_seed();

baryon_sm_t baryon_gen_mask();

size_t baryon_gen_l1_addr();

size_t baryon_gen_l2_addr();

baryon_src_t baryon_gen_src_type();

std::vector<size_t> baryon_gen_row_nums();

std::vector<size_t> baryon_gen_writable_row_nums();

void baryon_randomize_apuc(baryon_apuc_t *apuc, uint32_t seed);

void baryon_randomize_wordline(baryon_wordline_t *wordline, uint32_t seed);

void baryon_randomize_vr(baryon_vr_t *vr, uint32_t seed);

#define baryon_randomize_rl baryon_randomize_vr

void baryon_randomize_ggl(baryon_ggl_t *ggl, uint32_t seed);

#define baryon_randomize_l1 baryon_randomize_ggl

void baryon_randomize_gl(baryon_gl_t *gl, uint32_t seed);

void baryon_randomize_lgl(baryon_lgl_t *lgl, uint32_t seed);

#define baryon_randomize_l2 baryon_randomize_lgl

void baryon_randomize_rsp16(baryon_rsp16_t *rsp16, uint32_t seed);

void baryon_randomize_rsp256(baryon_rsp256_t *rsp256, uint32_t seed);

void baryon_randomize_rsp2k(baryon_rsp2k_t *rsp2k, uint32_t seed);

void baryon_randomize_rsp32k(baryon_rsp32k_t *rsp32k, uint32_t seed);

void baryon_randomize_src(baryon_apuc_t *apuc, baryon_src_t src_type, uint32_t seed);

#endif // __GSI__BARYON__TEST__GENERATORS_H__
