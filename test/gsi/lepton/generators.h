#ifndef __GSI__LEPTON__TEST__GENERATORS_H__
#define __GSI__LEPTON__TEST__GENERATORS_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <vector>

#include <gsi/lepton/apuc.h>

bool lepton_gen_weighted_bool(uint32_t prob_true);

bool lepton_gen_bool();

uint32_t lepton_gen_seed();

lepton_sm_t lepton_gen_mask();

size_t lepton_gen_l1_addr();

size_t lepton_gen_l2_addr();

lepton_src_t lepton_gen_src_type();

std::vector<size_t> lepton_gen_row_nums();

std::vector<size_t> lepton_gen_writable_row_nums();

void lepton_randomize_apuc(lepton_apuc_t *apuc, uint32_t seed);

void lepton_randomize_wordline(lepton_wordline_t *wordline, uint32_t seed);

void lepton_randomize_vr(lepton_vr_t *vr, uint32_t seed);

#define lepton_randomize_rl lepton_randomize_vr

void lepton_randomize_ggl(lepton_ggl_t *ggl, uint32_t seed);

#define lepton_randomize_l1 lepton_randomize_ggl

void lepton_randomize_gl(lepton_gl_t *gl, uint32_t seed);

void lepton_randomize_lgl(lepton_lgl_t *lgl, uint32_t seed);

#define lepton_randomize_l2 lepton_randomize_lgl

void lepton_randomize_rsp16(lepton_rsp16_t *rsp16, uint32_t seed);

void lepton_randomize_rsp256(lepton_rsp256_t *rsp256, uint32_t seed);

void lepton_randomize_rsp2k(lepton_rsp2k_t *rsp2k, uint32_t seed);

void lepton_randomize_rsp32k(lepton_rsp32k_t *rsp32k, uint32_t seed);

void lepton_randomize_src(lepton_apuc_t *apuc, lepton_src_t src_type, uint32_t seed);

#endif // __GSI__LEPTON__TEST__GENERATORS_H__
