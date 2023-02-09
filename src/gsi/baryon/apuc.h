#ifndef __GSI__BARYON__APUC_H__
#define __GSI__BARYON__APUC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "constants.h"
#include "fifo.h"

#define BARYON_FOREACH_RANGE_3(var, lower, upper, step_size, block) \
  for (size_t var = lower; var < upper; var += step_size) {         \
    block;                                                          \
  }

#define BARYON_FOREACH_RANGE_2(var, lower, upper, block) \
  BARYON_FOREACH_RANGE_3(var, lower, upper, 1, block)

#define BARYON_FOREACH_RANGE_1(var, upper, block) \
  BARYON_FOREACH_RANGE_3(var, 0, upper, 1, block)

#define BARYON_EXPAND_FOREACH_RANGE(_1, _2, _3, _4, _5, NAME, ...) \
  NAME

#define baryon_foreach_range(...)                     \
  BARYON_EXPAND_FOREACH_RANGE(__VA_ARGS__,            \
                              BARYON_FOREACH_RANGE_3, \
                              BARYON_FOREACH_RANGE_2, \
                              BARYON_FOREACH_RANGE_1)(__VA_ARGS__)

#define baryon_foreach_masked_section(mask, section, block) \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, {      \
    if ((1 << section) & (mask)) {                          \
      block;                                                \
    }                                                       \
  })

#define baryon_foreach_unmasked_section(mask, section, block)                  \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, {                         \
    if (((1 << section) & (mask)) == 0) {                                      \
      block;                                                                   \
    }                                                                          \
  })

#define baryon_foreach_vr_row(row, block) \
  baryon_foreach_range(row, BARYON_NUM_SBS, block)

#define baryon_foreach_vr_section(section, block) \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, block)

#define baryon_foreach_vr_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_PLATS_PER_APUC, block)

#define baryon_foreach_wordline_plat baryon_foreach_vr_plat

#define baryon_foreach_vr_section_plat(section, plat, block) \
  baryon_foreach_vr_section(section, {                       \
    baryon_foreach_vr_plat(plat, block);                     \
  })

#define baryon_foreach_vr_row_section_plat(row, section, plat, block) \
  baryon_foreach_vr_row(row, {                                        \
    baryon_foreach_vr_section(section, {                              \
      baryon_foreach_vr_plat(plat, block);                            \
    });                                                               \
  })

#define baryon_foreach_rl_section baryon_foreach_vr_section
#define baryon_foreach_rl_plat baryon_foreach_vr_plat
#define baryon_foreach_rl_section_plat baryon_foreach_vr_section_plat

#define baryon_foreach_gl_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_PLATS_PER_APUC, block)

#define baryon_foreach_ggl_group(group, block) \
  baryon_foreach_range(group, BARYON_NUM_GROUPS, block)

#define baryon_foreach_ggl_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_PLATS_PER_APUC, block)

#define baryon_foreach_ggl_group_plat(group, plat, block) \
  baryon_foreach_ggl_group(group, {                       \
    baryon_foreach_ggl_plat(plat, block);                 \
  })

#define baryon_foreach_l1_group_plat baryon_foreach_ggl_group_plat

#define baryon_foreach_lgl_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_LGL_PLATS, block)

#define baryon_foreach_l1_row(row, block) \
  baryon_foreach_range(row, BARYON_NUM_L1_ROWS, block)

#define baryon_foreach_l1_group(group, block) \
  baryon_foreach_range(group, BARYON_NUM_GROUPS, block)

#define baryon_foreach_l1_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_PLATS_PER_APUC, block)

#define baryon_foreach_l1_row_group_plat(row, group, plat, block) \
  baryon_foreach_l1_row(row, {                                    \
    baryon_foreach_l1_group(group, {                              \
      baryon_foreach_l1_plat(plat, block);                        \
    })                                                            \
  })

#define baryon_foreach_l2_row(row, block) \
  baryon_foreach_range(row, BARYON_NUM_L2_ROWS, block)

#define baryon_foreach_l2_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_L2_PLATS, block)

#define baryon_foreach_l2_row_plat(row, plat, block) \
  baryon_foreach_l2_row(row, {                       \
    baryon_foreach_l2_plat(plat, block);             \
  })

#define baryon_foreach_rsp16_section(section, block) \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, block)

#define baryon_foreach_rsp16_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_RSP16_PLATS, block)

#define baryon_foreach_rsp16_section_plat(section, plat, block) \
  baryon_foreach_rsp16_section(section, {                       \
    baryon_foreach_rsp16_plat(plat, block);                     \
  })

#define baryon_foreach_rsp256_section(section, block) \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, block)

#define baryon_foreach_rsp256_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_RSP256_PLATS, block)

#define baryon_foreach_rsp256_section_plat(section, plat, block) \
  baryon_foreach_rsp256_section(section, {                       \
    baryon_foreach_rsp256_plat(plat, block);                     \
  })

#define baryon_foreach_rsp2k_section(section, block) \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, block)

#define baryon_foreach_rsp2k_plat(plat, block) \
  baryon_foreach_range(plat, BARYON_NUM_RSP2K_PLATS, block)

#define baryon_foreach_rsp2k_section_plat(section, plat, block) \
  baryon_foreach_rsp2k_section(section, {                       \
    baryon_foreach_rsp2k_plat(plat, block);                     \
  })

#define baryon_foreach_rsp32k_section(section, block) \
  baryon_foreach_range(section, BARYON_NUM_SECTIONS, block)

#define baryon_foreach_half_bank(half_bank, block) \
  baryon_foreach_range(half_bank, BARYON_NUM_HALF_BANKS_PER_APUC, block)

void baryon_bank_group_row(size_t l1_addr, size_t *bank, size_t *group,
                           size_t *row);

#define baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, block)            \
  {                                                                         \
    size_t lower_plat_apc_0;                                                \
    size_t upper_plat_apc_0;                                                \
    size_t lower_plat_apc_1;                                                \
    size_t upper_plat_apc_1;                                                \
    baryon_plats_for_bank(bank, &lower_plat_apc_0, &upper_plat_apc_0,       \
                          &lower_plat_apc_1, &upper_plat_apc_1);            \
    size_t lgl_plat;                                                        \
    baryon_foreach_range(l1_plat, lower_plat_apc_0, upper_plat_apc_0, {     \
      lgl_plat = l1_plat - lower_plat_apc_0;                                \
      block;                                                                \
    });                                                                     \
    baryon_foreach_range(l1_plat, lower_plat_apc_1, upper_plat_apc_1, {     \
      lgl_plat =                                                            \
          l1_plat - lower_plat_apc_1 + BARYON_NUM_PLATS_PER_HALF_BANK * 2;  \
      block;                                                                \
    });                                                                     \
  }

#define baryon_any_plat_in_place(lhs, rhs, section, step, lower, upper)        \
  {                                                                            \
    (*lhs)[section][step] = false;                                             \
    baryon_foreach_range(plat, lower, upper, {                                 \
      if ((*rhs)[section][plat]) {                                             \
        (*lhs)[section][step] = true;                                          \
        break;                                                                 \
      }                                                                        \
    })                                                                         \
  }

#define baryon_rsp_from_contraction(lhs, rhs, left_width, right_width)         \
  {                                                                            \
    size_t step_size = (right_width) / (left_width);                           \
    size_t num_steps = left_width;                                             \
    baryon_foreach_range(step, num_steps, {                                    \
      size_t lower = step * step_size;                                         \
      size_t upper = lower + step_size;                                        \
      baryon_foreach_rsp16_section(section, {                                  \
        baryon_any_plat_in_place(lhs, rhs, section, step, lower, upper);       \
      });                                                                      \
    });                                                                        \
  }

#define baryon_rsp_from_expansion(lhs, rhs, left_width, right_width)           \
  {                                                                            \
    size_t step_size = (left_width) / (right_width);                           \
    size_t num_steps = right_width;                                            \
    baryon_foreach_range(step, num_steps, {                                    \
      size_t lower = step * step_size;                                         \
      size_t upper = lower + step_size;                                        \
      baryon_foreach_range(section, BARYON_NUM_SECTIONS, {                     \
        baryon_foreach_range(plat, lower, upper, {                             \
          (*lhs)[section][plat] = (*rhs)[section][step];                       \
        });                                                                    \
      });                                                                      \
    });                                                                        \
  }

typedef bool baryon_vr_t[BARYON_NUM_SECTIONS][BARYON_NUM_PLATS_PER_APUC];
typedef baryon_vr_t baryon_rl_t;
typedef baryon_vr_t baryon_brsp16_t;
typedef uint16_t baryon_sm_t;
typedef uint32_t baryon_re_t;
typedef uint16_t baryon_ewe_t;
typedef bool baryon_gl_t[BARYON_NUM_PLATS_PER_APUC];
typedef bool baryon_ggl_t[BARYON_NUM_GROUPS][BARYON_NUM_PLATS_PER_APUC];
typedef bool baryon_rsp16_t[BARYON_NUM_SECTIONS][BARYON_NUM_RSP16_PLATS];
typedef bool baryon_rsp256_t[BARYON_NUM_SECTIONS][BARYON_NUM_RSP256_PLATS];
typedef bool baryon_rsp2k_t[BARYON_NUM_SECTIONS][BARYON_NUM_RSP2K_PLATS];
typedef bool baryon_rsp32k_t[BARYON_NUM_SECTIONS];
typedef bool baryon_l1_t[BARYON_NUM_GROUPS][BARYON_NUM_PLATS_PER_APUC];
typedef bool baryon_l2_t[BARYON_NUM_L2_PLATS];
typedef bool baryon_lgl_t[BARYON_NUM_LGL_PLATS];

typedef bool baryon_wordline_t[BARYON_NUM_PLATS_PER_APUC];
typedef bool baryon_rsp16_section_t[BARYON_NUM_RSP16_PLATS];

#define BARYON_VR_SIZE \
  (BARYON_NUM_SECTIONS * BARYON_NUM_PLATS_PER_APUC * sizeof(bool))
#define BARYON_RL_SIZE BARYON_VR_SIZE
#define BARYON_GL_SIZE \
  (BARYON_NUM_PLATS_PER_APUC * sizeof(bool))
#define BARYON_WORDLINE_SIZE BARYON_GL_SIZE
#define BARYON_GGL_SIZE \
  (BARYON_NUM_GROUPS * BARYON_NUM_PLATS_PER_APUC * sizeof(bool))
#define BARYON_RSP16_SIZE \
  (BARYON_NUM_SECTIONS * BARYON_NUM_RSP16_PLATS * sizeof(bool))
#define BARYON_RSP16_SECTION_SIZE \
  BARYON_NUM_RSP16_PLATS * sizeof(bool)
#define BARYON_RSP256_SIZE \
  (BARYON_NUM_SECTIONS * BARYON_NUM_RSP256_PLATS * sizeof(bool))
#define BARYON_RSP2K_SIZE \
  (BARYON_NUM_SECTIONS * BARYON_NUM_RSP2K_PLATS * sizeof(bool))
#define BARYON_RSP32K_SIZE \
  (BARYON_NUM_SECTIONS * sizeof(bool))
#define BARYON_L1_SIZE \
  (BARYON_NUM_GROUPS * BARYON_NUM_PLATS_PER_APUC * sizeof(bool))
#define BARYON_L2_SIZE \
  (BARYON_NUM_L2_PLATS * sizeof(bool))
#define BARYON_LGL_SIZE \
  (BARYON_NUM_LGL_PLATS * sizeof(bool))

typedef enum {
  BARYON_RSP_MODE_IDLE,
  BARYON_RSP_MODE_RSP16_READ,   // invalid APUC RSP operation
  BARYON_RSP_MODE_RSP256_READ,  // invalid APUC RSP operation
  BARYON_RSP_MODE_RSP2K_READ,
  BARYON_RSP_MODE_RSP32K_READ,
  BARYON_RSP_MODE_RSP16_WRITE,
  BARYON_RSP_MODE_RSP256_WRITE,
  BARYON_RSP_MODE_RSP2K_WRITE,
  BARYON_RSP_MODE_RSP32K_WRITE,
  BARYON_NUM_RSP_MODES
} baryon_rsp_mode_t;

extern const char *baryon_rsp_mode_name[9];

typedef struct baryon_apuc_t {
  baryon_rsp32k_fifo_t *rsp32k_fifo;
  baryon_rsp2k_fifo_t *rsp2k_fifo;
  baryon_rsp_mode_t rsp_mode;

  baryon_vr_t vrs[BARYON_NUM_SBS];
  baryon_rl_t rl;
  baryon_gl_t gl;
  baryon_ggl_t ggl;
  baryon_rsp16_t rsp16;
  baryon_rsp256_t rsp256;
  baryon_rsp2k_t rsp2k;
  baryon_rsp32k_t rsp32k;
  baryon_l1_t l1[BARYON_NUM_L1_ROWS];
  baryon_l2_t l2[BARYON_NUM_L2_ROWS];
  baryon_lgl_t lgl;

  bool in_place;

  baryon_vr_t rwinh_filter;
  uint16_t rwinh_sects;
} baryon_apuc_t;

typedef struct baryon_vr_patch_t {
  baryon_vr_t *vr;
  baryon_vr_t *update;
} baryon_vr_patch_t;

typedef struct baryon_wordline_patch_t {
  baryon_vr_t *vr;
  size_t section;
  baryon_wordline_t *update;
} baryon_wordline_patch_t;

typedef struct baryon_wordline_map_t {
  size_t size;
  baryon_wordline_patch_t updates[];
} baryon_wordline_map_t;

typedef enum {
  BARYON_L1_SRC_GGL,
  BARYON_L1_SRC_LGL,
  BARYON_NUM_L1_SRCS
} baryon_l1_patch_src_t;

extern const char *baryon_l1_patch_src_name[2];

typedef struct baryon_l1_patch_t {
  baryon_l1_patch_src_t src;
  size_t l1_addr;
  union {
    baryon_ggl_t *ggl_patch;
    baryon_lgl_t *lgl_patch;
  };
} baryon_l1_patch_t;

typedef struct baryon_l2_patch_t {
  size_t l2_addr;
  baryon_l2_t *update;
} baryon_l2_patch_t;

typedef struct baryon_rsp16_section_patch_t {
  size_t section;
  baryon_rsp16_section_t update;
} baryon_rsp16_section_patch_t;

typedef struct baryon_rsp16_section_map_t {
  size_t size;
  baryon_rsp16_section_patch_t updates[];
} baryon_rsp16_section_map_t;

typedef struct baryon_rsp_patches_t {
  baryon_rsp16_t *rsp16_update;
  baryon_rsp256_t *rsp256_update;
  baryon_rsp2k_t *rsp2k_update;
  baryon_rsp32k_t *rsp32k_update;
} baryon_rsp_patches_t;

typedef struct baryon_rwinh_rst_patch_t {
  baryon_sm_t mask;
  bool has_read;
} baryon_rwinh_rst_patch_t;

typedef enum {
  BARYON_SRC_RL,
  BARYON_SRC_NRL,
  BARYON_SRC_ERL,
  BARYON_SRC_WRL,
  BARYON_SRC_SRL,

  BARYON_SRC_GL,
  BARYON_SRC_GGL,
  BARYON_SRC_RSP16,

  BARYON_SRC_INV_RL,
  BARYON_SRC_INV_NRL,
  BARYON_SRC_INV_ERL,
  BARYON_SRC_INV_WRL,
  BARYON_SRC_INV_SRL,

  BARYON_SRC_INV_GL,
  BARYON_SRC_INV_GGL,
  BARYON_SRC_INV_RSP16,

  BARYON_NUM_SRCS
} baryon_src_t;

extern const char *baryon_src_name[16];

typedef baryon_wordline_t *(*baryon_unary_op_t)(baryon_wordline_t *nth1);
typedef baryon_wordline_t *(*baryon_binary_op_t)(baryon_wordline_t *nth1,
                                                 baryon_wordline_t *nth2);
typedef baryon_wordline_t *(*baryon_ternary_op_t)(baryon_wordline_t *nth1,
                                                  baryon_wordline_t *nth2,
                                                  baryon_wordline_t *nth3);

void baryon_plats_for_bank(size_t bank,
                           size_t *lower_plat_apc_0,
                           size_t *upper_plat_apc_0,
                           size_t *lower_plat_apc_1,
                           size_t *upper_plat_apc_1);

void baryon_patch_whole_vr(baryon_apuc_t *apuc, baryon_vr_patch_t *patch);
void baryon_patch_sb(baryon_apuc_t *apuc, baryon_wordline_map_t *patch);
void baryon_patch_gl(baryon_apuc_t *apuc, baryon_gl_t *patch);
void baryon_patch_ggl(baryon_apuc_t *apuc, baryon_ggl_t *patch);
void baryon_patch_lgl(baryon_apuc_t *apuc, baryon_lgl_t *patch);
void baryon_patch_whole_l1(baryon_apuc_t *apuc,
                           baryon_l1_t (*patch)[BARYON_NUM_L1_ROWS]);
void baryon_patch_l1(baryon_apuc_t *apuc, baryon_l1_patch_t *patch);
void baryon_patch_whole_l2(baryon_apuc_t *apuc,
                           baryon_l2_t (*patch)[BARYON_NUM_L2_ROWS]);
void baryon_patch_l2(baryon_apuc_t *apuc, baryon_l2_patch_t *patch);
void baryon_patch_rsp16(baryon_apuc_t *apuc, baryon_rsp16_t *patch);
void baryon_patch_partial_rsp16(baryon_apuc_t *apuc,
                                baryon_rsp16_section_map_t *patch);
void baryon_patch_rsp256(baryon_apuc_t *apuc, baryon_rsp256_t *patch);
void baryon_patch_rsp2k(baryon_apuc_t *apuc, baryon_rsp2k_t *patch);
void baryon_patch_rsp32k(baryon_apuc_t *apuc, baryon_rsp32k_t *patch);
void baryon_patch_rsps(baryon_apuc_t *apuc, baryon_rsp_patches_t *patches);
void baryon_patch_noop(baryon_apuc_t *apuc, void *patch);
void baryon_patch_rsp_end(baryon_apuc_t *apuc, void *patch);
void baryon_patch_rsp_start_ret(baryon_apuc_t *apuc, void *patch);
void baryon_patch_l2_end(baryon_apuc_t *apuc, void *patch);
void baryon_patch_rwinh_set(baryon_apuc_t *apuc, baryon_sm_t mask);
void baryon_patch_rwinh_rst(baryon_apuc_t *apuc,
                            baryon_rwinh_rst_patch_t *patch);

void baryon_init_vrs(baryon_vr_t (*vrs)[BARYON_NUM_SBS], bool value);
void baryon_init_vr(baryon_vr_t *vr, bool value);
void baryon_init_gl(baryon_gl_t *gl, bool value);
void baryon_init_ggl(baryon_ggl_t *ggl, bool value);
void baryon_init_rsp16(baryon_rsp16_t *rsp16, bool value);
void baryon_init_rsp256(baryon_rsp256_t *rsp256, bool value);
void baryon_init_rsp2k(baryon_rsp2k_t *rsp2k, bool value);
void baryon_init_rsp32k(baryon_rsp32k_t *rsp32k, bool value);
void baryon_init_l1(baryon_l1_t *l1, bool value);
void baryon_init_l2(baryon_l2_t *l2, bool value);
void baryon_init_lgl(baryon_lgl_t *lgl, bool value);

void baryon_init_apuc(baryon_apuc_t *apuc,
                      baryon_rsp32k_fifo_t *rsp32k_fifo,
                      baryon_rsp2k_fifo_t *rsp2k_fifo);

void baryon_free_apuc(baryon_apuc_t *apuc);
void baryon_free_vr(baryon_vr_t *vr);
void baryon_free_rl(baryon_rl_t *rl);
void baryon_free_gl(baryon_gl_t *gl);
void baryon_free_ggl(baryon_ggl_t *ggl);
void baryon_free_rsp16(baryon_rsp16_t *rsp16);
void baryon_free_rsp256(baryon_rsp256_t *rsp256);
void baryon_free_rsp2k(baryon_rsp2k_t *rsp2k);
void baryon_free_rsp32k(baryon_rsp32k_t *rsp32k);
void baryon_free_l1(baryon_l1_t *l1);
void baryon_free_l2(baryon_l2_t *l2);
void baryon_free_lgl(baryon_lgl_t *lgl);
void baryon_free_wordline(baryon_wordline_t *wordline);
void baryon_free_rsp16_section(baryon_rsp16_section_t *rsp16_section);
void baryon_free_vr_patch(baryon_vr_patch_t *patch);
void baryon_free_wordline_patch(baryon_wordline_patch_t *patch);
void baryon_free_wordline_map(baryon_wordline_map_t *patch);
void baryon_free_l1_patch(baryon_l1_patch_t *patch);
void baryon_free_l2_patch(baryon_l2_patch_t *patch);
void baryon_free_rsp16_section_patch(baryon_rsp16_section_patch_t *patch);
void baryon_free_rsp16_section_map(baryon_rsp16_section_map_t *patch);
void baryon_free_rsp_patches(baryon_rsp_patches_t *patch);
void baryon_free_rwinh_rst_patch(baryon_rwinh_rst_patch_t *patch);

void baryon_free_src(void *src, baryon_src_t src_type);

void baryon_reset_rl_in_place(baryon_apuc_t *apuc);
baryon_vr_patch_t *baryon_reset_rl(baryon_apuc_t *apuc);

void baryon_reset_gl_in_place(baryon_apuc_t *apuc);
baryon_gl_t *baryon_reset_gl(baryon_apuc_t *apuc);

void baryon_reset_ggl_in_place(baryon_apuc_t *apuc);
baryon_ggl_t *baryon_reset_ggl(baryon_apuc_t *apuc);

void baryon_reset_rsp16_in_place(baryon_apuc_t *apuc);
baryon_rsp16_t *baryon_reset_rsp16(baryon_apuc_t *apuc);

void baryon_reset_rsp256_in_place(baryon_apuc_t *apuc);
baryon_rsp256_t *baryon_reset_rsp256(baryon_apuc_t *apuc);

void baryon_reset_rsp2k_in_place(baryon_apuc_t *apuc);
baryon_rsp2k_t *baryon_reset_rsp2k(baryon_apuc_t *apuc);

void baryon_reset_rsp32k_in_place(baryon_apuc_t *apuc);
baryon_rsp32k_t *baryon_reset_rsp32k(baryon_apuc_t *apuc);

void baryon_reset_l1_in_place(baryon_apuc_t *apuc);
baryon_l1_t (*baryon_reset_l1(baryon_apuc_t *apuc))[BARYON_NUM_L1_ROWS];

void baryon_reset_l2_in_place(baryon_apuc_t *apuc);
baryon_l2_t (*baryon_reset_l2(baryon_apuc_t *apuc))[BARYON_NUM_L2_ROWS];

void baryon_reset_lgl_in_place(baryon_apuc_t *apuc);
baryon_lgl_t *baryon_reset_lgl(baryon_apuc_t *apuc);

/** [APL] RSP16 = RSP256; */
void baryon_rsp16_from_rsp256_in_place(baryon_apuc_t *apuc);
baryon_rsp16_t *baryon_rsp16_from_rsp256(baryon_apuc_t *apuc);

/** [APL] RSP256 = RSP16; */
void baryon_rsp256_from_rsp16_in_place(baryon_apuc_t *apuc);
baryon_rsp256_t *baryon_rsp256_from_rsp16(baryon_apuc_t *apuc);

/** [APL] RSP256 = RSP2K; */
void baryon_rsp256_from_rsp2k_in_place(baryon_apuc_t *apuc);
baryon_rsp256_t *baryon_rsp256_from_rsp2k(baryon_apuc_t *apuc);

/** [APL] RSP2K = RSP256; */
void baryon_rsp2k_from_rsp256_in_place(baryon_apuc_t *apuc);
baryon_rsp2k_t *baryon_rsp2k_from_rsp256(baryon_apuc_t *apuc);

/** [APL] RSP2K = RSP32K; */
void baryon_rsp2k_from_rsp32k_in_place(baryon_apuc_t *apuc);
baryon_rsp2k_t *baryon_rsp2k_from_rsp32k(baryon_apuc_t *apuc);

/** [APL] RSP32K = RSP2K; */
void baryon_rsp32k_from_rsp2k_in_place(baryon_apuc_t *apuc);
baryon_rsp32k_t *baryon_rsp32k_from_rsp2k(baryon_apuc_t *apuc);

/** [APL] NOOP; */
void baryon_noop_in_place(baryon_apuc_t *apuc);
void *baryon_noop(baryon_apuc_t *apuc);

/** [APL] FSEL_NOOP; */
void baryon_fsel_noop_in_place(baryon_apuc_t *apuc);
void *baryon_fsel_noop(baryon_apuc_t *apuc);

/** [APL] RSP_END; */
void baryon_rsp_end_in_place(baryon_apuc_t *apuc);
baryon_rsp_patches_t *baryon_rsp_end(baryon_apuc_t *apuc);

/** [APL] RSP_START_RET; */
void baryon_rsp_start_ret_in_place(baryon_apuc_t *apuc);
void *baryon_rsp_start_ret(baryon_apuc_t *apuc);

/** [APL] L2_END; */
void baryon_l2_end_in_place(baryon_apuc_t *apuc);
void *baryon_l2_end(baryon_apuc_t *apuc);

baryon_rl_t *baryon_rl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_nrl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_erl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_wrl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_srl(baryon_apuc_t *apuc);

baryon_rl_t *baryon_inv_rl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_inv_nrl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_inv_erl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_inv_wrl(baryon_apuc_t *apuc);
baryon_rl_t *baryon_inv_srl(baryon_apuc_t *apuc);

baryon_gl_t *baryon_gl(baryon_apuc_t *apuc);
baryon_gl_t *baryon_inv_gl(baryon_apuc_t *apuc);

baryon_ggl_t *baryon_ggl(baryon_apuc_t *apuc);
baryon_ggl_t *baryon_inv_ggl(baryon_apuc_t *apuc);

baryon_rsp16_t *baryon_rsp16(baryon_apuc_t *apuc);
baryon_rsp16_t *baryon_inv_rsp16(baryon_apuc_t *apuc);

void *baryon_src(baryon_apuc_t *apuc, baryon_src_t src_type);

baryon_gl_t *baryon_ternary_expr(baryon_apuc_t *apuc,
                                 baryon_gl_t *nth1,
                                 baryon_gl_t *nth2,
                                 baryon_gl_t *nth3,
                                 baryon_ternary_op_t op1,
                                 baryon_binary_op_t op2);

size_t baryon_count_masked_sections(baryon_sm_t mask);

baryon_brsp16_t *baryon_brsp16(baryon_rsp16_t *rsp16);

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

void baryon_sb_op_eq_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_vr_t *vrs[], size_t num_vrs,
                                 baryon_binary_op_t op, baryon_gl_t *gl);

baryon_wordline_map_t *baryon_sb_op_eq_gl(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs,
                                          baryon_binary_op_t op,
                                          baryon_gl_t *gl);

void baryon_sb_op_eq_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                  baryon_vr_t *vrs[], size_t num_vrs,
                                  baryon_binary_op_t op, baryon_ggl_t *ggl);

baryon_wordline_map_t *baryon_sb_op_eq_ggl(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs,
                                           baryon_binary_op_t op,
                                           baryon_ggl_t *ggl);

void baryon_sb_op_eq_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_vr_t *vrs[], size_t num_vrs,
                                 baryon_binary_op_t op, baryon_rl_t *rl);

baryon_wordline_map_t *baryon_sb_op_eq_rl(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs,
                                          baryon_binary_op_t op,
                                          baryon_rl_t *rl);

void baryon_sb_op_eq_rsp16_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                    baryon_vr_t *vrs[], size_t num_vrs,
                                    baryon_binary_op_t op,
                                    baryon_rsp16_t *rsp16);

baryon_wordline_map_t *baryon_sb_op_eq_rsp16(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_vr_t *vrs[],
                                             size_t num_vrs,
                                             baryon_binary_op_t op,
                                             baryon_rsp16_t *rsp16);

baryon_wordline_map_t *baryon_sb_op_eq_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs,
                                           baryon_binary_op_t op,
                                           void *src,
                                           baryon_src_t src_type);

/**
 * [APL] msk: <SB> = <SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
baryon_wordline_map_t *baryon_sb_from_src(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs,
                                          void *src,
                                          baryon_src_t src_type);

/**
 * [APL] msk: <SB> = ~<SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
baryon_wordline_map_t *baryon_sb_from_inv_src(baryon_apuc_t *apuc,
                                              baryon_sm_t mask,
                                              baryon_vr_t *vrs[],
                                              size_t num_vrs,
                                              void *src,
                                              baryon_src_t src_type);

/**
 * [APL] msk: <SB> ?= <SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
baryon_wordline_map_t *baryon_sb_cond_eq_src(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_vr_t *vrs[],
                                             size_t num_vrs,
                                             void *src,
                                             baryon_src_t src_type);

/**
 * [APL] msk: <SB> ?= ~<SRC>;
 * <SRC> can be [INV_][NEWS]RL, [INV_]GL, [INV_]GGL, or [INV_]RSP16."""
 */
baryon_wordline_map_t *baryon_sb_cond_eq_inv_src(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask,
                                                 baryon_vr_t *vrs[],
                                                 size_t num_vrs,
                                                 void *src,
                                                 baryon_src_t src_type);

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
void baryon_set_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask, bool bit);
baryon_wordline_map_t *baryon_set_rl(baryon_apuc_t *apuc, baryon_sm_t mask,
                                     bool bit);

//    __ __    __               ___           ____     ___  ___
//   / // /__ / /__  ___ ____  / _/__  ____  |_  /    |_  |/ _ \
//  / _  / -_) / _ \/ -_) __/ / _/ _ \/ __/ _/_ <_ _ / __// // /
// /_//_/\__/_/ .__/\__/_/   /_/ \___/_/   /____(_|_)____/\___/
//           /_/

// Helper for Instructions 3 through 20

baryon_wordline_t *baryon_conjoin_sections_in_place(baryon_vr_t *vrs[],
                                                    size_t num_vrs,
                                                    size_t section,
                                                    baryon_wordline_t *conj);

baryon_wordline_t *baryon_conjoin_sections(baryon_vr_t *vrs[],
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

void baryon_rl_op_eq_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_binary_op_t op, baryon_gl_t *gl);
baryon_wordline_map_t *baryon_rl_op_eq_gl(baryon_apuc_t *apuc, baryon_sm_t mask,
                                          baryon_binary_op_t op,
                                          baryon_gl_t *gl);

void baryon_rl_op_eq_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                  baryon_binary_op_t op, baryon_ggl_t *ggl);
baryon_wordline_map_t *baryon_rl_op_eq_ggl(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_binary_op_t op,
                                           baryon_ggl_t *ggl);

void baryon_rl_op_eq_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_binary_op_t op, baryon_rl_t *rl);
baryon_wordline_map_t *baryon_rl_op_eq_rl(baryon_apuc_t *apuc, baryon_sm_t mask,
                                          baryon_binary_op_t op,
                                          baryon_rl_t *rl);

void baryon_rl_op_eq_rsp16_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                    baryon_binary_op_t op,
                                    baryon_rsp16_t *rsp16);
baryon_wordline_map_t *baryon_rl_op_eq_rsp16(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_binary_op_t op,
                                             baryon_rsp16_t *rsp16);

baryon_wordline_map_t *baryon_rl_op_eq_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_binary_op_t op,
                                           void *src,
                                           baryon_src_t src_type);

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
baryon_wordline_map_t *baryon_rl_from_src(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          void *src,
                                          baryon_src_t src_type);

/**
 * Read-logic Instruction 4
 * [APL  4] msk: RL = ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
baryon_wordline_map_t *baryon_rl_from_inv_src(baryon_apuc_t *apuc,
                                              baryon_sm_t mask,
                                              void *src,
                                              baryon_src_t src_type);

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
baryon_wordline_map_t *baryon_rl_or_eq_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           void *src,
                                           baryon_src_t src_type);

/**
 * Read-logic Instruction 11
 * [APL 11] msk: RL |= ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
baryon_wordline_map_t *baryon_rl_or_eq_inv_src(baryon_apuc_t *apuc,
                                               baryon_sm_t mask,
                                               void *src,
                                               baryon_src_t src_type);

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
baryon_wordline_map_t *baryon_rl_and_eq_src(baryon_apuc_t *apuc,
                                            baryon_sm_t mask,
                                            void *src,
                                            baryon_src_t src_type);

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
baryon_wordline_map_t *baryon_rl_and_eq_inv_src(baryon_apuc_t *apuc,
                                                baryon_sm_t mask,
                                                void *src,
                                                baryon_src_t src_type);

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
baryon_wordline_map_t *baryon_rl_xor_eq_src(baryon_apuc_t *apuc,
                                            baryon_sm_t mask,
                                            void *src,
                                            baryon_src_t src_type);

/**
 * Read-logic Instruction 19
 * [APL 19] msk: RL ^= ~<SRC>;
 * <SRC> is one of (INV_)?[GL, GGL, RSP16, RL [NEWS]RL]
 * NOTA BENE: <SRC> does NOT include SB!
 */
baryon_wordline_map_t *baryon_rl_xor_eq_inv_src(baryon_apuc_t *apuc,
                                                baryon_sm_t mask,
                                                void *src,
                                                baryon_src_t src_type);

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

void baryon_rl_op_eq_sb_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_binary_op_t op, baryon_vr_t *vrs[],
                                 size_t num_vrs);
baryon_wordline_map_t *baryon_rl_op_eq_sb(baryon_apuc_t *apuc, baryon_sm_t mask,
                                          baryon_binary_op_t op,
                                          baryon_vr_t *vrs[], size_t num_vrs);

//    ____
//   |_  /
//  _/_ <
// /____/

/**
 * Read-logic Instruction 3
 * [APL  3] msk: RL = <SB>
 */
baryon_wordline_map_t *baryon_rl_from_sb(baryon_apuc_t *apuc,
                                         baryon_sm_t mask,
                                         baryon_vr_t *vrs[],
                                         size_t num_vrs);

/**
 * Read-logic Instruction 3
 * [APL  3] msk: RL = ~<SB>
 */
baryon_wordline_map_t *baryon_rl_from_inv_sb(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_vr_t *vrs[],
                                             size_t num_vrs);

//   ______
//  <  / _ \
//  / / // /
// /_/\___/

/**
 * Read-logic Instruction 10
 * [APL 10] msk: RL |= <SB>
 */
baryon_wordline_map_t *baryon_rl_or_eq_sb(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs);

//   _______
//  <  /_  /
//  / //_ <
// /_/____/

/**
 * Read-logic Instruction 13
 * [APL 13] msk: RL &= <SB>
 */
baryon_wordline_map_t *baryon_rl_and_eq_sb(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs);

//   _______
//  <  / __/
//  / / _ \
// /_/\___/

/**
 * Read-logic Instruction 16
 * [APL 16] msk: RL &= ~<SB>
 */
baryon_wordline_map_t *baryon_rl_and_eq_inv_sb(baryon_apuc_t *apuc,
                                               baryon_sm_t mask,
                                               baryon_vr_t *vrs[],
                                               size_t num_vrs);

//   ______
//  <  ( _ )
//  / / _  |
// /_/\___/

/**
 * Read-logic Instruction 18
 * [APL 18] msk: RL ^= <SB>
 */
baryon_wordline_map_t *baryon_rl_xor_eq_sb(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
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

void baryon_rl_op_eq_sb_and_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                        baryon_ternary_op_t op1,
                                        baryon_binary_op_t op2,
                                        baryon_vr_t *vrs[], size_t num_vrs,
                                        baryon_gl_t *gl);
baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_gl(baryon_apuc_t *apuc, baryon_sm_t mask,
                          baryon_ternary_op_t op1, baryon_binary_op_t op2,
                          baryon_vr_t *vrs[], size_t num_vrs, baryon_gl_t *gl);

void baryon_rl_op_eq_sb_and_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                         baryon_ternary_op_t op1,
                                         baryon_binary_op_t op2,
                                         baryon_vr_t *vrs[], size_t num_vrs,
                                         baryon_ggl_t *ggl);
baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_ggl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_ternary_op_t op1, baryon_binary_op_t op2,
                           baryon_vr_t *vrs[], size_t num_vrs,
                           baryon_ggl_t *ggl);

void baryon_rl_op_eq_sb_and_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                        baryon_ternary_op_t op1,
                                        baryon_binary_op_t op2,
                                        baryon_vr_t *vrs[], size_t num_vrs,
                                        baryon_rl_t *rl);
baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_rl(baryon_apuc_t *apuc, baryon_sm_t mask,
                          baryon_ternary_op_t op1, baryon_binary_op_t op2,
                          baryon_vr_t *vrs[], size_t num_vrs, baryon_rl_t *rl);

void baryon_rl_op_eq_sb_and_rsp16_in_place(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_ternary_op_t op1,
                                           baryon_binary_op_t op2,
                                           baryon_vr_t *vrs[], size_t num_vrs,
                                           baryon_rsp16_t *rsp16);
baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_rsp16(baryon_apuc_t *apuc, baryon_sm_t mask,
                             baryon_ternary_op_t op1, baryon_binary_op_t op2,
                             baryon_vr_t *vrs[], size_t num_vrs,
                             baryon_rsp16_t *rsp16);

/**
 * Abstract instructions 5, 12, 15, 20.
 */
baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_ternary_op_t op1, baryon_binary_op_t op2,
                           baryon_vr_t *vrs[], size_t num_vrs, void *src,
                           baryon_src_t src_type);

//    ____
//   / __/
//  /__ \
// /____/

/**
 * Read-logic Instruction 5
 * [APL  5] msk: RL = <SB> & <SRC>
 */
baryon_wordline_map_t *baryon_rl_from_sb_and_src(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask,
                                                 baryon_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 baryon_src_t src_type);

//   ______
//  <  /_  |
//  / / __/
// /_/____/

baryon_wordline_map_t *baryon_rl_or_eq_sb_and_src(baryon_apuc_t *apuc,
                                                  baryon_sm_t mask,
                                                  baryon_vr_t *vrs[],
                                                  size_t num_vrs, void *src,
                                                  baryon_src_t src_type);

baryon_wordline_map_t *baryon_rl_or_eq_sb_and_inv_src(baryon_apuc_t *apuc,
                                                      baryon_sm_t mask,
                                                      baryon_vr_t *vrs[],
                                                      size_t num_vrs, void *src,
                                                      baryon_src_t src_type);

//   _______
//  <  / __/
//  / /__ \
// /_/____/

baryon_wordline_map_t *baryon_rl_and_eq_sb_and_src(baryon_apuc_t *apuc,
                                                   baryon_sm_t mask,
                                                   baryon_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   baryon_src_t src_type);

baryon_wordline_map_t *
baryon_rl_and_eq_sb_and_inv_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                                baryon_vr_t *vrs[], size_t num_vrs, void *src,
                                baryon_src_t src_type);

//    ___  ___
//   |_  |/ _ \
//  / __// // /
// /____/\___/

baryon_wordline_map_t *baryon_rl_xor_eq_sb_and_src(baryon_apuc_t *apuc,
                                                   baryon_sm_t mask,
                                                   baryon_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   baryon_src_t src_type);

baryon_wordline_map_t *
baryon_rl_xor_eq_sb_and_inv_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                                baryon_vr_t *vrs[], size_t num_vrs, void *src,
                                baryon_src_t src_type);

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

void baryon_rl_from_sb_binop_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                         baryon_vr_t *vrs[], size_t num_vrs,
                                         baryon_binary_op_t op,
                                         baryon_gl_t *gl);
baryon_wordline_map_t *
baryon_rl_from_sb_binop_gl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_vr_t *vrs[], size_t num_vrs,
                           baryon_binary_op_t op, baryon_gl_t *gl);

void baryon_rl_from_sb_binop_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                          baryon_vr_t *vrs[], size_t num_vrs,
                                          baryon_binary_op_t op,
                                          baryon_ggl_t *ggl);
baryon_wordline_map_t *
baryon_rl_from_sb_binop_ggl(baryon_apuc_t *apuc, baryon_sm_t mask,
                            baryon_vr_t *vrs[], size_t num_vrs,
                            baryon_binary_op_t op, baryon_ggl_t *ggl);

void baryon_rl_from_sb_binop_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                         baryon_vr_t *vrs[], size_t num_vrs,
                                         baryon_binary_op_t op,
                                         baryon_rl_t *rl);
baryon_wordline_map_t *
baryon_rl_from_sb_binop_rl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_vr_t *vrs[], size_t num_vrs,
                           baryon_binary_op_t op, baryon_rl_t *rl);

void baryon_rl_from_sb_binop_rsp16_in_place(baryon_apuc_t *apuc,
                                            baryon_sm_t mask,
                                            baryon_vr_t *vrs[], size_t num_vrs,
                                            baryon_binary_op_t op,
                                            baryon_rsp16_t *rsp16);
baryon_wordline_map_t *
baryon_rl_from_sb_binop_rsp16(baryon_apuc_t *apuc, baryon_sm_t mask,
                              baryon_vr_t *vrs[], size_t num_vrs,
                              baryon_binary_op_t op, baryon_rsp16_t *rsp16);

baryon_wordline_map_t *baryon_rl_from_sb_binop_src(
    baryon_apuc_t *apuc, baryon_sm_t mask, baryon_vr_t *vrs[], size_t num_vrs,
    baryon_binary_op_t op, void *src, baryon_src_t src_type);

//   ____
//  / __/
// / _ \
// \___/

/**
 * Read-logic Instruction 6
 * [APL  6] msk: RL = <SB> | <SRC>
 */
baryon_wordline_map_t *
baryon_rl_from_sb_or_src(baryon_apuc_t *apuc, baryon_sm_t mask, baryon_vr_t *vrs[],
                         size_t num_vrs, void *src, baryon_src_t src_type);

/**
 * Read-logic Instruction 6
 * [APL  6] msk: RL = <SB> | ~<SRC>
 */
baryon_wordline_map_t *baryon_rl_from_sb_or_inv_src(baryon_apuc_t *apuc,
                                                    baryon_sm_t mask,
                                                    baryon_vr_t *vrs[],
                                                    size_t num_vrs, void *src,
                                                    baryon_src_t src_type);

//  ____
// /_  /
//  / /
// /_/

/**
 * Read-logic Instruction 7
 * [APL  7] msk: RL = <SB> ^ <SRC>
 */
baryon_wordline_map_t *baryon_rl_from_sb_xor_src(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask,
                                                 baryon_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 baryon_src_t src_type);

/**
 * Read-logic Instruction 7
 * [APL  7] msk: RL = <SB> ^ ~<SRC>
 */
baryon_wordline_map_t *baryon_rl_from_sb_xor_inv_src(baryon_apuc_t *apuc,
                                                     baryon_sm_t mask,
                                                     baryon_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     baryon_src_t src_type);

//   ___
//  ( _ )
// / _  |
// \___/

/**
 * Read-logic Instruction 8
 * [APL 8] msk: RL = ~<SB> & <SRC>
 */
baryon_wordline_map_t *baryon_rl_from_inv_sb_and_src(baryon_apuc_t *apuc,
                                                     baryon_sm_t mask,
                                                     baryon_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     baryon_src_t src_type);

/**
 * Read-logic Instruction 8
 * [APL 8] msk: RL = ~<SB> & ~<SRC>
 */
baryon_wordline_map_t *
baryon_rl_from_inv_sb_and_inv_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                                  baryon_vr_t *vrs[], size_t num_vrs, void *src,
                                  baryon_src_t src_type);

//   ___
//  / _ \
//  \_, /
// /___/

/**
 * Read-logic Instruction 9
 * [APL 9] msk: RL = <SB> & ~<SRC>
 */
baryon_wordline_map_t *baryon_rl_from_sb_and_inv_src(baryon_apuc_t *apuc,
                                                     baryon_sm_t mask,
                                                     baryon_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     baryon_src_t src_type);

//  ___     ___      _   _              _
// | _ \___/ __| ___| | | |   ___  __ _(_)__
// |   /___\__ \/ -_) | | |__/ _ \/ _` | / _|
// |_|_\   |___/\___|_| |____\___/\__, |_\__|
//                                |___/

/**
 * [APL] msk: RSP16 = RL;
 */
void baryon_rsp16_from_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask);
baryon_rsp16_section_map_t *baryon_rsp16_from_rl(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask);

/**
 * [APL] msk: GL = RL;
 */
void baryon_gl_from_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask);
baryon_gl_t *baryon_gl_from_rl(baryon_apuc_t *apuc, baryon_sm_t mask);

/**
 * [APL] msk: GGL = RL;
 */
void baryon_ggl_from_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask);
baryon_ggl_t *baryon_ggl_from_rl(baryon_apuc_t *apuc, baryon_sm_t mask);

/**
 * [APL] LX = GGL;
 */
void baryon_l1_from_ggl_in_place(baryon_apuc_t *apuc, size_t l1_addr);
baryon_l1_patch_t *baryon_l1_from_ggl(baryon_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] LGL = <LX>;
 */
void baryon_lgl_from_l1_in_place(baryon_apuc_t *apuc, size_t l1_addr);
baryon_lgl_t *baryon_lgl_from_l1(baryon_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] LX = LGL;
 */
void baryon_l2_from_lgl_in_place(baryon_apuc_t *apuc, size_t l2_addr);
baryon_l2_patch_t *baryon_l2_from_lgl(baryon_apuc_t *apuc, size_t l2_addr);

/**
 * [APL] LGL = <LX>;
 */
void baryon_lgl_from_l2_in_place(baryon_apuc_t *apuc, size_t l2_addr);
baryon_lgl_t *baryon_lgl_from_l2(baryon_apuc_t *apuc, size_t l2_addr);

/**
 * [APL] LX = LGL;
 */
void baryon_l1_from_lgl_in_place(baryon_apuc_t *apuc, size_t l1_addr);
baryon_l1_patch_t *baryon_l1_from_lgl(baryon_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] GGL = <LX>;
 */
void baryon_ggl_from_l1_in_place(baryon_apuc_t *apuc, size_t l1_addr);
baryon_ggl_t *baryon_ggl_from_l1(baryon_apuc_t *apuc, size_t l1_addr);

/**
 * [APL] msk: GGL = RL & <LX>;
 */
void baryon_ggl_from_rl_and_l1_in_place(baryon_apuc_t *apuc, size_t mask,
                                        size_t l1_addr);
baryon_ggl_t *baryon_ggl_from_rl_and_l1(baryon_apuc_t *apuc, size_t mask,
                                        size_t l1_addr);

//  ___             _   ____      __   _ _          ___      _    _ _    _ _
// | _ \___ __ _ __| | / /\ \    / / _(_) |_ ___ __|_ _|_ _ | |_ (_) |__(_) |_
// |   / -_) _` / _` |/ /  \ \/\/ / '_| |  _/ -_)___| || ' \| ' \| | '_ \ |  _|
// |_|_\___\__,_\__,_/_/    \_/\_/|_| |_|\__\___|  |___|_||_|_||_|_|_.__/_|\__|

/**
 * [APL] msk: RL = <SB> RWINH_SET;
 */
void baryon_rwinh_set_in_place(baryon_apuc_t *apuc, size_t mask);
size_t baryon_rwinh_set(baryon_apuc_t *apuc, size_t mask);

/**
 * [APL] msk: RL = <SB> RWINH_RST;
 */
void baryon_rwinh_rst_in_place(baryon_apuc_t *apuc, size_t mask, bool has_read);
baryon_rwinh_rst_patch_t *baryon_rwinh_rst(baryon_apuc_t *apuc, size_t mask,
                                           bool has_read);

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__APUC_H__
