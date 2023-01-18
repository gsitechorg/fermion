#ifndef __GSI__LEPTON__APUC_H__
#define __GSI__LEPTON__APUC_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "constants.h"

/* #ifdef __cplusplus */
/* extern "C" { */
/* #endif */

#define LEPTON_FOREACH_RANGE_3(var, lower, upper, step_size, block) \
  for (size_t var = lower; var < upper; var += step_size) {         \
    block;                                                          \
  }

#define LEPTON_FOREACH_RANGE_2(var, lower, upper, block) \
  LEPTON_FOREACH_RANGE_3(var, lower, upper, 1, block)

#define LEPTON_FOREACH_RANGE_1(var, upper, block) \
  LEPTON_FOREACH_RANGE_3(var, 0, upper, 1, block)

#define LEPTON_EXPAND_FOREACH_RANGE(_1, _2, _3, _4, _5, NAME, ...) \
  NAME

#define lepton_foreach_range(...)                     \
  LEPTON_EXPAND_FOREACH_RANGE(__VA_ARGS__,            \
                              LEPTON_FOREACH_RANGE_3, \
                              LEPTON_FOREACH_RANGE_2, \
                              LEPTON_FOREACH_RANGE_1)(__VA_ARGS__)

#define lepton_foreach_masked_section(mask, section, block) \
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS, {      \
    if ((1 << section) & (mask)) {                          \
      block;                                                \
    }                                                       \
  })

#define lepton_foreach_vr_row(row, block) \
  lepton_foreach_range(row, LEPTON_NUM_SBS, block)

#define lepton_foreach_vr_section(section, block) \
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS, block)

#define lepton_foreach_vr_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_PLATS_PER_APUC, block)

#define lepton_foreach_vr_section_plat(section, plat, block) \
  lepton_foreach_vr_section(section, {                       \
    lepton_foreach_vr_plat(plat, block);                     \
  })

#define lepton_foreach_vr_row_section_plat(row, section, plat, block) \
  lepton_foreach_vr_row(row, {                                        \
    lepton_foreach_vr_section(section, {                              \
      lepton_foreach_vr_plat(plat, block);                            \
    });                                                               \
  })

#define lepton_foreach_rl_section lepton_foreach_vr_section
#define lepton_foreach_rl_plat lepton_foreach_vr_plat
#define lepton_foreach_rl_section_plat lepton_foreach_vr_section_plat

#define lepton_foreach_gl_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_PLATS_PER_APUC, block)

#define lepton_foreach_ggl_group(group, block) \
  lepton_foreach_range(group, LEPTON_NUM_GROUPS, block)

#define lepton_foreach_ggl_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_PLATS_PER_APUC, block)

#define lepton_foreach_ggl_group_plat(group, plat, block) \
  lepton_foreach_ggl_group(group, {                       \
    lepton_foreach_ggl_plat(plat, block);                 \
  })

#define lepton_foreach_l1_group_plat lepton_foreach_ggl_group_plat

#define lepton_foreach_lgl_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_LGL_PLATS, block)

#define lepton_foreach_l1_row(row, block) \
  lepton_foreach_range(row, LEPTON_NUM_L1_ROWS, block)

#define lepton_foreach_l1_group(group, block) \
  lepton_foreach_range(group, LEPTON_NUM_GROUPS, block)

#define lepton_foreach_l1_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_PLATS_PER_APUC, block)

#define lepton_foreach_l1_row_group_plat(row, group, plat, block) \
  lepton_foreach_l1_row(row, {                                    \
    lepton_foreach_l1_group(group, {                              \
      lepton_foreach_l1_plat(plat, block);                        \
    })                                                            \
  })

#define lepton_foreach_l2_row(row, block) \
  lepton_foreach_range(row, LEPTON_NUM_L2_ROWS, block)

#define lepton_foreach_l2_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_L2_PLATS, block)

#define lepton_foreach_l2_row_plat(row, plat, block) \
  lepton_foreach_l2_row(row, {                       \
    lepton_foreach_l2_plat(plat, block);             \
  })

#define lepton_foreach_rsp16_section(section, block) \
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS, block)

#define lepton_foreach_rsp16_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_RSP16_PLATS, block)

#define lepton_foreach_rsp16_section_plat(section, plat, block) \
  lepton_foreach_rsp16_section(section, {                       \
    lepton_foreach_rsp16_plat(plat, block);                     \
  })

#define lepton_foreach_rsp256_section(section, block) \
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS, block)

#define lepton_foreach_rsp256_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_RSP256_PLATS, block)

#define lepton_foreach_rsp256_section_plat(section, plat, block) \
  lepton_foreach_rsp256_section(section, {                       \
    lepton_foreach_rsp256_plat(plat, block);                     \
  })

#define lepton_foreach_rsp2k_section(section, block) \
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS, block)

#define lepton_foreach_rsp2k_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_RSP2K_PLATS, block)

#define lepton_foreach_rsp2k_section_plat(section, plat, block) \
  lepton_foreach_rsp2k_section(section, {                       \
    lepton_foreach_rsp2k_plat(plat, block);                     \
  })

#define lepton_foreach_rsp32k_section(section, block) \
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS, block)

#define lepton_foreach_rsp32k_plat(plat, block) \
  lepton_foreach_range(plat, LEPTON_NUM_RSP32K_PLATS, block)

#define lepton_foreach_rsp32k_section_plat(section, plat, block) \
  lepton_foreach_rsp32k_section(section, {                       \
    lepton_foreach_rsp32k_plat(plat, block);                     \
  })

#define lepton_foreach_half_bank(half_bank, block) \
  lepton_foreach_range(half_bank, LEPTON_NUM_HALF_BANKS_PER_APUC, block)

void lepton_bank_group_row(size_t l1_addr, size_t *bank, size_t *group,
                           size_t *row);

#define lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, block)            \
  {                                                                         \
    size_t lower_plat_apc_0;                                                \
    size_t upper_plat_apc_0;                                                \
    size_t lower_plat_apc_1;                                                \
    size_t upper_plat_apc_1;                                                \
    lepton_plats_for_bank(bank, &lower_plat_apc_0, &upper_plat_apc_0,       \
                          &lower_plat_apc_1, &upper_plat_apc_1);            \
    size_t lgl_plat;                                                        \
    lepton_foreach_range(l1_plat, lower_plat_apc_0, upper_plat_apc_0, {     \
      lgl_plat = l1_plat - lower_plat_apc_0;                                \
      block;                                                                \
    });                                                                     \
    lepton_foreach_range(l1_plat, lower_plat_apc_1, upper_plat_apc_1, {     \
      lgl_plat =                                                            \
          l1_plat - lower_plat_apc_1 + LEPTON_NUM_PLATS_PER_HALF_BANK * 2;  \
      block;                                                                \
    });                                                                     \
  }

typedef bool lepton_vr_t[LEPTON_NUM_SECTIONS][LEPTON_NUM_PLATS_PER_APUC];
typedef lepton_vr_t lepton_rl_t;
typedef uint16_t lepton_sm_t;
typedef uint32_t lepton_re_t;
typedef uint16_t lepton_ewe_t;
typedef bool lepton_gl_t[LEPTON_NUM_PLATS_PER_APUC];
typedef bool lepton_ggl_t[LEPTON_NUM_GROUPS][LEPTON_NUM_PLATS_PER_APUC];
typedef bool lepton_rsp16_t[LEPTON_NUM_SECTIONS][LEPTON_NUM_RSP16_PLATS];
typedef bool lepton_rsp256_t[LEPTON_NUM_SECTIONS][LEPTON_NUM_RSP256_PLATS];
typedef bool lepton_rsp2k_t[LEPTON_NUM_SECTIONS][LEPTON_NUM_RSP2K_PLATS];
typedef bool lepton_rsp32k_t[LEPTON_NUM_SECTIONS][LEPTON_NUM_RSP32K_PLATS];
typedef bool lepton_l1_t[LEPTON_NUM_GROUPS][LEPTON_NUM_PLATS_PER_APUC];
typedef bool lepton_l2_t[LEPTON_NUM_L2_PLATS];
typedef bool lepton_lgl_t[LEPTON_NUM_LGL_PLATS];

typedef bool lepton_wordline_t[LEPTON_NUM_PLATS_PER_APUC];
typedef bool lepton_rsp16_section_t[LEPTON_NUM_RSP16_PLATS];

#define LEPTON_VR_SIZE \
  (LEPTON_NUM_SECTIONS * LEPTON_NUM_PLATS_PER_APUC * sizeof(bool))
#define LEPTON_RL_SIZE LEPTON_VR_SIZE
#define LEPTON_GL_SIZE \
  (LEPTON_NUM_PLATS_PER_APUC * sizeof(bool))
#define LEPTON_WORDLINE_SIZE LEPTON_GL_SIZE
#define LEPTON_GGL_SIZE \
  (LEPTON_NUM_GROUPS * LEPTON_NUM_PLATS_PER_APUC * sizeof(bool))
#define LEPTON_RSP16_SIZE \
  (LEPTON_NUM_SECTIONS * LEPTON_NUM_RSP16_PLATS * sizeof(bool))
#define LEPTON_RSP16_SECTION_SIZE \
  LEPTON_NUM_RSP16_PLATS * sizeof(bool)
#define LEPTON_RSP256_SIZE \
  (LEPTON_NUM_SECTIONS * LEPTON_NUM_RSP256_PLATS * sizeof(bool))
#define LEPTON_RSP2K_SIZE \
  (LEPTON_NUM_SECTIONS * LEPTON_NUM_RSP2K_PLATS * sizeof(bool))
#define LEPTON_RSP32K_SIZE \
  (LEPTON_NUM_SECTIONS * LEPTON_NUM_RSP32K_PLATS * sizeof(bool))
#define LEPTON_L1_SIZE \
  (LEPTON_NUM_GROUPS * LEPTON_NUM_PLATS_PER_APUC * sizeof(bool))
#define LEPTON_L2_SIZE \
  (LEPTON_NUM_L2_PLATS * sizeof(bool))
#define LEPTON_LGL_SIZE \
  (LEPTON_NUM_LGL_PLATS * sizeof(bool))

typedef struct lepton_apuc_t {
  lepton_vr_t vrs[LEPTON_NUM_SBS];
  lepton_rl_t rl;
  lepton_gl_t gl;
  lepton_ggl_t ggl;
  lepton_rsp16_t rsp16;
  lepton_rsp256_t rsp256;
  lepton_rsp2k_t rsp2k;
  lepton_rsp32k_t rsp32k;
  lepton_l1_t l1[LEPTON_NUM_L1_ROWS];
  lepton_l2_t l2[LEPTON_NUM_L2_ROWS];
  lepton_lgl_t lgl;

  bool in_place;

  lepton_vr_t rwinh_filter;
  uint16_t rwinh_sects;
} lepton_apuc_t;

typedef struct lepton_vr_patch_t {
  lepton_vr_t *vr;
  lepton_vr_t *update;
} lepton_vr_patch_t;

typedef struct lepton_wordline_patch_t {
  lepton_vr_t *vr;
  size_t section;
  lepton_wordline_t *update;
} lepton_wordline_patch_t;

typedef struct lepton_wordline_map_t {
  size_t size;
  lepton_wordline_patch_t updates[];
} lepton_wordline_map_t;

typedef enum {
  LEPTON_L1_SRC_GGL,
  LEPTON_L1_SRC_LGL,
} lepton_l1_patch_src;

typedef struct lepton_l1_patch_t {
  lepton_l1_patch_src src;
  size_t l1_addr;
  union {
    lepton_ggl_t *ggl_patch;
    lepton_lgl_t *lgl_patch;
  };
} lepton_l1_patch_t;

typedef struct lepton_l2_patch_t {
  size_t l2_addr;
  lepton_l2_t *update;
} lepton_l2_patch_t;

typedef struct lepton_rsp16_section_patch_t {
  size_t section;
  lepton_rsp16_section_t *update;
} lepton_rsp16_section_patch_t;

typedef struct lepton_rsp16_section_map_t {
  size_t size;
  lepton_rsp16_section_patch_t *updates[];
} lepton_rsp16_section_map_t;

typedef struct lepton_rsp_patches_t {
  lepton_rsp16_t *rsp16_update;
  lepton_rsp256_t *rsp256_update;
  lepton_rsp2k_t *rsp2k_update;
  lepton_rsp32k_t *rsp32k_update;
} lepton_rsp_patches_t;

typedef struct lepton_rwinh_rst_patch_t {
  lepton_sm_t mask;
  bool has_read;
} lepton_rwinh_rst_patch_t;

typedef enum {
  LEPTON_SRC_RL,
  LEPTON_SRC_NRL,
  LEPTON_SRC_ERL,
  LEPTON_SRC_WRL,
  LEPTON_SRC_SRL,

  LEPTON_SRC_GL,
  LEPTON_SRC_GGL,
  LEPTON_SRC_RSP16,

  LEPTON_SRC_INV_RL,
  LEPTON_SRC_INV_NRL,
  LEPTON_SRC_INV_ERL,
  LEPTON_SRC_INV_WRL,
  LEPTON_SRC_INV_SRL,

  LEPTON_SRC_INV_GL,
  LEPTON_SRC_INV_GGL,
  LEPTON_SRC_INV_RSP16,
} lepton_src_t;

typedef lepton_wordline_t *(*lepton_unary_op_t)(lepton_wordline_t *nth1);
typedef lepton_wordline_t *(*lepton_binary_op_t)(lepton_wordline_t *nth1,
                                                 lepton_wordline_t *nth2);
typedef lepton_wordline_t *(*lepton_ternary_op_t)(lepton_wordline_t *nth1,
                                                  lepton_wordline_t *nth2,
                                                  lepton_wordline_t *nth3);

void lepton_plats_for_bank(size_t bank,
                           size_t *lower_plat_apc_0,
                           size_t *upper_plat_apc_0,
                           size_t *lower_plat_apc_1,
                           size_t *upper_plat_apc_1);

void lepton_patch_whole_vr(lepton_apuc_t *apuc, lepton_vr_patch_t *patch);
void lepton_patch_sb(lepton_apuc_t *apuc, lepton_wordline_map_t *patch);
void lepton_patch_gl(lepton_apuc_t *apuc, lepton_gl_t *patch);
void lepton_patch_ggl(lepton_apuc_t *apuc, lepton_ggl_t *patch);
void lepton_patch_lgl(lepton_apuc_t *apuc, lepton_lgl_t *patch);
void lepton_patch_whole_l1(lepton_apuc_t *apuc,
                           lepton_l1_t (*patch)[LEPTON_NUM_L1_ROWS]);
void lepton_patch_l1(lepton_apuc_t *apuc, lepton_l1_patch_t *patch);
void lepton_patch_whole_l2(lepton_apuc_t *apuc,
                           lepton_l2_t (*patch)[LEPTON_NUM_L2_ROWS]);
void lepton_patch_l2(lepton_apuc_t *apuc, lepton_l2_patch_t *patch);
void lepton_patch_rsp16(lepton_apuc_t *apuc, lepton_rsp16_t *patch);
void lepton_patch_partial_rsp16(lepton_apuc_t *apuc,
                                lepton_rsp16_section_map_t *patch);
void lepton_patch_rsp256(lepton_apuc_t *apuc, lepton_rsp256_t *patch);
void lepton_patch_rsp2k(lepton_apuc_t *apuc, lepton_rsp2k_t *patch);
void lepton_patch_rsp32k(lepton_apuc_t *apuc, lepton_rsp32k_t *patch);
void lepton_patch_rsps(lepton_apuc_t *apuc, lepton_rsp_patches_t *patches);
void lepton_patch_noop(lepton_apuc_t *apuc, void *patch);
void lepton_patch_rsp_end(lepton_apuc_t *apuc, void *patch);
void lepton_patch_rsp_start_ret(lepton_apuc_t *apuc, void *patch);
void lepton_patch_l2_end(lepton_apuc_t *apuc, void *patch);
void lepton_patch_rwinh_set(lepton_apuc_t *apuc, lepton_sm_t mask);
void lepton_patch_rwinh_rst(lepton_apuc_t *apuc,
                            lepton_rwinh_rst_patch_t *patch);

void lepton_init_vrs(lepton_vr_t (*vrs)[LEPTON_NUM_SBS], bool value);
void lepton_init_vr(lepton_vr_t *vr, bool value);
void lepton_init_gl(lepton_gl_t *gl, bool value);
void lepton_init_ggl(lepton_ggl_t *ggl, bool value);
void lepton_init_rsp16(lepton_rsp16_t *rsp16, bool value);
void lepton_init_rsp256(lepton_rsp256_t *rsp256, bool value);
void lepton_init_rsp2k(lepton_rsp2k_t *rsp2k, bool value);
void lepton_init_rsp32k(lepton_rsp32k_t *rsp32k, bool value);
void lepton_init_l1(lepton_l1_t *l1, bool value);
void lepton_init_l2(lepton_l2_t *l2, bool value);
void lepton_init_lgl(lepton_lgl_t *lgl, bool value);

void lepton_init_apuc(lepton_apuc_t *apuc);

void lepton_free_apuc(lepton_apuc_t *apuc);
void lepton_free_vr(lepton_vr_t *vr);
void lepton_free_rl(lepton_rl_t *rl);
void lepton_free_gl(lepton_gl_t *gl);
void lepton_free_ggl(lepton_ggl_t *ggl);
void lepton_free_rsp16(lepton_rsp16_t *rsp16);
void lepton_free_rsp256(lepton_rsp256_t *rsp256);
void lepton_free_rsp2k(lepton_rsp2k_t *rsp2k);
void lepton_free_rsp32k(lepton_rsp32k_t *rsp32k);
void lepton_free_l1(lepton_l1_t *l1);
void lepton_free_l2(lepton_l2_t *l2);
void lepton_free_lgl(lepton_lgl_t *lgl);
void lepton_free_wordline(lepton_wordline_t *wordline);
void lepton_free_rsp16_section(lepton_rsp16_section_t *rsp16_section);
void lepton_free_vr_patch(lepton_vr_patch_t *patch);
void lepton_free_wordline_patch(lepton_wordline_patch_t *patch);
void lepton_free_wordline_map(lepton_wordline_map_t *patch);
void lepton_free_l1_patch(lepton_l1_patch_t *patch);
void lepton_free_l2_patch(lepton_l2_patch_t *patch);
void lepton_free_rsp16_section_patch(lepton_rsp16_section_patch_t *patch);
void lepton_free_rsp16_section_map(lepton_rsp16_section_map_t *patch);
void lepton_free_rsp_patches(lepton_rsp_patches_t *patch);
void lepton_free_rwinh_rst_patch(lepton_rwinh_rst_patch_t *patch);

lepton_vr_t *lepton_build_vr(void);
lepton_gl_t *lepton_build_gl(void);
lepton_ggl_t *lepton_build_ggl(void);
lepton_rsp16_t *lepton_build_rsp16(void);
lepton_rsp256_t *lepton_build_rsp256(void);
lepton_rsp2k_t *lepton_build_rsp2k(void);
lepton_rsp32k_t *lepton_build_rsp32k(void);
lepton_l1_t *lepton_build_l1(void);
lepton_l2_t *lepton_build_l2(void);
lepton_lgl_t *lepton_build_lgl(void);

void lepton_reset_rl_in_place(lepton_apuc_t *apuc);
lepton_vr_patch_t *lepton_reset_rl(lepton_apuc_t *apuc);

void lepton_reset_gl_in_place(lepton_apuc_t *apuc);
lepton_gl_t *lepton_reset_gl(lepton_apuc_t *apuc);

void lepton_reset_ggl_in_place(lepton_apuc_t *apuc);
lepton_ggl_t *lepton_reset_ggl(lepton_apuc_t *apuc);

void lepton_reset_rsp16_in_place(lepton_apuc_t *apuc);
lepton_rsp16_t *lepton_reset_rsp16(lepton_apuc_t *apuc);

void lepton_reset_rsp256_in_place(lepton_apuc_t *apuc);
lepton_rsp256_t *lepton_reset_rsp256(lepton_apuc_t *apuc);

void lepton_reset_rsp2k_in_place(lepton_apuc_t *apuc);
lepton_rsp2k_t *lepton_reset_rsp2k(lepton_apuc_t *apuc);

void lepton_reset_rsp32k_in_place(lepton_apuc_t *apuc);
lepton_rsp32k_t *lepton_reset_rsp32k(lepton_apuc_t *apuc);

void lepton_reset_l1_in_place(lepton_apuc_t *apuc);
lepton_l1_t (*lepton_reset_l1(lepton_apuc_t *apuc))[LEPTON_NUM_L1_ROWS];

void lepton_reset_l2_in_place(lepton_apuc_t *apuc);
lepton_l2_t (*lepton_reset_l2(lepton_apuc_t *apuc))[LEPTON_NUM_L2_ROWS];

void lepton_reset_lgl_in_place(lepton_apuc_t *apuc);
lepton_lgl_t *lepton_reset_lgl(lepton_apuc_t *apuc);

bool lepton_any_section_plat(bool ***data, size_t section, size_t lower,
                             size_t upper);

void lepton_rsp_from_rsp(bool ***rsp_left,
                         bool ***rsp_right,
                         size_t left_width,
                         size_t right_width);

void lepton_rsp_from_contraction(bool ***rsp_left,
                                 bool ***rsp_right,
                                 size_t left_width,
                                 size_t right_width);

void lepton_rsp_from_expansion(bool ***rsp_left,
                               bool ***rsp_right,
                               size_t left_width,
                               size_t right_width);

/** [APL] RSP16 = RSP256; */
void lepton_rsp16_from_rsp256_in_place(lepton_apuc_t *apuc);
lepton_rsp16_t *lepton_rsp16_from_rsp256(lepton_apuc_t *apuc);

/** [APL] RSP256 = RSP16; */
void lepton_rsp256_from_rsp16_in_place(lepton_apuc_t *apuc);
lepton_rsp256_t *lepton_rsp256_from_rsp16(lepton_apuc_t *apuc);

/** [APL] RSP256 = RSP2K; */
void lepton_rsp256_from_rsp2k_in_place(lepton_apuc_t *apuc);
lepton_rsp256_t *lepton_rsp256_from_rsp2k(lepton_apuc_t *apuc);

/** [APL] RSP2K = RSP256; */
void lepton_rsp2k_from_rsp256_in_place(lepton_apuc_t *apuc);
lepton_rsp2k_t *lepton_rsp2k_from_rsp256(lepton_apuc_t *apuc);

/** [APL] RSP2K = RSP32K; */
void lepton_rsp2k_from_rsp32k_in_place(lepton_apuc_t *apuc);
lepton_rsp2k_t *lepton_rsp2k_from_rsp32k(lepton_apuc_t *apuc);

/** [APL] RSP32K = RSP2K; */
void lepton_rsp32k_from_rsp2k_in_place(lepton_apuc_t *apuc);
lepton_rsp32k_t *lepton_rsp32k_from_rsp2k(lepton_apuc_t *apuc);

/** [APL] NOOP; */
void lepton_noop_in_place(lepton_apuc_t *apuc);
void *lepton_noop(lepton_apuc_t *apuc);

/** [APL] FSEL_NOOP; */
void lepton_fsel_noop_in_place(lepton_apuc_t *apuc);
void *lepton_fsel_noop(lepton_apuc_t *apuc);

/** [APL] RSP_END; */
void lepton_rsp_end_in_place(lepton_apuc_t *apuc);
lepton_rsp_patches_t *lepton_rsp_end(lepton_apuc_t *apuc);

/** [APL] RSP_START_RET; */
void lepton_rsp_start_ret_in_place(lepton_apuc_t *apuc);
void *lepton_rsp_start_ret(lepton_apuc_t *apuc);

/** [APL] L2_END; */
void lepton_l2_end_in_place(lepton_apuc_t *apuc);
void *lepton_l2_end(lepton_apuc_t *apuc);

lepton_rl_t *lepton_rl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_nrl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_erl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_wrl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_srl(lepton_apuc_t *apuc);

lepton_rl_t *lepton_inv_rl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_inv_nrl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_inv_erl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_inv_wrl(lepton_apuc_t *apuc);
lepton_rl_t *lepton_inv_srl(lepton_apuc_t *apuc);

lepton_gl_t *lepton_gl(lepton_apuc_t *apuc);
lepton_gl_t *lepton_inv_gl(lepton_apuc_t *apuc);

lepton_ggl_t *lepton_ggl(lepton_apuc_t *apuc);
lepton_ggl_t *lepton_inv_ggl(lepton_apuc_t *apuc);

lepton_rsp16_t *lepton_rsp16(lepton_apuc_t *apuc);
lepton_rsp16_t *lepton_inv_rsp16(lepton_apuc_t *apuc);

lepton_gl_t *lepton_ternary_expr(lepton_apuc_t *apuc,
                                 lepton_gl_t *nth1,
                                 lepton_gl_t *nth2,
                                 lepton_gl_t *nth3,
                                 lepton_ternary_op_t op1,
                                 lepton_binary_op_t op2);

size_t lepton_count_masked_sections(lepton_sm_t mask);

lepton_vr_t *lepton_brsp16(lepton_rsp16_t *rsp16);

//  ___         _               _   _
// |_ _|_ _  __| |_ _ _ _  _ __| |_(_)___ _ _  ___
//  | || ' \(_-<  _| '_| || / _|  _| / _ \ ' \(_-<
// |___|_||_/__/\__|_|  \_,_\__|\__|_\___/_||_/__/
//

// __      __   _ _         _              _
// \ \    / / _(_) |_ ___  | |   ___  __ _(_)__
//  \ \/\/ / '_| |  _/ -_) | |__/ _ \/ _` | / _|
//   \_/\_/|_| |_|\__\___| |____\___/\__, |_\__|
//                                   |___/

void lepton_sb_op_eq_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_vr_t *vrs[], size_t num_vrs,
                                 lepton_binary_op_t op, lepton_gl_t *gl);

lepton_wordline_map_t *lepton_sb_op_eq_gl(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs,
                                          lepton_binary_op_t op,
                                          lepton_gl_t *gl);

void lepton_sb_op_eq_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                  lepton_vr_t *vrs[], size_t num_vrs,
                                  lepton_binary_op_t op, lepton_ggl_t *ggl);

lepton_wordline_map_t *lepton_sb_op_eq_ggl(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           lepton_binary_op_t op,
                                           lepton_ggl_t *ggl);

void lepton_sb_op_eq_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_vr_t *vrs[], size_t num_vrs,
                                 lepton_binary_op_t op, lepton_rl_t *rl);

lepton_wordline_map_t *lepton_sb_op_eq_rl(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs,
                                          lepton_binary_op_t op,
                                          lepton_rl_t *rl);

void lepton_sb_op_eq_rsp16_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                    lepton_vr_t *vrs[], size_t num_vrs,
                                    lepton_binary_op_t op,
                                    lepton_rsp16_t *rsp16);

lepton_wordline_map_t *lepton_sb_op_eq_rsp16(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_vr_t *vrs[],
                                             size_t num_vrs,
                                             lepton_binary_op_t op,
                                             lepton_rsp16_t *rsp16);

lepton_wordline_map_t *lepton_sb_op_eq_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           lepton_binary_op_t op,
                                           void *src,
                                           lepton_src_t src_type);

/**
 * [APL] msk: <SB> = <SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
lepton_wordline_map_t *lepton_sb_from_src(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs,
                                          void *src,
                                          lepton_src_t src_type);

/**
 * [APL] msk: <SB> = ~<SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
lepton_wordline_map_t *lepton_sb_from_inv_src(lepton_apuc_t *apuc,
                                              lepton_sm_t mask,
                                              lepton_vr_t *vrs[],
                                              size_t num_vrs,
                                              void *src,
                                              lepton_src_t src_type);

/**
 * [APL] msk: <SB> ?= <SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
lepton_wordline_map_t *lepton_sb_cond_eq_src(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_vr_t *vrs[],
                                             size_t num_vrs,
                                             void *src,
                                             lepton_src_t src_type);

/**
 * [APL] msk: <SB> ?= ~<SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
lepton_wordline_map_t *lepton_sb_cond_eq_inv_src(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask,
                                                 lepton_vr_t *vrs[],
                                                 size_t num_vrs,
                                                 void *src,
                                                 lepton_src_t src_type);

//  ___             _   _              _
// | _ \___ __ _ __| | | |   ___  __ _(_)__
// |   / -_) _` / _` | | |__/ _ \/ _` | / _|
// |_|_\___\__,_\__,_| |____\___/\__, |_\__|
//                               |___/

//   ___    ___
//  <  /   |_  |
//  / /   / __/
// /_( ) /____/
//   |/

// Read-logic Instructions 1 and 2

/**
 * Read-logic Instructions 1 and 2
 * [APL  1] msk: RL = 1
 * [APL  2] msk: RL = 0
 * Set all columns of RL to a given bit through a mask
 */
void lepton_set_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask, bool bit);
lepton_wordline_map_t *lepton_set_rl(lepton_apuc_t *apuc, lepton_sm_t mask,
                                     bool bit);

//    __ __    __               ___           ____     ___  ___
//   / // /__ / /__  ___ ____  / _/__  ____  |_  /    |_  |/ _ \
//  / _  / -_) / _ \/ -_) __/ / _/ _ \/ __/ _/_ <_ _ / __// // /
// /_//_/\__/_/ .__/\__/_/   /_/ \___/_/   /____(_|_)____/\___/
//           /_/

// Helper for Instructions 3 through 20

lepton_wordline_t *lepton_conjoin_sections_in_place(lepton_vr_t *vrs[],
                                                    size_t num_vrs,
                                                    size_t section,
                                                    lepton_wordline_t *conj);

lepton_wordline_t *lepton_conjoin_sections(lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           size_t section);

//   ____     ______    _______     _______    ______
//  / / /    <  <  /   <  / / /    <  /_  /   <  / _ \
// /_  _/    / // /    / /_  _/    / / / /    / /\_, /
//  /_/( )  /_//_( )  /_/ /_/( )  /_/ /_( )  /_//___/
//     |/        |/          |/         |/

// Read-logic instructions 4, 11, 14, 17, 19
//   |  4.  RL  =  <SRC>           | :=               <SRC>  |
//   | 11.  RL |=  <SRC>           | |=               <SRC>  |
//   | 14.  RL &=  <SRC>           | &=               <SRC>  |
//   | 17.  RL &= ~<SRC>           | &=              ~<SRC>  |
//   | 19.  RL ^=  <SRC>           | ^=               <SRC>  |

void lepton_rl_op_eq_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_binary_op_t op, lepton_gl_t *gl);
lepton_wordline_map_t *lepton_rl_op_eq_gl(lepton_apuc_t *apuc, lepton_sm_t mask,
                                          lepton_binary_op_t op,
                                          lepton_gl_t *gl);

void lepton_rl_op_eq_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                  lepton_binary_op_t op, lepton_ggl_t *ggl);
lepton_wordline_map_t *lepton_rl_op_eq_ggl(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_binary_op_t op,
                                           lepton_ggl_t *ggl);

void lepton_rl_op_eq_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_binary_op_t op, lepton_rl_t *rl);
lepton_wordline_map_t *lepton_rl_op_eq_rl(lepton_apuc_t *apuc, lepton_sm_t mask,
                                          lepton_binary_op_t op,
                                          lepton_rl_t *rl);

void lepton_rl_op_eq_rsp16_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                    lepton_binary_op_t op,
                                    lepton_rsp16_t *rsp16);
lepton_wordline_map_t *lepton_rl_op_eq_rsp16(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_binary_op_t op,
                                             lepton_rsp16_t *rsp16);

lepton_wordline_map_t *lepton_rl_op_eq_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_binary_op_t op,
                                           void *src,
                                           lepton_src_t src_type);

//   ____
//  / / /
// /_  _/
//  /_/

/**
 * Read-logic Instruction 4
 * [APL  4] msk: RL = <SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_from_src(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          void *src,
                                          lepton_src_t src_type);

/**
 * Read-logic Instruction 4
 * [APL  4] msk: RL = ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_from_inv_src(lepton_apuc_t *apuc,
                                              lepton_sm_t mask,
                                              void *src,
                                              lepton_src_t src_type);

//   ______
//  <  <  /
//  / // /
// /_//_/

/**
 * Read-logic Instruction 11
 * [APL 11] msk: RL |= <SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_or_eq_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           void *src,
                                           lepton_src_t src_type);

/**
 * Read-logic Instruction 11
 * [APL 11] msk: RL |= ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_or_eq_inv_src(lepton_apuc_t *apuc,
                                               lepton_sm_t mask,
                                               void *src,
                                               lepton_src_t src_type);

//   _______
//  <  / / /
//  / /_  _/
// /_/ /_/

/**
 * Read-logic Instruction 14
 * [APL 14] msk: RL &= <SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_and_eq_src(lepton_apuc_t *apuc,
                                            lepton_sm_t mask,
                                            void *src,
                                            lepton_src_t src_type);

//   _______
//  <  /_  /
//  / / / /
// /_/ /_/

/**
 * Read-logic Instruction 17
 * [APL 17] msk: RL &= ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_and_eq_inv_src(lepton_apuc_t *apuc,
                                                lepton_sm_t mask,
                                                void *src,
                                                lepton_src_t src_type);

//   ______
//  <  / _ \
//  / /\_, /
// /_//___/

/**
 * Read-logic Instruction 19
 * [APL 19] msk: RL ^= <SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_xor_eq_src(lepton_apuc_t *apuc,
                                            lepton_sm_t mask,
                                            void *src,
                                            lepton_src_t src_type);

/**
 * Read-logic Instruction 19
 * [APL 19] msk: RL ^= ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
lepton_wordline_map_t *lepton_rl_xor_eq_inv_src(lepton_apuc_t *apuc,
                                                lepton_sm_t mask,
                                                void *src,
                                                lepton_src_t src_type);

//    ____     ______      _______     _______     ______
//   |_  /    <  / _ \    <  /_  /    <  / __/    <  ( _ )
//  _/_ <_    / / // /    / //_ <_    / / _ \_    / / _  |
// /____( )  /_/\___( )  /_/____( )  /_/\___( )  /_/\___/
//      |/          |/          |/          |/

// Read-logic instructions 3, 10, 13, 16, 18
//   |  3.  RL  =  <SB>            | :=  <SB>                |
//   | 10.  RL |=  <SB>            | |=  <SB>                |
//   | 13.  RL &=  <SB>            | &=  <SB>                |
//   | 16.  RL &= ~<SB>            | &= ~<SB>                |
//   | 18.  RL ^=  <SB>            | ^=  <SB>                |

void lepton_rl_op_eq_sb_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_binary_op_t op, lepton_vr_t *vrs[],
                                 size_t num_vrs);
lepton_wordline_map_t *lepton_rl_op_eq_sb(lepton_apuc_t *apuc, lepton_sm_t mask,
                                          lepton_binary_op_t op,
                                          lepton_vr_t *vrs[], size_t num_vrs);

//    ____
//   |_  /
//  _/_ <
// /____/

/**
 * Read-logic Instruction 3
 * [APL  3] msk: RL = <SB>
 */
lepton_wordline_map_t *lepton_rl_from_sb(lepton_apuc_t *apuc,
                                         lepton_sm_t mask,
                                         lepton_vr_t *vrs[],
                                         size_t num_vrs);

/**
 * Read-logic Instruction 3
 * [APL  3] msk: RL = ~<SB>
 */
lepton_wordline_map_t *lepton_rl_from_inv_sb(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_vr_t *vrs[],
                                             size_t num_vrs);

//   ______
//  <  / _ \
//  / / // /
// /_/\___/

/**
 * Read-logic Instruction 10
 * [APL 10] msk: RL |= <SB>
 */
lepton_wordline_map_t *lepton_rl_or_eq_sb(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs);

//   _______
//  <  /_  /
//  / //_ <
// /_/____/

/**
 * Read-logic Instruction 13
 * [APL 13] msk: RL &= <SB>
 */
lepton_wordline_map_t *lepton_rl_and_eq_sb(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs);

//   _______
//  <  / __/
//  / / _ \
// /_/\___/

/**
 * Read-logic Instruction 16
 * [APL 16] msk: RL &= ~<SB>
 */
lepton_wordline_map_t *lepton_rl_and_eq_inv_sb(lepton_apuc_t *apuc,
                                               lepton_sm_t mask,
                                               lepton_vr_t *vrs[],
                                               size_t num_vrs);

//   ______
//  <  ( _ )
//  / / _  |
// /_/\___/

/**
 * Read-logic Instruction 18
 * [APL 18] msk: RL ^= <SB>
 */
lepton_wordline_map_t *lepton_rl_xor_eq_sb(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs);

//    ____     ______      _______     ___  ___
//   / __/    <  /_  |    <  / __/    |_  |/ _ \
//  /__ \_    / / __/_    / /__ \_   / __// // /
// /____( )  /_/____( )  /_/____( ) /____/\___/
//      |/          |/          |/

// Read-logic instruction 5, 12, 15, 20

//   |  5.  RL  =  <SB> &  <SRC>   | :=  <SB>    &    <SRC>  |
//   | 12.  RL |=  <SB> &  <SRC>   | |=  <SB>    &    <SRC>  |
//   | 15.  RL &=  <SB> &  <SRC>   | &=  <SB>    &    <SRC>  |
//   | 20.  RL ^=  <SB> &  <SRC>   | ^=  <SB>    &    <SRC>  |

void lepton_rl_op_eq_sb_and_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                        lepton_ternary_op_t op1,
                                        lepton_binary_op_t op2,
                                        lepton_vr_t *vrs[], size_t num_vrs,
                                        lepton_gl_t *gl);
lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_gl(lepton_apuc_t *apuc, lepton_sm_t mask,
                          lepton_ternary_op_t op1, lepton_binary_op_t op2,
                          lepton_vr_t *vrs[], size_t num_vrs, lepton_gl_t *gl);

void lepton_rl_op_eq_sb_and_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                         lepton_ternary_op_t op1,
                                         lepton_binary_op_t op2,
                                         lepton_vr_t *vrs[], size_t num_vrs,
                                         lepton_ggl_t *ggl);
lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_ggl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_ternary_op_t op1, lepton_binary_op_t op2,
                           lepton_vr_t *vrs[], size_t num_vrs,
                           lepton_ggl_t *ggl);

void lepton_rl_op_eq_sb_and_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                        lepton_ternary_op_t op1,
                                        lepton_binary_op_t op2,
                                        lepton_vr_t *vrs[], size_t num_vrs,
                                        lepton_rl_t *rl);
lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_rl(lepton_apuc_t *apuc, lepton_sm_t mask,
                          lepton_ternary_op_t op1, lepton_binary_op_t op2,
                          lepton_vr_t *vrs[], size_t num_vrs, lepton_rl_t *rl);

void lepton_rl_op_eq_sb_and_rsp16_in_place(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_ternary_op_t op1,
                                           lepton_binary_op_t op2,
                                           lepton_vr_t *vrs[], size_t num_vrs,
                                           lepton_rsp16_t *rsp16);
lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_rsp16(lepton_apuc_t *apuc, lepton_sm_t mask,
                             lepton_ternary_op_t op1, lepton_binary_op_t op2,
                             lepton_vr_t *vrs[], size_t num_vrs,
                             lepton_rsp16_t *rsp16);

/**
 * Abstract instructions 5, 12, 15, 20.
 */
lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_ternary_op_t op1, lepton_binary_op_t op2,
                           lepton_vr_t *vrs[], size_t num_vrs, void *src,
                           lepton_src_t src_type);

//    ____
//   / __/
//  /__ \
// /____/

/**
 * Read-logic Instruction 5
 * [APL  5] msk: RL = <SB> & <SRC>
 */
lepton_wordline_map_t *lepton_rl_from_sb_and_src(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask,
                                                 lepton_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 lepton_src_t src_type);

//   ______
//  <  /_  |
//  / / __/
// /_/____/

lepton_wordline_map_t *lepton_rl_or_eq_sb_and_src(lepton_apuc_t *apuc,
                                                  lepton_sm_t mask,
                                                  lepton_vr_t *vrs[],
                                                  size_t num_vrs, void *src,
                                                  lepton_src_t src_type);

lepton_wordline_map_t *lepton_rl_or_eq_sb_and_inv_src(lepton_apuc_t *apuc,
                                                      lepton_sm_t mask,
                                                      lepton_vr_t *vrs[],
                                                      size_t num_vrs, void *src,
                                                      lepton_src_t src_type);

//   _______
//  <  / __/
//  / /__ \
// /_/____/

lepton_wordline_map_t *lepton_rl_and_eq_sb_and_src(lepton_apuc_t *apuc,
                                                   lepton_sm_t mask,
                                                   lepton_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   lepton_src_t src_type);

lepton_wordline_map_t *
lepton_rl_and_eq_sb_and_inv_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                                lepton_vr_t *vrs[], size_t num_vrs, void *src,
                                lepton_src_t src_type);

//    ___  ___
//   |_  |/ _ \
//  / __// // /
// /____/\___/

lepton_wordline_map_t *lepton_rl_xor_eq_sb_and_src(lepton_apuc_t *apuc,
                                                   lepton_sm_t mask,
                                                   lepton_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   lepton_src_t src_type);

lepton_wordline_map_t *
lepton_rl_xor_eq_sb_and_inv_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                                lepton_vr_t *vrs[], size_t num_vrs, void *src,
                                lepton_src_t src_type);

//   ____     ____    ___      ___
//  / __/    /_  /   ( _ )    / _ \
// / _ \_     / /   / _  |    \_, /
// \___( )   /_( )  \___( )  /___/
//     |/      |/       |/

// Read-logic instruction 6, 7, 8, 9
//   |  6.  RL  =  <SB> |  <SRC>   | :=  <SB>    |    <SRC>  |
//   |  7.  RL  =  <SB> ^  <SRC>   | :=  <SB>    ^    <SRC>  |
//   |  8.  RL  = ~<SB> &  <SRC>   | := ~<SB>    &    <SRC>  |
//   |  9.  RL  =  <SB> & ~<SRC>   | :=  <SB>    &   ~<SRC>  |

void lepton_rl_from_sb_binop_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                         lepton_vr_t *vrs[], size_t num_vrs,
                                         lepton_binary_op_t op,
                                         lepton_gl_t *gl);
lepton_wordline_map_t *
lepton_rl_from_sb_binop_gl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_vr_t *vrs[], size_t num_vrs,
                           lepton_binary_op_t op, lepton_gl_t *gl);

void lepton_rl_from_sb_binop_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                          lepton_vr_t *vrs[], size_t num_vrs,
                                          lepton_binary_op_t op,
                                          lepton_ggl_t *ggl);
lepton_wordline_map_t *
lepton_rl_from_sb_binop_ggl(lepton_apuc_t *apuc, lepton_sm_t mask,
                            lepton_vr_t *vrs[], size_t num_vrs,
                            lepton_binary_op_t op, lepton_ggl_t *ggl);

void lepton_rl_from_sb_binop_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                         lepton_vr_t *vrs[], size_t num_vrs,
                                         lepton_binary_op_t op,
                                         lepton_rl_t *rl);
lepton_wordline_map_t *
lepton_rl_from_sb_binop_rl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_vr_t *vrs[], size_t num_vrs,
                           lepton_binary_op_t op, lepton_rl_t *rl);

void lepton_rl_from_sb_binop_rsp16_in_place(lepton_apuc_t *apuc,
                                            lepton_sm_t mask,
                                            lepton_vr_t *vrs[], size_t num_vrs,
                                            lepton_binary_op_t op,
                                            lepton_rsp16_t *rsp16);
lepton_wordline_map_t *
lepton_rl_from_sb_binop_rsp16(lepton_apuc_t *apuc, lepton_sm_t mask,
                              lepton_vr_t *vrs[], size_t num_vrs,
                              lepton_binary_op_t op, lepton_rsp16_t *rsp16);

lepton_wordline_map_t *lepton_rl_from_sb_binop_src(
    lepton_apuc_t *apuc, lepton_sm_t mask, lepton_vr_t *vrs[], size_t num_vrs,
    lepton_binary_op_t op, void *src, lepton_src_t src_type);

//   ____
//  / __/
// / _ \
// \___/

/**
 * Read-logic Instruction 6
 * [APL  6] msk: RL = <SB> | <SRC>
 */
lepton_wordline_map_t *
lepton_rl_from_sb_or_src(lepton_apuc_t *apuc, lepton_sm_t mask, lepton_vr_t *vrs[],
                         size_t num_vrs, void *src, lepton_src_t src_type);

/**
 * Read-logic Instruction 6
 * [APL  6] msk: RL = <SB> | ~<SRC>
 */
lepton_wordline_map_t *lepton_rl_from_sb_or_inv_src(lepton_apuc_t *apuc,
                                                    lepton_sm_t mask,
                                                    lepton_vr_t *vrs[],
                                                    size_t num_vrs, void *src,
                                                    lepton_src_t src_type);

//  ____
// /_  /
//  / /
// /_/

/**
 * Read-logic Instruction 7
 * [APL  7] msk: RL = <SB> ^ <SRC>
 */
lepton_wordline_map_t *lepton_rl_from_sb_xor_src(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask,
                                                 lepton_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 lepton_src_t src_type);

/**
 * Read-logic Instruction 7
 * [APL  7] msk: RL = <SB> ^ ~<SRC>
 */
lepton_wordline_map_t *lepton_rl_from_sb_xor_inv_src(lepton_apuc_t *apuc,
                                                     lepton_sm_t mask,
                                                     lepton_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     lepton_src_t src_type);

//   ___
//  ( _ )
// / _  |
// \___/

/**
 * Read-logic Instruction 8
 * [APL 8] msk: RL = ~<SB> & <SRC>
 */
lepton_wordline_map_t *lepton_rl_from_inv_sb_and_src(lepton_apuc_t *apuc,
                                                     lepton_sm_t mask,
                                                     lepton_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     lepton_src_t src_type);

/**
 * Read-logic Instruction 8
 * [APL 8] msk: RL = ~<SB> & ~<SRC>
 */
lepton_wordline_map_t *
lepton_rl_from_inv_sb_and_inv_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                                  lepton_vr_t *vrs[], size_t num_vrs, void *src,
                                  lepton_src_t src_type);

//   ___
//  / _ \
//  \_, /
// /___/

/**
 * Read-logic Instruction 9
 * [APL 9] msk: RL = <SB> & ~<SRC>
 */
lepton_wordline_map_t *lepton_rl_from_sb_and_inv_src(lepton_apuc_t *apuc,
                                                     lepton_sm_t mask,
                                                     lepton_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     lepton_src_t src_type);

//  ___     ___      _   _              _
// | _ \___/ __| ___| | | |   ___  __ _(_)__
// |   /___\__ \/ -_) | | |__/ _ \/ _` | / _|
// |_|_\   |___/\___|_| |____\___/\__, |_\__|
//                                |___/

/**
 * [APL] msk: RSP16 = RL;
 */
void lepton_rsp16_from_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask);
lepton_rsp16_section_map_t *lepton_rsp16_from_rl(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask);

/**
 * [APL] msk: GL = RL;
 */
void lepton_gl_from_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask);
lepton_gl_t *lepton_gl_from_rl(lepton_apuc_t *apuc, lepton_sm_t mask);

/**
 * [APL] msk: GGL = RL;
 */
void lepton_ggl_from_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask);
lepton_ggl_t *lepton_ggl_from_rl(lepton_apuc_t *apuc, lepton_sm_t mask);

/**
 * [APL] LX = GGL;
 */
void lepton_l1_from_ggl_in_place(lepton_apuc_t *apuc, size_t l1_addr);
lepton_l1_patch_t *lepton_l1_from_ggl(lepton_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] LGL = <LX>;
 */
void lepton_lgl_from_l1_in_place(lepton_apuc_t *apuc, size_t l1_addr);
lepton_lgl_t *lepton_lgl_from_l1(lepton_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] LX = LGL;
 */
void lepton_l2_from_lgl_in_place(lepton_apuc_t *apuc, size_t l2_addr);
lepton_l2_patch_t *lepton_l2_from_lgl(lepton_apuc_t *apuc, size_t l2_addr);

/**
 * [APL] LGL = <LX>;
 */
void lepton_lgl_from_l2_in_place(lepton_apuc_t *apuc, size_t l2_addr);
lepton_lgl_t *lepton_lgl_from_l2(lepton_apuc_t *apuc, size_t l2_addr);

/**
 * [APL] LX = LGL;
 */
void lepton_l1_from_lgl_in_place(lepton_apuc_t *apuc, size_t l1_addr);
lepton_l1_patch_t *lepton_l1_from_lgl(lepton_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] GGL = <LX>;
 */
void lepton_ggl_from_l1_in_place(lepton_apuc_t *apuc, size_t l1_addr);
lepton_ggl_t *lepton_ggl_from_l1(lepton_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] msk: GGL = RL & <LX>;
 */
void lepton_ggl_from_rl_and_l1_in_place(lepton_apuc_t *apuc, size_t mask,
                                        size_t l1_addr);
lepton_ggl_t *lepton_ggl_from_rl_and_l1(lepton_apuc_t *apuc, size_t mask,
                                        size_t l1_addr);

//  ___             _   ____      __   _ _          ___      _    _ _    _ _
// | _ \___ __ _ __| | / /\ \    / / _(_) |_ ___ __|_ _|_ _ | |_ (_) |__(_) |_
// |   / -_) _` / _` |/ /  \ \/\/ / '_| |  _/ -_)___| || ' \| ' \| | '_ \ |  _|
// |_|_\___\__,_\__,_/_/    \_/\_/|_| |_|\__\___|  |___|_||_|_||_|_|_.__/_|\__|

/**
 * [APL] msk: RL = <SB> RWINH_SET;
 */
void lepton_rwinh_set_in_place(lepton_apuc_t *apuc, size_t mask);
size_t lepton_rwinh_set(lepton_apuc_t *apuc, size_t mask);

/**
 * [APL] msk: RL = <SB> RWINH_RST;
 */
void lepton_rwinh_rst_in_place(lepton_apuc_t *apuc, size_t mask, bool has_read);
lepton_rwinh_rst_patch_t *lepton_rwinh_rst(lepton_apuc_t *apuc, size_t mask,
                                           bool has_read);

#define lepton_rand_bool() (rand() & 1)
void lepton_randomize_apuc(lepton_apuc_t *apuc, uint32_t seed);
void lepton_repeatably_randomize_apuc(lepton_apuc_t *apuc);

/* #ifdef __cplusplus */
/* } */
/* #endif */

#endif // __GSI__LEPTON__APUC_H__
