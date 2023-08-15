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

#include <stdio.h>
#include <string.h>

#include <log.h>

#include "apuc.h"
#include "constants.h"
#include "fifo.h"
#include "operations.h"

const char *baryon_status_names[BARYON_NUM_STATUSES + 1] = {
  "BARYON_STATUS_SUCCESS",
  "BARYON_STATUS_ERROR",
  "BARYON_STATUS_UNSUPPORTED",
  "BARYON_NUM_STATUSES"
};

const char *baryon_rsp_mode_names[BARYON_NUM_RSP_MODES + 1] = {
  "BARYON_RSP_MODE_IDLE",
  "BARYON_RSP_MODE_RSP16_READ",
  "BARYON_RSP_MODE_RSP256_READ",
  "BARYON_RSP_MODE_RSP2K_READ",
  "BARYON_RSP_MODE_RSP32K_READ",
  "BARYON_RSP_MODE_RSP16_WRITE",
  "BARYON_RSP_MODE_RSP256_WRITE",
  "BARYON_RSP_MODE_RSP2K_WRITE",
  "BARYON_RSP_MODE_RSP32K_WRITE",
  "BARYON_NUM_RSP_MODES"
};

const char *baryon_l1_patch_src_names[BARYON_NUM_L1_SRCS + 1] = {
  "BARYON_L1_SRC_GGL",
  "BARYON_L1_SRC_LGL",
  "BARYON_NUM_L1_SRCS"
};

const char *baryon_src_names[BARYON_NUM_SRCS + 1] = {
  "BARYON_SRC_RL",
  "BARYON_SRC_NRL",
  "BARYON_SRC_ERL",
  "BARYON_SRC_WRL",
  "BARYON_SRC_SRL",

  "BARYON_SRC_GL",
  "BARYON_SRC_GGL",
  "BARYON_SRC_RSP16",

  "BARYON_SRC_INV_RL",
  "BARYON_SRC_INV_NRL",
  "BARYON_SRC_INV_ERL",
  "BARYON_SRC_INV_WRL",
  "BARYON_SRC_INV_SRL",

  "BARYON_SRC_INV_GL",
  "BARYON_SRC_INV_GGL",
  "BARYON_SRC_INV_RSP16",

  "BARYON_NUM_SRCS"
};

const char *baryon_glassible_names[BARYON_NUM_GLASSIBLES + 1] = {
    "BARYON_GLASSIBLE_RN",
    "BARYON_GLASSIBLE_SM",
    "BARYON_GLASSIBLE_EWE",
    "BARYON_GLASSIBLE_RE",

    "BARYON_GLASSIBLE_L1",
    "BARYON_GLASSIBLE_L2",
    "BARYON_GLASSIBLE_LGL",

    "BARYON_GLASSIBLE_RL",
    "BARYON_GLASSIBLE_NRL",
    "BARYON_GLASSIBLE_ERL",
    "BARYON_GLASSIBLE_WRL",
    "BARYON_GLASSIBLE_SRL",
    "BARYON_GLASSIBLE_GL",
    "BARYON_GLASSIBLE_GGL",
    "BARYON_GLASSIBLE_RSP16",

    "BARYON_GLASSIBLE_INV_RL",
    "BARYON_GLASSIBLE_INV_NRL",
    "BARYON_GLASSIBLE_INV_ERL",
    "BARYON_GLASSIBLE_INV_WRL",
    "BARYON_GLASSIBLE_INV_SRL",
    "BARYON_GLASSIBLE_INV_GL",
    "BARYON_GLASSIBLE_INV_GGL",
    "BARYON_GLASSIBLE_INV_RSP16",

    "BARYON_GLASSIBLE_RSP256",
    "BARYON_GLASSIBLE_RSP2K",
    "BARYON_GLASSIBLE_RSP32K",

    "BARYON_NUM_GLASSIBLES"
};

const char *baryon_glass_fmt_names[BARYON_NUM_GLASS_FMTS + 1] = {
    "BARYON_GLASS_FMT_HEX",
    "BARYON_GLASS_FMT_BIN",
    "BARYON_NUM_GLASS_FMTS"
};

const char *baryon_glass_order_names[BARYON_NUM_GLASS_ORDERS + 1] = {
  "BARYON_GLASS_ORDER_LSB",
  "BARYON_GLASS_ORDER_MSB",
  "BARYON_NUM_GLASS_ORDERS"
};

void baryon_plats_for_bank(size_t bank, size_t *apc_0_lo, size_t *apc_0_hi,
                           size_t *apc_1_lo, size_t *apc_1_hi) {
  *apc_0_lo = bank * BARYON_NUM_PLATS_PER_HALF_BANK;
  *apc_0_hi = (*apc_0_lo) + 4 * BARYON_NUM_PLATS_PER_HALF_BANK;
  *apc_1_lo = (*apc_0_lo) + BARYON_NUM_PLATS_PER_APC;
  *apc_1_hi = (*apc_0_hi) + BARYON_NUM_PLATS_PER_APC;
}

void baryon_patch_whole_vr(baryon_apuc_t *apuc, baryon_vr_patch_t *patch) {
  baryon_vr_t *vr = patch->vr;
  baryon_vr_t *update = patch->update;
  if (update == NULL) {
    baryon_init_vr(vr, false);
  }
  else {
    memcpy(vr, update, BARYON_VR_SIZE);
  }
}

void baryon_patch_sb(baryon_apuc_t *apuc, baryon_wordline_map_t *patch) {
  baryon_foreach_range(i, patch->size, {
    baryon_wordline_patch_t *section_patch = &patch->updates[i];
    baryon_vr_t *vr = section_patch->vr;
    size_t section = section_patch->section;
    baryon_wordline_t *update = section_patch->update;
    memcpy(&(*vr)[section], update, BARYON_WORDLINE_SIZE);
  });
}

void baryon_patch_gl(baryon_apuc_t *apuc, baryon_gl_t *patch) {
  if (patch != NULL) {
    memcpy(&apuc->gl, patch, BARYON_GL_SIZE);
  }
  else {
    baryon_init_gl(&apuc->gl, false);
  }
}

void baryon_patch_ggl(baryon_apuc_t *apuc, baryon_ggl_t *patch) {
  if (patch != NULL) {
    memcpy(&apuc->ggl, patch, BARYON_GGL_SIZE);
  }
  else {
    baryon_init_ggl(&apuc->ggl, false);
  }
}

void baryon_patch_lgl(baryon_apuc_t *apuc, baryon_lgl_t *patch) {
  if (patch != NULL) {
    memcpy(&apuc->lgl, patch, BARYON_LGL_SIZE);
  }
  else {
    baryon_init_lgl(&apuc->lgl, false);
  }
}

void baryon_patch_whole_l1(baryon_apuc_t *apuc,
                           baryon_l1_t (*patch)[BARYON_NUM_L1_ROWS]) {
  if (patch == NULL) {
    memset(&apuc->l1, false, BARYON_NUM_L1_ROWS * BARYON_L1_SIZE);
  }
  else {
    memcpy(&apuc->l1, patch, BARYON_NUM_L1_ROWS * BARYON_L1_SIZE);
  }
}

void baryon_patch_l1(baryon_apuc_t *apuc, baryon_l1_patch_t *patch) {
  size_t l1_addr = patch->l1_addr;
  switch (patch->src) {
  case BARYON_L1_SRC_GGL: {
    memcpy(&apuc->l1[l1_addr], patch->ggl_patch, BARYON_GGL_SIZE);
    break;
  }
  case BARYON_L1_SRC_LGL: {
    size_t bank, group, row;
    baryon_bank_group_row(l1_addr, &bank, &group, &row);
    baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
      apuc->l1[row][group][l1_plat] = (*patch->lgl_patch)[lgl_plat];
    });
    break;
  }
  }
}

void baryon_patch_whole_l2(baryon_apuc_t *apuc,
                           baryon_l2_t (*patch)[BARYON_NUM_L2_ROWS]) {
  if (patch == NULL) {
    memset(&apuc->l2, false, BARYON_NUM_L2_ROWS * BARYON_L2_SIZE);
  }
  else {
    memcpy(&apuc->l2, patch, BARYON_NUM_L2_ROWS * BARYON_L2_SIZE);
  }
}

void baryon_patch_l2(baryon_apuc_t *apuc, baryon_l2_patch_t *patch) {
  size_t l2_addr = patch->l2_addr;
  memcpy(&apuc->l2[l2_addr], patch->update, BARYON_L2_SIZE);
}

void baryon_patch_rsp16(baryon_apuc_t *apuc, baryon_rsp16_t *patch) {
  memcpy(&apuc->rsp16, patch, BARYON_RSP16_SIZE);
}

void baryon_patch_partial_rsp16(baryon_apuc_t *apuc,
                                baryon_rsp16_section_map_t *patch) {
  baryon_foreach_range(i, patch->size, {
    baryon_rsp16_section_patch_t *section_patch = &patch->updates[i];
    size_t section = section_patch->section;
    baryon_rsp16_section_t *update = &section_patch->update;
    memcpy(&apuc->rsp16[section], update, BARYON_RSP16_SECTION_SIZE);
  });
}

void baryon_patch_rsp256(baryon_apuc_t *apuc, baryon_rsp256_t *patch) {
  memcpy(&apuc->rsp256, patch, BARYON_RSP256_SIZE);
}

void baryon_patch_rsp2k(baryon_apuc_t *apuc, baryon_rsp2k_t *patch) {
  memcpy(&apuc->rsp2k, patch, BARYON_RSP2K_SIZE);
}

void baryon_patch_rsp32k(baryon_apuc_t *apuc, baryon_rsp32k_t *patch) {
  memcpy(&apuc->rsp32k, patch, BARYON_RSP32K_SIZE);
}

void baryon_patch_rsps(baryon_apuc_t *apuc, baryon_rsp_patches_t *patches) {
  if (patches != NULL && patches->rsp16_update != NULL) {
    baryon_patch_rsp16(apuc, patches->rsp16_update);
  }
  else {
    baryon_init_rsp16(&apuc->rsp16, false);
  }

  if (patches != NULL && patches->rsp256_update != NULL) {
    baryon_patch_rsp256(apuc, patches->rsp256_update);
  }
  else {
    baryon_init_rsp256(&apuc->rsp256, false);
  }

  if (patches != NULL && patches->rsp2k_update != NULL) {
    baryon_patch_rsp2k(apuc, patches->rsp2k_update);
  }
  else {
    baryon_init_rsp2k(&apuc->rsp2k, false);
  }

  if (patches != NULL && patches->rsp32k_update != NULL) {
    baryon_patch_rsp32k(apuc, patches->rsp32k_update);
  }
  else {
    baryon_init_rsp32k(&apuc->rsp32k, false);
  }
}

void baryon_patch_noop(baryon_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void baryon_patch_rsp_end(baryon_apuc_t *apuc, void *patch) {
  baryon_rsp_end_in_place(apuc);
}

void baryon_patch_rsp_start_ret(baryon_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void baryon_patch_l2_end(baryon_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void baryon_patch_rwinh_set(baryon_apuc_t *apuc, baryon_sm_t mask) {
  baryon_rwinh_set_in_place(apuc, mask);
}

void baryon_patch_rwinh_rst(baryon_apuc_t *apuc,
                            baryon_rwinh_rst_patch_t *patch) {
  baryon_rwinh_rst_in_place(apuc, patch->mask, patch->has_read);
}

void baryon_init_vrs(baryon_vr_t (*vrs)[BARYON_NUM_SBS], bool value) {
  memset(vrs, false, BARYON_NUM_SBS * BARYON_VR_SIZE);
}

void baryon_init_vr(baryon_vr_t *vr, bool value) {
  memset(vr, value, BARYON_VR_SIZE);
}

void baryon_init_gl(baryon_gl_t *gl, bool value) {
  memset(gl, value, BARYON_GL_SIZE);
}

void baryon_init_ggl(baryon_ggl_t *ggl, bool value) {
  memset(ggl, value, BARYON_GGL_SIZE);
}

void baryon_init_rsp16(baryon_rsp16_t *rsp16, bool value) {
  memset(rsp16, value, BARYON_RSP16_SIZE);
}

void baryon_init_rsp256(baryon_rsp256_t *rsp256, bool value) {
  memset(rsp256, value, BARYON_RSP256_SIZE);
}

void baryon_init_rsp2k(baryon_rsp2k_t *rsp2k, bool value) {
  memset(rsp2k, value, BARYON_RSP2K_SIZE);
}

void baryon_init_rsp32k(baryon_rsp32k_t *rsp32k, bool value) {
  memset(rsp32k, value, BARYON_RSP32K_SIZE);
}

void baryon_init_l1(baryon_l1_t *l1, bool value) {
  memset(l1, value, BARYON_L1_SIZE);
}

void baryon_init_l2(baryon_l2_t *l2, bool value) {
  memset(l2, value, BARYON_L2_SIZE);
}

void baryon_init_lgl(baryon_lgl_t *lgl, bool value) {
  memset(lgl, value, BARYON_LGL_SIZE);
}

void baryon_init_apuc(baryon_apuc_t *apuc,
                      baryon_apuc_rsp_fifo_t *apuc_rsp_fifo) {
  apuc->in_place = true;
  apuc->num_instructions = 0;

  apuc->apuc_rsp_fifo = apuc_rsp_fifo;
  apuc->rsp_mode = BARYON_RSP_MODE_IDLE;

  baryon_init_vrs(&apuc->vrs, false);

  baryon_reset_rl(apuc);
  baryon_reset_gl(apuc);
  baryon_reset_ggl(apuc);

  baryon_reset_rsp16(apuc);
  baryon_reset_rsp256(apuc);
  baryon_reset_rsp2k(apuc);
  baryon_reset_rsp32k(apuc);

  baryon_reset_l1(apuc);
  baryon_reset_l2(apuc);
  baryon_reset_lgl(apuc);

  baryon_init_vr(&apuc->rwinh_filter, true);
  apuc->rwinh_sects = 0x0000;
}

void baryon_init_glass_stmt(baryon_glass_stmt_t *glass_stmt) {
  glass_stmt->subject = NULL;
  glass_stmt->subject_type = BARYON_NUM_GLASSIBLES;
  glass_stmt->comment[0] = '\0';
  memset(&glass_stmt->sections, false, BARYON_NUM_SECTIONS * sizeof(bool));
  glass_stmt->num_plats = 0;
  glass_stmt->fmt = BARYON_NUM_GLASS_FMTS;
  glass_stmt->order = BARYON_NUM_GLASS_ORDERS;
  glass_stmt->balloon = true;
  for (int i = 0; i < 16; i += 1) {
    sprintf(&glass_stmt->rewrite[i], "%d", i);
  }
  glass_stmt->file_path[0] = '\0';
  glass_stmt->line_number = -1;
}

void baryon_free_apuc(baryon_apuc_t *apuc) {
  if (apuc != NULL) {
    free(apuc);
  }
}

void baryon_free_glass_stmt(baryon_glass_stmt_t *glass_stmt) {
  if (glass_stmt != NULL) {
    free(glass_stmt);
  }
}

void baryon_free_vr(baryon_vr_t *vr) {
  if (vr != NULL) {
    free(vr);
  }
}

void baryon_free_rl(baryon_rl_t *rl) {
  if (rl != NULL) {
    free(rl);
  }
}

void baryon_free_gl(baryon_gl_t *gl) {
  if (gl != NULL) {
    free(gl);
  }
}

void baryon_free_ggl(baryon_ggl_t *ggl) {
  if (ggl != NULL) {
    free(ggl);
  }
}

void baryon_free_rsp16(baryon_rsp16_t *rsp16) {
  if (rsp16 != NULL) {
    free(rsp16);
  }
}

void baryon_free_rsp256(baryon_rsp256_t *rsp256) {
  if (rsp256 != NULL) {
    free(rsp256);
  }
}

void baryon_free_rsp2k(baryon_rsp2k_t *rsp2k) {
  if (rsp2k != NULL) {
    free(rsp2k);
  }
}

void baryon_free_rsp32k(baryon_rsp32k_t *rsp32k) {
  if (rsp32k != NULL) {
    free(rsp32k);
  }
}

void baryon_free_l1(baryon_l1_t *l1) {
  if (l1 != NULL) {
    free(l1);
  }
}

void baryon_free_l2(baryon_l2_t *l2) {
  if (l2 != NULL) {
    free(l2);
  }
}

void baryon_free_lgl(baryon_lgl_t *lgl) {
  if (lgl != NULL) {
    free(lgl);
  }
}

void baryon_free_wordline(baryon_wordline_t *wordline) {
  if (wordline != NULL) {
    free(wordline);
  }
}

void baryon_free_rsp16_section(baryon_rsp16_section_t *rsp16_section) {
  if (rsp16_section != NULL) {
    free(rsp16_section);
  }
}

void baryon_free_vr_patch(baryon_vr_patch_t *patch) {
  if (patch != NULL) {
    baryon_free_vr(patch->vr);
    baryon_free_vr(patch->update);
    free(patch);
  }
}

void baryon_free_wordline_patch(baryon_wordline_patch_t *patch) {
  if (patch != NULL) {
    // NOTE: Do not free patch->vr because it points to memory in apuc.
    /* baryon_free_vr(patch->vr); */
    baryon_free_wordline(patch->update);
    free(patch);
  }
}

void baryon_free_wordline_map(baryon_wordline_map_t *patches) {
  if (patches != NULL) {
    baryon_foreach_range(i, patches->size, {
      baryon_wordline_patch_t *patch = &patches->updates[i];
      baryon_free_wordline(patch->update);
    });
    free(patches);
  }
}

void baryon_free_l1_patch(baryon_l1_patch_t *patch) {
  if (patch != NULL) {
    switch (patch->src) {
    case BARYON_L1_SRC_GGL:
      baryon_free_ggl(patch->ggl_patch);
      break;
    case BARYON_L1_SRC_LGL:
      baryon_free_lgl(patch->lgl_patch);
      break;
    }
    free(patch);
  }
}

void baryon_free_l2_patch(baryon_l2_patch_t *patch) {
  if (patch != NULL) {
    baryon_free_l2(patch->update);
    free(patch);
  }
}

void baryon_free_rsp16_section_patch(baryon_rsp16_section_patch_t *patch) {
  if (patch != NULL) {
    free(patch);
  }
}

void baryon_free_rsp16_section_map(baryon_rsp16_section_map_t *patch) {
  if (patch != NULL) {
    free(patch);
  }
}

void baryon_free_rsp_patches(baryon_rsp_patches_t *patch) {
  if (patch != NULL) {
    baryon_free_rsp16(patch->rsp16_update);
    baryon_free_rsp256(patch->rsp256_update);
    baryon_free_rsp2k(patch->rsp2k_update);
    baryon_free_rsp32k(patch->rsp32k_update);
    free(patch);
  }
}

void baryon_free_rwinh_rst_patch(baryon_rwinh_rst_patch_t *patch) {
  if (patch != NULL) {
    free(patch);
  }
}

baryon_status_t baryon_glass_rn(baryon_glass_stmt_t *glass_stmt) {
  baryon_vr_t *vr = (baryon_vr_t *)glass_stmt->subject;
  switch (glass_stmt->fmt) {
  case BARYON_GLASS_FMT_HEX:
    switch (glass_stmt->order) {
    case BARYON_GLASS_ORDER_LSB: {
      baryon_foreach_range(nibble_index, 4, {
        size_t lower_section = nibble_index * 4;
        size_t upper_section = lower_section + 4;
        baryon_foreach_range(plat_index, glass_stmt->num_plats, {
          size_t plat = glass_stmt->plats[plat_index];
          size_t nibble = 0x0;
          baryon_foreach_range(section, lower_section, upper_section, {
            nibble |= (*vr)[section][plat] << (section - lower_section);
          });
          printf("%c", glass_stmt->rewrite[nibble]);
          if (plat_index + 1 < glass_stmt->num_plats) {
            printf(" ");
          }
        });
        printf("\n");
      });
      break;
    }
    case BARYON_GLASS_ORDER_MSB: {
      break;
    }
    default:
      log_error("Unsupported baryon_glass_order_t: %s",
                baryon_glass_order_names[glass_stmt->order]);
      return BARYON_STATUS_UNSUPPORTED;
    }
    break;
  case BARYON_GLASS_FMT_BIN:
    switch (glass_stmt->order) {
    case BARYON_GLASS_ORDER_LSB: {
      break;
    }
    case BARYON_GLASS_ORDER_MSB: {
      break;
    }
    default:
      log_error("Unsupported baryon_glass_order_t: %s",
                baryon_glass_order_names[glass_stmt->order]);
      return BARYON_STATUS_UNSUPPORTED;
    }
    break;
  default:
    log_error("Unsupported baryon_glass_fmt_t: %s",
              baryon_glass_fmt_names[glass_stmt->fmt]);
    return BARYON_STATUS_UNSUPPORTED;
  }
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_sm(baryon_glass_stmt_t *glass_stmt) {
  baryon_sm_t sm = *(baryon_sm_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_ewe(baryon_glass_stmt_t *glass_stmt) {
  baryon_ewe_t ewe = *(baryon_ewe_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_re(baryon_glass_stmt_t *glass_stmt) {
  baryon_re_t re = *(baryon_re_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_l1(baryon_glass_stmt_t *glass_stmt) {
  baryon_l1_t *l1 = (baryon_l1_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_l2(baryon_glass_stmt_t *glass_stmt) {
  baryon_l2_t *l2 = (baryon_l2_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_lgl(baryon_glass_stmt_t *glass_stmt) {
  baryon_lgl_t *lgl = (baryon_lgl_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_rl(baryon_glass_stmt_t *glass_stmt) {
  baryon_rl_t *rl = (baryon_rl_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_gl(baryon_glass_stmt_t *glass_stmt) {
  baryon_gl_t *gl = (baryon_gl_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_ggl(baryon_glass_stmt_t *glass_stmt) {
  baryon_ggl_t *ggl = (baryon_ggl_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_rsp16(baryon_glass_stmt_t *glass_stmt) {
  baryon_rsp16_t *rsp16 = (baryon_rsp16_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_rsp256(baryon_glass_stmt_t *glass_stmt) {
  baryon_rsp256_t *rsp256 = (baryon_rsp256_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_rsp2k(baryon_glass_stmt_t *glass_stmt) {
  baryon_rsp2k_t *rsp2k = (baryon_rsp2k_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass_rsp32k(baryon_glass_stmt_t *glass_stmt) {
  baryon_rsp32k_t *rsp32k = (baryon_rsp32k_t *)glass_stmt->subject;
  return BARYON_STATUS_SUCCESS;
}

baryon_status_t baryon_glass(baryon_glass_stmt_t *glass_stmt) {
  switch (glass_stmt->subject_type) {
  case BARYON_GLASSIBLE_RN:
    return baryon_glass_rn(glass_stmt);
  case BARYON_GLASSIBLE_SM:
    return baryon_glass_sm(glass_stmt);
  case BARYON_GLASSIBLE_EWE:
    return baryon_glass_ewe(glass_stmt);
  case BARYON_GLASSIBLE_RE:
    return baryon_glass_re(glass_stmt);
  case BARYON_GLASSIBLE_L1:
    return baryon_glass_l1(glass_stmt);
  case BARYON_GLASSIBLE_L2:
    return baryon_glass_l2(glass_stmt);
  case BARYON_GLASSIBLE_LGL:
    return baryon_glass_lgl(glass_stmt);
  case BARYON_GLASSIBLE_RL:      // fallthrough
  case BARYON_GLASSIBLE_NRL:     // fallthrough
  case BARYON_GLASSIBLE_ERL:     // fallthrough
  case BARYON_GLASSIBLE_WRL:     // fallthrough
  case BARYON_GLASSIBLE_SRL:     // fallthrough
  case BARYON_GLASSIBLE_INV_RL:  // fallthrough
  case BARYON_GLASSIBLE_INV_NRL: // fallthrough
  case BARYON_GLASSIBLE_INV_ERL: // fallthrough
  case BARYON_GLASSIBLE_INV_WRL: // fallthrough
  case BARYON_GLASSIBLE_INV_SRL:
    return baryon_glass_rl(glass_stmt);
  case BARYON_GLASSIBLE_GL: // fallthrough
  case BARYON_GLASSIBLE_INV_GL:
    return baryon_glass_gl(glass_stmt);
  case BARYON_GLASSIBLE_GGL: // fallthrough
  case BARYON_GLASSIBLE_INV_GGL:
    return baryon_glass_ggl(glass_stmt);
  case BARYON_GLASSIBLE_RSP16: // fallthrough
  case BARYON_GLASSIBLE_INV_RSP16:
    return baryon_glass_rsp16(glass_stmt);
  case BARYON_GLASSIBLE_RSP256:
    return baryon_glass_rsp256(glass_stmt);
  case BARYON_GLASSIBLE_RSP2K:
    return baryon_glass_rsp256(glass_stmt);
  case BARYON_GLASSIBLE_RSP32K:
    return baryon_glass_rsp256(glass_stmt);
  default:
    log_error("Unsupported subject_type for baryon_glass: %d\n",
              glass_stmt->subject_type);
    return BARYON_STATUS_UNSUPPORTED;
  }
}

void baryon_reset_rl_in_place(baryon_apuc_t *apuc) {
  baryon_init_vr(&apuc->rl, false);
}

baryon_vr_patch_t *baryon_reset_rl(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_rl_in_place(apuc);
    return NULL;
  }

  baryon_vr_patch_t *patch = malloc(sizeof(baryon_vr_patch_t));
  patch->vr = &apuc->rl;
  patch->update = NULL;
  return patch;
}

void baryon_reset_gl_in_place(baryon_apuc_t *apuc) {
  baryon_init_gl(&apuc->gl, false);
}

baryon_gl_t *baryon_reset_gl(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_gl_in_place(apuc);
  }
  return NULL;
}

void baryon_reset_ggl_in_place(baryon_apuc_t *apuc) {
  baryon_init_ggl(&apuc->ggl, false);
}

baryon_ggl_t *baryon_reset_ggl(baryon_apuc_t *apuc)
{
  if (apuc->in_place) {
    baryon_reset_ggl_in_place(apuc);
  }
  return NULL;
}

void baryon_reset_rsp16_in_place(baryon_apuc_t *apuc) {
  baryon_init_rsp16(&apuc->rsp16, false);
}

baryon_rsp16_t *baryon_reset_rsp16(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_rsp16_in_place(apuc);
  }
  return NULL;
}

void baryon_reset_rsp256_in_place(baryon_apuc_t *apuc) {
  baryon_init_rsp256(&apuc->rsp256, false);
}

baryon_rsp256_t *baryon_reset_rsp256(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_rsp256_in_place(apuc);
  }
  return NULL;
}

void baryon_reset_rsp2k_in_place(baryon_apuc_t *apuc) {
  baryon_init_rsp2k(&apuc->rsp2k, false);
}

baryon_rsp2k_t *baryon_reset_rsp2k(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_rsp2k_in_place(apuc);
  }
  return NULL;
}

void baryon_reset_rsp32k_in_place(baryon_apuc_t *apuc) {
  baryon_init_rsp32k(&apuc->rsp32k, false);
}

baryon_rsp32k_t *baryon_reset_rsp32k(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_rsp32k_in_place(apuc);
  }
  return NULL;
}

void baryon_reset_l1_in_place(baryon_apuc_t *apuc) {
  memset(&apuc->l1, false, BARYON_NUM_L1_ROWS * BARYON_L1_SIZE);
}

baryon_l1_t (*baryon_reset_l1(baryon_apuc_t *apuc))[BARYON_NUM_L1_ROWS] {
  if (apuc->in_place) {
    baryon_reset_l1_in_place(apuc);
  }

  return NULL;
}

void baryon_reset_l2_in_place(baryon_apuc_t *apuc) {
  memset(&apuc->l2, false, BARYON_NUM_L2_ROWS * BARYON_L2_SIZE);
}

baryon_l2_t (*baryon_reset_l2(baryon_apuc_t *apuc))[BARYON_NUM_L2_ROWS] {
  if (apuc->in_place) {
    baryon_reset_l2_in_place(apuc);
  }

  return NULL;
}

void baryon_reset_lgl_in_place(baryon_apuc_t *apuc) {
  baryon_init_lgl(&apuc->lgl, false);
}

baryon_lgl_t *baryon_reset_lgl(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_reset_lgl_in_place(apuc);
  }

  return NULL;
}

void baryon_bank_group_row(size_t l1_addr, size_t *bank, size_t *group,
                           size_t *row) {
  *bank = (l1_addr >> 11) & 0x3;
  *group = (l1_addr >> 9) & 0x3;
  *row = l1_addr & 0x1FF;
}

void baryon_rsp16_from_rsp256_in_place(baryon_apuc_t *apuc) {
  baryon_rsp16_t *rsp_left = &apuc->rsp16;
  baryon_rsp256_t *rsp_right = &apuc->rsp256;
  baryon_rsp_from_expansion(rsp_left, rsp_right, BARYON_NUM_RSP16_PLATS,
                            BARYON_NUM_RSP256_PLATS);
}

baryon_rsp16_t *baryon_rsp16_from_rsp256(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_rsp16_from_rsp256_in_place(apuc);
    return NULL;
  }

  baryon_rsp16_t *rsp_left = malloc(sizeof(baryon_rsp16_t));
  baryon_rsp256_t *rsp_right = &apuc->rsp256;
  baryon_rsp_from_expansion(rsp_left, rsp_right, BARYON_NUM_RSP16_PLATS,
                            BARYON_NUM_RSP256_PLATS);

  return rsp_left;
}

void baryon_rsp256_from_rsp16_in_place(baryon_apuc_t *apuc) {
  baryon_rsp256_t *rsp_left = &apuc->rsp256;
  baryon_rsp16_t *rsp_right = &apuc->rsp16;
  baryon_rsp_from_contraction(rsp_left, rsp_right, BARYON_NUM_RSP256_PLATS,
                              BARYON_NUM_RSP16_PLATS);
}

baryon_rsp256_t *baryon_rsp256_from_rsp16(baryon_apuc_t *apuc) {
  apuc->rsp_mode = BARYON_RSP_MODE_RSP256_READ;

  if (apuc->in_place) {
    baryon_rsp256_from_rsp16_in_place(apuc);
    return NULL;
  }

  baryon_rsp256_t *rsp_left = malloc(sizeof(baryon_rsp256_t));
  baryon_rsp16_t *rsp_right = &apuc->rsp16;
  baryon_rsp_from_contraction(rsp_left, rsp_right, BARYON_NUM_RSP256_PLATS,
                              BARYON_NUM_RSP16_PLATS);

  return rsp_left;
}

void baryon_rsp256_from_rsp2k_in_place(baryon_apuc_t *apuc) {
  baryon_rsp256_t *rsp_left = &apuc->rsp256;
  baryon_rsp2k_t *rsp_right = &apuc->rsp2k;
  baryon_rsp_from_expansion(rsp_left, rsp_right, BARYON_NUM_RSP256_PLATS,
                            BARYON_NUM_RSP2K_PLATS);
}

baryon_rsp256_t *baryon_rsp256_from_rsp2k(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_rsp256_from_rsp2k_in_place(apuc);
    return NULL;
  }

  baryon_rsp256_t *rsp_left = malloc(sizeof(baryon_rsp256_t));
  baryon_rsp2k_t *rsp_right = &apuc->rsp2k;
  baryon_rsp_from_expansion(rsp_left, rsp_right, BARYON_NUM_RSP256_PLATS,
                            BARYON_NUM_RSP2K_PLATS);

  return rsp_left;
}

void baryon_rsp2k_from_rsp256_in_place(baryon_apuc_t *apuc) {
  baryon_rsp2k_t *rsp_left = &apuc->rsp2k;
  baryon_rsp256_t *rsp_right = &apuc->rsp256;
  baryon_rsp_from_contraction(rsp_left, rsp_right, BARYON_NUM_RSP2K_PLATS,
                              BARYON_NUM_RSP256_PLATS);
}

baryon_rsp2k_t *baryon_rsp2k_from_rsp256(baryon_apuc_t *apuc) {
  apuc->rsp_mode = BARYON_RSP_MODE_RSP2K_READ;

  if (apuc->in_place) {
    baryon_rsp2k_from_rsp256_in_place(apuc);
    return NULL;
  }

  baryon_rsp2k_t *rsp_left = malloc(sizeof(baryon_rsp2k_t));
  baryon_rsp256_t *rsp_right = &apuc->rsp256;
  baryon_rsp_from_contraction(rsp_left, rsp_right, BARYON_NUM_RSP2K_PLATS,
                              BARYON_NUM_RSP256_PLATS);

  return rsp_left;
}

void baryon_rsp2k_from_rsp32k_in_place(baryon_apuc_t *apuc) {
  baryon_foreach_half_bank(half_bank, {
    bool value = apuc->rsp32k[half_bank];
    baryon_foreach_rsp2k_section(section, {
      apuc->rsp2k[section][half_bank] = value;
    });
  });
}

baryon_rsp2k_t *baryon_rsp2k_from_rsp32k(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_rsp2k_from_rsp32k_in_place(apuc);
    return NULL;
  }

  baryon_rsp2k_t *rsp2k = malloc(sizeof(baryon_rsp2k_t));
  baryon_rsp32k_t *rsp32k = &apuc->rsp32k;

  baryon_foreach_half_bank(half_bank, {
    bool value = (*rsp32k)[half_bank];
    baryon_foreach_rsp2k_section(section, {
      (*rsp2k)[section][half_bank] = value;
    });
  });

  return rsp2k;
}

void baryon_rsp32k_from_rsp2k_in_place(baryon_apuc_t *apuc) {
  baryon_foreach_half_bank(half_bank, {
    apuc->rsp32k[half_bank] = false;
    baryon_foreach_rsp2k_section(section, {
      apuc->rsp32k[half_bank] |= apuc->rsp2k[section][half_bank];
    });
  });
}

baryon_rsp32k_t *baryon_rsp32k_from_rsp2k(baryon_apuc_t *apuc) {
  apuc->rsp_mode = BARYON_RSP_MODE_RSP32K_READ;

  if (apuc->in_place) {
    baryon_rsp32k_from_rsp2k_in_place(apuc);
    return NULL;
  }

  baryon_rsp32k_t *rsp32k = malloc(sizeof(baryon_rsp32k_t));

  baryon_foreach_half_bank(half_bank, {
    (*rsp32k)[half_bank] = false;
    baryon_foreach_rsp2k_section(section, {
      (*rsp32k)[half_bank] |= apuc->rsp2k[section][half_bank];
    });
  });

  return rsp32k;
}

void baryon_noop_in_place(baryon_apuc_t *apuc) {
  // nothing to do
}

void *baryon_noop(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_noop_in_place(apuc);
  }
  return NULL;
}

void baryon_fsel_noop_in_place(baryon_apuc_t *apuc) {
  // nothing to do
}

void *baryon_fsel_noop(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_fsel_noop_in_place(apuc);
  }
  return NULL;
}

void baryon_rsp_end_in_place(baryon_apuc_t *apuc) {
  static baryon_rsp_fifo_msg_t rsp_fifo_msg;

  if (apuc->rsp_mode == BARYON_RSP_MODE_RSP32K_READ) {
    for (size_t apc_id = 0; apc_id < BARYON_NUM_APCS_PER_APUC; apc_id += 1) {
      size_t offset = apc_id * BARYON_NUM_HALF_BANKS_PER_APC;

      // TODO: Only enqueue rsp2k if enough clock cycles have passed since
      // calling rsp32k-from-rsp2k (2 cycles before calling rsp_end).
      memset(&rsp_fifo_msg.rsp2k, 0x0000,
             BARYON_NUM_HALF_BANKS_PER_APC * sizeof(uint16_t));
      baryon_foreach_range(half_bank, BARYON_NUM_HALF_BANKS_PER_APC, {
        baryon_foreach_rsp2k_section(section, {
          rsp_fifo_msg.rsp2k[half_bank] |=
            (apuc->rsp2k[section][half_bank + offset] << section);
        });
      });

      rsp_fifo_msg.rsp32k = 0x00;
      baryon_foreach_range(section, BARYON_NUM_HALF_BANKS_PER_APC, {
        rsp_fifo_msg.rsp32k |= (apuc->rsp32k[section + offset] << section);
      });

      baryon_apc_rsp_fifo_t *apc_rsp_fifo =
          &apuc->apuc_rsp_fifo->queues[apc_id];
      baryon_apc_rsp_fifo_enqueue(apc_rsp_fifo, &rsp_fifo_msg);
    }
  }

  apuc->rsp_mode = BARYON_RSP_MODE_IDLE;
  baryon_init_rsp16(&apuc->rsp16, false);
  baryon_init_rsp256(&apuc->rsp256, false);
  baryon_init_rsp2k(&apuc->rsp2k, false);
  baryon_init_rsp32k(&apuc->rsp32k, false);
}

baryon_rsp_patches_t *baryon_rsp_end(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_rsp_end_in_place(apuc);
  }

  return NULL;
}

void baryon_rsp_start_ret_in_place(baryon_apuc_t *apuc) {
  // nothing to do
}

void *baryon_rsp_start_ret(baryon_apuc_t *apuc) {
  switch (apuc->rsp_mode) {
  case BARYON_RSP_MODE_RSP16_READ: {
    apuc->rsp_mode = BARYON_RSP_MODE_RSP16_WRITE;
    break;
  }
  case BARYON_RSP_MODE_RSP256_READ: {
    apuc->rsp_mode = BARYON_RSP_MODE_RSP256_WRITE;
    break;
  }
  case BARYON_RSP_MODE_RSP2K_READ: {
    apuc->rsp_mode = BARYON_RSP_MODE_RSP2K_WRITE;
    break;
  }
  case BARYON_RSP_MODE_RSP32K_READ: {
    apuc->rsp_mode = BARYON_RSP_MODE_RSP32K_WRITE;
    break;
  }
  }

  if (apuc->in_place) {
    baryon_rsp_start_ret_in_place(apuc);
  }

  return NULL;
}

void baryon_l2_end_in_place(baryon_apuc_t *apuc) {
  // nothing to do
}

void *baryon_l2_end(baryon_apuc_t *apuc) {
  if (apuc->in_place) {
    baryon_l2_end_in_place(apuc);
  }
  return NULL;
}

static inline void baryon_invert_rl(baryon_rl_t *tgt, baryon_rl_t *src) {
  baryon_foreach_rl_section_plat(section, plat, {
    (*tgt)[section][plat] = !(*src)[section][plat];
  });
}

baryon_rl_t *baryon_rl_in_place(baryon_apuc_t *apuc, baryon_rl_t *rl) {
  memcpy(rl, &apuc->rl, BARYON_RL_SIZE);
  return rl;
}

baryon_rl_t *baryon_rl(baryon_apuc_t *apuc) {
  baryon_rl_t *rl = malloc(sizeof(baryon_rl_t));
  return baryon_rl_in_place(apuc, rl);
}

baryon_rl_t *baryon_nrl_in_place(baryon_apuc_t *apuc, baryon_rl_t *nrl) {
  baryon_foreach_rl_plat(plat, { (*nrl)[0][plat] = false; });
  baryon_foreach_range(section, 1, BARYON_NUM_SECTIONS, {
    baryon_foreach_rl_plat(
        plat, { (*nrl)[section][plat] = apuc->rl[section - 1][plat]; });
  });
  return nrl;
}

baryon_rl_t *baryon_nrl(baryon_apuc_t *apuc) {
  baryon_rl_t *nrl = malloc(sizeof(baryon_rl_t));
  return baryon_nrl_in_place(apuc, nrl);
}

baryon_rl_t *baryon_erl_in_place(baryon_apuc_t *apuc, baryon_rl_t *erl) {
  baryon_foreach_half_bank(half_bank, {
    size_t lower = half_bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    size_t upper = lower + BARYON_NUM_PLATS_PER_HALF_BANK;
    baryon_foreach_rl_section(section, {
      (*erl)[section][upper - 1] = false;
      baryon_foreach_range(plat, lower, upper - 1, {
        (*erl)[section][plat] = apuc->rl[section][plat + 1];
      });
    });
  });
  return erl;
}

baryon_rl_t *baryon_erl(baryon_apuc_t *apuc) {
  baryon_rl_t *erl = malloc(sizeof(baryon_rl_t));
  return baryon_erl_in_place(apuc, erl);
}

baryon_rl_t *baryon_wrl_in_place(baryon_apuc_t *apuc, baryon_rl_t *wrl) {
  baryon_foreach_half_bank(half_bank, {
    size_t lower = half_bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    size_t upper = lower + BARYON_NUM_PLATS_PER_HALF_BANK;
    baryon_foreach_rl_section(section, {
      (*wrl)[section][lower] = false;
      baryon_foreach_range(plat, lower + 1, upper, {
        (*wrl)[section][plat] = apuc->rl[section][plat - 1];
      });
    });
  });
  return wrl;
}

baryon_rl_t *baryon_wrl(baryon_apuc_t *apuc) {
  baryon_rl_t *wrl = malloc(sizeof(baryon_rl_t));
  return baryon_wrl_in_place(apuc, wrl);
}

baryon_rl_t *baryon_srl_in_place(baryon_apuc_t *apuc, baryon_rl_t *srl) {
  baryon_foreach_rl_plat(plat,
                         { (*srl)[BARYON_NUM_SECTIONS - 1][plat] = false; });
  baryon_foreach_range(section, BARYON_NUM_SECTIONS - 1, {
    baryon_foreach_rl_plat(
        plat, { (*srl)[section][plat] = apuc->rl[section + 1][plat]; });
  });
  return srl;
}

baryon_rl_t *baryon_srl(baryon_apuc_t *apuc) {
  baryon_rl_t *srl = malloc(sizeof(baryon_rl_t));
  return baryon_srl_in_place(apuc, srl);
}

baryon_rl_t *baryon_inv_rl_in_place(baryon_apuc_t *apuc, baryon_rl_t *inv_rl) {
  baryon_invert_rl(inv_rl, &apuc->rl);
  return inv_rl;
}

baryon_rl_t *baryon_inv_rl(baryon_apuc_t *apuc) {
  baryon_rl_t *inv_rl = malloc(sizeof(baryon_rl_t));
  return baryon_inv_rl_in_place(apuc, inv_rl);
}

baryon_rl_t *baryon_inv_nrl_in_place(baryon_apuc_t *apuc, baryon_rl_t *inv_nrl) {
  baryon_nrl_in_place(apuc, inv_nrl);
  baryon_invert_rl(inv_nrl, inv_nrl);
  return inv_nrl;
}

baryon_rl_t *baryon_inv_nrl(baryon_apuc_t *apuc) {
  baryon_rl_t *inv_nrl = malloc(sizeof(baryon_rl_t));
  return baryon_inv_nrl_in_place(apuc, inv_nrl);
}

baryon_rl_t *baryon_inv_erl_in_place(baryon_apuc_t *apuc, baryon_rl_t *inv_erl) {
  baryon_erl_in_place(apuc, inv_erl);
  baryon_invert_rl(inv_erl, inv_erl);
  return inv_erl;
}

baryon_rl_t *baryon_inv_erl(baryon_apuc_t *apuc) {
  baryon_rl_t *inv_erl = malloc(sizeof(baryon_rl_t));
  return baryon_inv_erl_in_place(apuc, inv_erl);
}

baryon_rl_t *baryon_inv_wrl_in_place(baryon_apuc_t *apuc, baryon_rl_t *inv_wrl) {
  baryon_wrl_in_place(apuc, inv_wrl);
  baryon_invert_rl(inv_wrl, inv_wrl);
  return inv_wrl;
}

baryon_rl_t *baryon_inv_wrl(baryon_apuc_t *apuc) {
  baryon_rl_t *inv_wrl = malloc(sizeof(baryon_rl_t));
  return baryon_inv_wrl_in_place(apuc, inv_wrl);
}

baryon_rl_t *baryon_inv_srl_in_place(baryon_apuc_t *apuc, baryon_rl_t *inv_srl) {
  baryon_srl_in_place(apuc, inv_srl);
  baryon_invert_rl(inv_srl, inv_srl);
  return inv_srl;
}

baryon_rl_t *baryon_inv_srl(baryon_apuc_t *apuc) {
  baryon_rl_t *inv_srl = malloc(sizeof(baryon_rl_t));
  return baryon_inv_srl_in_place(apuc, inv_srl);
}

baryon_gl_t *baryon_gl_in_place(baryon_apuc_t *apuc, baryon_gl_t *gl) {
  memcpy(gl, &apuc->gl, BARYON_GL_SIZE);
  return gl;
}

baryon_gl_t *baryon_gl(baryon_apuc_t *apuc) {
  baryon_gl_t *gl = malloc(sizeof(baryon_gl_t));
  return baryon_gl_in_place(apuc, gl);
}

baryon_gl_t *baryon_inv_gl_in_place(baryon_apuc_t *apuc, baryon_gl_t *inv_gl) {
  baryon_foreach_gl_plat(plat, {
    (*inv_gl)[plat] = !apuc->gl[plat];
  });
  return inv_gl;
}

baryon_gl_t *baryon_inv_gl(baryon_apuc_t *apuc) {
  baryon_gl_t *inv_gl = malloc(sizeof(baryon_gl_t));
  return baryon_inv_gl_in_place(apuc, inv_gl);
}

baryon_ggl_t *baryon_ggl_in_place(baryon_apuc_t *apuc, baryon_ggl_t *ggl) {
  memcpy(ggl, &apuc->ggl, BARYON_GGL_SIZE);
  return ggl;
}

baryon_ggl_t *baryon_ggl(baryon_apuc_t *apuc) {
  baryon_ggl_t *ggl = malloc(sizeof(baryon_ggl_t));
  return baryon_ggl_in_place(apuc, ggl);
}

baryon_ggl_t *baryon_inv_ggl_in_place(baryon_apuc_t *apuc,
                                      baryon_ggl_t *inv_ggl) {
  baryon_foreach_ggl_group_plat(group, plat, {
    (*inv_ggl)[group][plat] = !apuc->ggl[group][plat];
  });
  return inv_ggl;
}

baryon_ggl_t *baryon_inv_ggl(baryon_apuc_t *apuc) {
  baryon_ggl_t *inv_ggl = malloc(sizeof(baryon_ggl_t));
  return baryon_inv_ggl_in_place(apuc, inv_ggl);
}

baryon_rsp16_t *baryon_rsp16_in_place(baryon_apuc_t *apuc,
                                      baryon_rsp16_t *rsp16) {
  memcpy(rsp16, &apuc->rsp16, BARYON_RSP16_SIZE);
  return rsp16;
}

baryon_rsp16_t *baryon_rsp16(baryon_apuc_t *apuc) {
  baryon_rsp16_t *rsp16 = malloc(sizeof(baryon_rsp16_t));
  return baryon_rsp16_in_place(apuc, rsp16);
}

baryon_rsp16_t *baryon_inv_rsp16_in_place(baryon_apuc_t *apuc,
                                          baryon_rsp16_t *inv_rsp16) {
  baryon_foreach_rsp16_section_plat(section, plat, {
    (*inv_rsp16)[section][plat] = !apuc->rsp16[section][plat];
  });
  return inv_rsp16;
}

baryon_rsp16_t *baryon_inv_rsp16(baryon_apuc_t *apuc) {
  baryon_rsp16_t *inv_rsp16 = malloc(sizeof(baryon_rsp16_t));
  return baryon_inv_rsp16_in_place(apuc, inv_rsp16);
}

void *baryon_src(baryon_apuc_t *apuc, baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_RL:
    return baryon_rl(apuc);
  case BARYON_SRC_NRL:
    return baryon_nrl(apuc);
  case BARYON_SRC_ERL:
    return baryon_erl(apuc);
  case BARYON_SRC_WRL:
    return baryon_wrl(apuc);
  case BARYON_SRC_SRL:
    return baryon_srl(apuc);
  case BARYON_SRC_INV_RL:
    return baryon_inv_rl(apuc);
  case BARYON_SRC_INV_NRL:
    return baryon_inv_nrl(apuc);
  case BARYON_SRC_INV_ERL:
    return baryon_inv_erl(apuc);
  case BARYON_SRC_INV_WRL:
    return baryon_inv_wrl(apuc);
  case BARYON_SRC_INV_SRL:
    return baryon_inv_srl(apuc);
  case BARYON_SRC_GGL:
    return baryon_ggl(apuc);
  case BARYON_SRC_INV_GGL:
    return baryon_inv_ggl(apuc);
  case BARYON_SRC_GL:
    return baryon_gl(apuc);
  case BARYON_SRC_INV_GL:
    return baryon_inv_gl(apuc);
  case BARYON_SRC_RSP16:
    return baryon_rsp16(apuc);
  case BARYON_SRC_INV_RSP16:
    return baryon_inv_rsp16(apuc);
  }
}

void baryon_free_src(void *src, baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_RL:      // fallthrough
  case BARYON_SRC_NRL:     // fallthrough
  case BARYON_SRC_ERL:     // fallthrough
  case BARYON_SRC_WRL:     // fallthrough
  case BARYON_SRC_SRL:     // fallthrough
  case BARYON_SRC_INV_RL:  // fallthrough
  case BARYON_SRC_INV_NRL: // fallthrough
  case BARYON_SRC_INV_ERL: // fallthrough
  case BARYON_SRC_INV_WRL: // fallthrough
  case BARYON_SRC_INV_SRL:
    baryon_free_rl((baryon_rl_t *)src);
    break;
  case BARYON_SRC_GGL: // fallthrough
  case BARYON_SRC_INV_GGL:
    baryon_free_ggl((baryon_ggl_t *)src);
    break;
  case BARYON_SRC_GL: // fallthrough
  case BARYON_SRC_INV_GL:
    baryon_free_gl((baryon_gl_t *)src);
    break;
  case BARYON_SRC_RSP16: // fallthrough
  case BARYON_SRC_INV_RSP16:
    baryon_free_rsp16((baryon_rsp16_t *)src);
    break;
  }
}

baryon_gl_t *baryon_ternary_expr(baryon_apuc_t *apuc,
                                 baryon_gl_t *nth1,
                                 baryon_gl_t *nth2,
                                 baryon_gl_t *nth3,
                                 baryon_ternary_op_t op1,
                                 baryon_binary_op_t op2) {
  baryon_gl_t *result = op2(nth2, nth3);
  op1(nth1, result, result);
  return result;
}

size_t baryon_count_masked_sections(baryon_sm_t mask) {
  size_t num_masked_sections = 0;
  baryon_foreach_masked_section(mask, section, {
    num_masked_sections += 1;
  });
  return num_masked_sections;
}

baryon_brsp16_t *baryon_brsp16(baryon_rsp16_t *rsp16) {
  baryon_vr_t *brsp16 = malloc(sizeof(baryon_vr_t));
  baryon_foreach_rsp16_plat(rsp16_plat, {
    size_t lower = rsp16_plat * 16;
    size_t upper = lower + 16;
    baryon_foreach_range(vr_plat, lower, upper, {
      baryon_foreach_rsp16_section(section, {
        (*brsp16)[section][vr_plat] = (*rsp16)[section][rsp16_plat];
      });
    });
  });
  return brsp16;
}

void baryon_sb_op_eq_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_vr_t *vrs[], size_t num_vrs,
                                 baryon_binary_op_t op, baryon_gl_t *gl) {
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *rhs = gl;
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      baryon_rwinh_in_place(apuc, lhs, section, result);
      memcpy(lhs, result, BARYON_WORDLINE_SIZE);
      baryon_free_wordline(result);
    });
  });
}

baryon_wordline_map_t *baryon_sb_op_eq_gl(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs,
                                          baryon_binary_op_t op,
                                          baryon_gl_t *gl) {
  if (apuc->in_place) {
    baryon_sb_op_eq_gl_in_place(apuc, mask, vrs, num_vrs, op, gl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_vrs * num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *rhs = gl;
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      baryon_rwinh_in_place(apuc, lhs, section, result);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
  });

  return patch;
}

void baryon_sb_op_eq_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                  baryon_vr_t *vrs[], size_t num_vrs,
                                  baryon_binary_op_t op, baryon_ggl_t *ggl) {
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_wordline_t *rhs = pseudo_gl;
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      baryon_rwinh_in_place(apuc, lhs, section, result);
      memcpy(lhs, result, BARYON_WORDLINE_SIZE);
      baryon_free_wordline(result);
    });
  });
}

baryon_wordline_map_t *baryon_sb_op_eq_ggl(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs,
                                           baryon_binary_op_t op,
                                           baryon_ggl_t *ggl) {
  if (apuc->in_place) {
    baryon_sb_op_eq_ggl_in_place(apuc, mask, vrs, num_vrs, op, ggl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_vrs * num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_wordline_t *rhs = pseudo_gl;
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      baryon_rwinh_in_place(apuc, lhs, section, result);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
  });

  return patch;
}

void baryon_sb_op_eq_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_vr_t *vrs[], size_t num_vrs,
                                 baryon_binary_op_t op, baryon_rl_t *rl) {
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *wordline = &(*rl)[section];
    baryon_wordline_t *rhs = wordline;
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      baryon_rwinh_in_place(apuc, lhs, section, result);
      memcpy(lhs, result, BARYON_WORDLINE_SIZE);
      baryon_free_wordline(result);
    });
  });
}

baryon_wordline_map_t *baryon_sb_op_eq_rl(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs,
                                          baryon_binary_op_t op,
                                          baryon_rl_t *rl) {
  if (apuc->in_place) {
    baryon_sb_op_eq_rl_in_place(apuc, mask, vrs, num_vrs, op, rl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_vrs * num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *wordline = &(*rl)[section];
    baryon_wordline_t *rhs = wordline;
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      baryon_rwinh_in_place(apuc, lhs, section, result);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
  });

  return patch;
}

void baryon_sb_op_eq_rsp16_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                    baryon_vr_t *vrs[], size_t num_vrs,
                                    baryon_binary_op_t op,
                                    baryon_rsp16_t *rsp16) {
  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *rhs = &(*filtered_brsp16)[section];
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      memcpy(lhs, result, BARYON_WORDLINE_SIZE);
      baryon_free_wordline(result);
    });
  });

  baryon_free_vr(filtered_brsp16);
}

baryon_wordline_map_t *baryon_sb_op_eq_rsp16(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_vr_t *vrs[],
                                             size_t num_vrs,
                                             baryon_binary_op_t op,
                                             baryon_rsp16_t *rsp16) {
  if (apuc->in_place) {
    baryon_sb_op_eq_rsp16_in_place(apuc, mask, vrs, num_vrs, op, rsp16);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_vrs * num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *rhs = &(*filtered_brsp16)[section];
    baryon_foreach_range(i, num_vrs, {
      baryon_vr_t *vr = vrs[i];
      baryon_wordline_t *lhs = &(*vr)[section];
      baryon_wordline_t *result = op(lhs, rhs);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
  });

  baryon_free_vr(filtered_brsp16);
  return patch;
}

baryon_wordline_map_t *baryon_sb_op_eq_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs,
                                           baryon_binary_op_t op,
                                           void *src,
                                           baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_GL: // fallthrough
  case BARYON_SRC_INV_GL: {
    return baryon_sb_op_eq_gl(apuc, mask, vrs, num_vrs, op, src);
  }
  case BARYON_SRC_GGL: // fallthrough
  case BARYON_SRC_INV_GGL: {
    return baryon_sb_op_eq_ggl(apuc, mask, vrs, num_vrs, op, src);
  }
  case BARYON_SRC_RL: // fallthrough
  case BARYON_SRC_NRL: // fallthrough
  case BARYON_SRC_ERL: // fallthrough
  case BARYON_SRC_WRL: // fallthrough
  case BARYON_SRC_SRL: // fallthrough
  case BARYON_SRC_INV_RL: // fallthrough
  case BARYON_SRC_INV_NRL: // fallthrough
  case BARYON_SRC_INV_ERL: // fallthrough
  case BARYON_SRC_INV_WRL: // fallthrough
  case BARYON_SRC_INV_SRL: {
    return baryon_sb_op_eq_rl(apuc, mask, vrs, num_vrs, op, src);
  }
  case BARYON_SRC_RSP16: // fallthrough
  case BARYON_SRC_INV_RSP16: {
    return baryon_sb_op_eq_rsp16(apuc, mask, vrs, num_vrs, op, src);
  }
  }
}

baryon_wordline_map_t * baryon_sb_from_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs,
                                           void *src,
                                           baryon_src_t src_type) {
  return baryon_sb_op_eq_src(apuc, mask,
                             vrs, num_vrs,
                             baryon_right,
                             src, src_type);
}

baryon_wordline_map_t * baryon_sb_from_inv_src(baryon_apuc_t *apuc,
                                               baryon_sm_t mask,
                                               baryon_vr_t *vrs[],
                                               size_t num_vrs,
                                               void *src,
                                               baryon_src_t src_type) {
  return baryon_sb_op_eq_src(apuc, mask,
                             vrs, num_vrs,
                             baryon_inv_right,
                             src, src_type);
}

baryon_wordline_map_t * baryon_sb_cond_eq_src(baryon_apuc_t *apuc,
                                              baryon_sm_t mask,
                                              baryon_vr_t *vrs[],
                                              size_t num_vrs,
                                              void *src,
                                              baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_RL:  // fallthrough
  case BARYON_SRC_NRL: // fallthrough
  case BARYON_SRC_ERL: // fallthrough
  case BARYON_SRC_WRL: // fallthrough
  case BARYON_SRC_SRL: // fallthrough
  case BARYON_SRC_GGL: // fallthrough
  case BARYON_SRC_GL:  // fallthrough
  case BARYON_SRC_RSP16:
    return baryon_sb_op_eq_src(apuc, mask, vrs, num_vrs, baryon_left_or_right,
                               src, src_type);
  default:
    return baryon_sb_cond_eq_inv_src(apuc, mask, vrs, num_vrs, src, src_type);
  }
}

baryon_wordline_map_t * baryon_sb_cond_eq_inv_src(baryon_apuc_t *apuc,
                                                  baryon_sm_t mask,
                                                  baryon_vr_t *vrs[],
                                                  size_t num_vrs,
                                                  void *src,
                                                  baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_INV_RL:  // fallthrough
  case BARYON_SRC_INV_NRL: // fallthrough
  case BARYON_SRC_INV_ERL: // fallthrough
  case BARYON_SRC_INV_WRL: // fallthrough
  case BARYON_SRC_INV_SRL: // fallthrough
  case BARYON_SRC_INV_GGL: // fallthrough
  case BARYON_SRC_INV_GL:  // fallthrough
  case BARYON_SRC_INV_RSP16:
    return baryon_sb_op_eq_src(apuc, mask, vrs, num_vrs,
                               baryon_left_and_right, src, src_type);
  default:
    return baryon_sb_cond_eq_src(apuc, mask, vrs, num_vrs, src, src_type);
  }
}

void baryon_set_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask, bool bit) {
  baryon_wordline_t *wordline = malloc(BARYON_WORDLINE_SIZE);

  baryon_foreach_masked_section(mask, section, {
    memset(wordline, bit, BARYON_WORDLINE_SIZE);
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *result = wordline;
    baryon_rwinh_in_place(apuc, lhs, section, result);
    memcpy(lhs, result, BARYON_WORDLINE_SIZE);
  });

  baryon_free_wordline(wordline);
}

baryon_wordline_map_t *baryon_set_rl(baryon_apuc_t *apuc,
                                     baryon_sm_t mask,
                                     bool bit) {
  if (apuc->in_place) {
    baryon_set_rl_in_place(apuc, mask, bit);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *result = malloc(BARYON_WORDLINE_SIZE);
    memset(result, bit, BARYON_WORDLINE_SIZE);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

baryon_wordline_t *baryon_conjoin_sections_in_place(baryon_vr_t *vrs[],
                                                    size_t num_vrs,
                                                    size_t section,
                                                    baryon_wordline_t *conj)
{
  memset(conj, true, BARYON_WORDLINE_SIZE);
  baryon_foreach_range(i, num_vrs, {
    baryon_wordline_t *wordline = &(*vrs[i])[section];
    baryon_left_and_right_in_place(conj, wordline, conj);
  });
  return conj;
}

baryon_wordline_t *baryon_conjoin_sections(baryon_vr_t *vrs[],
                                           size_t num_vrs,
                                           size_t section)
{
  baryon_wordline_t *conj = malloc(BARYON_WORDLINE_SIZE);
  return baryon_conjoin_sections_in_place(vrs, num_vrs, section, conj);
}

void baryon_rl_op_eq_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_binary_op_t op, baryon_gl_t *gl) {
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    memcpy(lhs, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });
}

baryon_wordline_map_t *baryon_rl_op_eq_gl(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_binary_op_t op,
                                          baryon_gl_t *gl) {
  if (apuc->in_place) {
    baryon_rl_op_eq_gl_in_place(apuc, mask, op, gl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

void baryon_rl_op_eq_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                  baryon_binary_op_t op, baryon_ggl_t *ggl) {
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = pseudo_gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    memcpy(lhs, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });
}

baryon_wordline_map_t *baryon_rl_op_eq_ggl(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_binary_op_t op,
                                           baryon_ggl_t *ggl) {
  if (apuc->in_place) {
    baryon_rl_op_eq_ggl_in_place(apuc, mask, op, ggl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = pseudo_gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

void baryon_rl_op_eq_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_binary_op_t op, baryon_rl_t *rl) {
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = &(*rl)[section];
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    memcpy(lhs, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });
}

baryon_wordline_map_t *baryon_rl_op_eq_rl(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_binary_op_t op,
                                          baryon_rl_t *rl) {
  if (apuc->in_place) {
    baryon_rl_op_eq_rl_in_place(apuc, mask, op, rl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = &(*rl)[section];
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

void baryon_rl_op_eq_rsp16_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                    baryon_binary_op_t op,
                                    baryon_rsp16_t *rsp16) {
  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = &(*filtered_brsp16)[section];
    baryon_wordline_t *result = op(lhs, rhs);
    memcpy(lhs, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_vr(filtered_brsp16);
}

baryon_wordline_map_t *baryon_rl_op_eq_rsp16(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_binary_op_t op,
                                             baryon_rsp16_t *rsp16) {
  if (apuc->in_place) {
    baryon_rl_op_eq_rsp16_in_place(apuc, mask, op, rsp16);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_wordline_t *rhs = &(*filtered_brsp16)[section];
    baryon_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_vr(filtered_brsp16);
  return patch;
}

baryon_wordline_map_t *baryon_rl_op_eq_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_binary_op_t op,
                                           void *src,
                                           baryon_src_t src_type)
{
  switch (src_type) {
  case BARYON_SRC_GL: // fallthrough
  case BARYON_SRC_INV_GL: {
    return baryon_rl_op_eq_gl(apuc, mask, op, src);
  }
  case BARYON_SRC_GGL: // fallthrough
  case BARYON_SRC_INV_GGL: {
    return baryon_rl_op_eq_ggl(apuc, mask, op, src);
  }
  case BARYON_SRC_RL: // fallthrough
  case BARYON_SRC_NRL: // fallthrough
  case BARYON_SRC_ERL: // fallthrough
  case BARYON_SRC_WRL: // fallthrough
  case BARYON_SRC_SRL: // fallthrough
  case BARYON_SRC_INV_RL: // fallthrough
  case BARYON_SRC_INV_NRL: // fallthrough
  case BARYON_SRC_INV_ERL: // fallthrough
  case BARYON_SRC_INV_WRL: // fallthrough
  case BARYON_SRC_INV_SRL: {
    return baryon_rl_op_eq_rl(apuc, mask, op, src);
  }
  case BARYON_SRC_RSP16: // fallthrough
  case BARYON_SRC_INV_RSP16: {
    return baryon_rl_op_eq_rsp16(apuc, mask, op, src);
  }
  }
}

baryon_wordline_map_t *baryon_rl_from_src(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          void *src,
                                          baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_from_inv_src(baryon_apuc_t *apuc,
                                              baryon_sm_t mask,
                                              void *src,
                                              baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_inv_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_or_eq_src(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           void *src,
                                           baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_left_or_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_or_eq_inv_src(baryon_apuc_t *apuc,
                                               baryon_sm_t mask,
                                               void *src,
                                               baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_left_or_inv_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_and_eq_src(baryon_apuc_t *apuc,
                                            baryon_sm_t mask,
                                            void *src,
                                            baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_left_and_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_and_eq_inv_src(baryon_apuc_t *apuc,
                                                baryon_sm_t mask,
                                                void *src,
                                                baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_left_and_inv_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_xor_eq_src(baryon_apuc_t *apuc,
                                            baryon_sm_t mask,
                                            void *src,
                                            baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_left_xor_right,
                             src, src_type);
}

baryon_wordline_map_t *baryon_rl_xor_eq_inv_src(baryon_apuc_t *apuc,
                                                baryon_sm_t mask,
                                                void *src,
                                                baryon_src_t src_type)
{
  return baryon_rl_op_eq_src(apuc, mask,
                             baryon_left_xor_inv_right,
                             src, src_type);
}

void baryon_rl_op_eq_sb_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                 baryon_binary_op_t op, baryon_vr_t *vrs[],
                                 size_t num_vrs) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *rhs = sbdata;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    memcpy(lhs, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *baryon_rl_op_eq_sb(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_binary_op_t op,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs) {
  if (apuc->in_place) {
    baryon_rl_op_eq_sb_in_place(apuc, mask, op, vrs, num_vrs);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
    malloc(sizeof(baryon_wordline_map_t)
           + num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *lhs = &apuc->rl[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *rhs = sbdata;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, lhs, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

baryon_wordline_map_t *baryon_rl_from_sb(baryon_apuc_t *apuc,
                                         baryon_sm_t mask,
                                         baryon_vr_t *vrs[],
                                         size_t num_vrs)
{
  return baryon_rl_op_eq_sb(apuc, mask, baryon_right, vrs, num_vrs);
}

baryon_wordline_map_t *baryon_rl_from_inv_sb(baryon_apuc_t *apuc,
                                             baryon_sm_t mask,
                                             baryon_vr_t *vrs[],
                                             size_t num_vrs)
{
  return baryon_rl_op_eq_sb(apuc, mask, baryon_inv_right, vrs, num_vrs);
}

baryon_wordline_map_t *baryon_rl_or_eq_sb(baryon_apuc_t *apuc,
                                          baryon_sm_t mask,
                                          baryon_vr_t *vrs[],
                                          size_t num_vrs)
{
  return baryon_rl_op_eq_sb(apuc, mask, baryon_left_or_right, vrs, num_vrs);
}

baryon_wordline_map_t *baryon_rl_and_eq_sb(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_vr_t *vrs[],
                                           size_t num_vrs)
{
  return baryon_rl_op_eq_sb(apuc, mask, baryon_left_and_right, vrs, num_vrs);
}

baryon_wordline_map_t *baryon_rl_and_eq_inv_sb(baryon_apuc_t *apuc,
                                               baryon_sm_t mask,
                                               baryon_vr_t *vrs[],
                                               size_t num_vrs)
{
  return baryon_rl_op_eq_sb(apuc, mask, baryon_left_and_inv_right, vrs, num_vrs);
}

baryon_wordline_map_t *baryon_rl_xor_eq_sb(baryon_apuc_t *apuc, baryon_sm_t mask,
                                           baryon_vr_t *vrs[], size_t num_vrs)
{
  return baryon_rl_op_eq_sb(apuc, mask, baryon_left_xor_right, vrs, num_vrs);
}

void baryon_rl_op_eq_sb_and_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                        baryon_ternary_op_t op1,
                                        baryon_binary_op_t op2,
                                        baryon_vr_t *vrs[], size_t num_vrs,
                                        baryon_gl_t *gl) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = gl;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    memcpy(nth1, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_gl(baryon_apuc_t *apuc, baryon_sm_t mask,
                          baryon_ternary_op_t op1, baryon_binary_op_t op2,
                          baryon_vr_t *vrs[], size_t num_vrs, baryon_gl_t *gl) {
  if (apuc->in_place) {
    baryon_rl_op_eq_sb_and_gl_in_place(apuc, mask, op1, op2, vrs, num_vrs, gl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = gl;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

void baryon_rl_op_eq_sb_and_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                         baryon_ternary_op_t op1,
                                         baryon_binary_op_t op2,
                                         baryon_vr_t *vrs[], size_t num_vrs,
                                         baryon_ggl_t *ggl) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = pseudo_gl;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    memcpy(nth1, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_ggl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_ternary_op_t op1, baryon_binary_op_t op2,
                           baryon_vr_t *vrs[], size_t num_vrs, baryon_ggl_t *ggl) {
  if (apuc->in_place) {
    baryon_rl_op_eq_sb_and_ggl_in_place(apuc, mask, op1, op2, vrs, num_vrs, ggl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = pseudo_gl;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

void baryon_rl_op_eq_sb_and_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                        baryon_ternary_op_t op1,
                                        baryon_binary_op_t op2,
                                        baryon_vr_t *vrs[], size_t num_vrs,
                                        baryon_rl_t *rl) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_wordline_t *wordline = &(*rl)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = wordline;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    memcpy(nth1, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_rl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_ternary_op_t op1, baryon_binary_op_t op2,
                           baryon_vr_t *vrs[], size_t num_vrs, baryon_rl_t *rl) {
  if (apuc->in_place) {
    baryon_rl_op_eq_sb_and_rl_in_place(apuc, mask, op1, op2, vrs, num_vrs, rl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_wordline_t *wordline = &(*rl)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = wordline;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

void baryon_rl_op_eq_sb_and_rsp16_in_place(baryon_apuc_t *apuc,
                                           baryon_sm_t mask,
                                           baryon_ternary_op_t op1,
                                           baryon_binary_op_t op2,
                                           baryon_vr_t *vrs[], size_t num_vrs,
                                           baryon_rsp16_t *rsp16) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_wordline_t *wordline = &(*filtered_brsp16)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = wordline;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    memcpy(nth1, result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_vr(filtered_brsp16);
  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_rsp16(baryon_apuc_t *apuc, baryon_sm_t mask,
                             baryon_ternary_op_t op1, baryon_binary_op_t op2,
                             baryon_vr_t *vrs[], size_t num_vrs,
                             baryon_rsp16_t *rsp16) {
  if (apuc->in_place) {
    baryon_rl_op_eq_sb_and_rsp16_in_place(apuc, mask, op1, op2, vrs, num_vrs, rsp16);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *nth1 = &apuc->rl[section];
    baryon_wordline_t *wordline = &(*filtered_brsp16)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *nth2 = sbdata;
    baryon_wordline_t *nth3 = wordline;
    baryon_wordline_t *result =
      baryon_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    baryon_rwinh_in_place(apuc, nth1, section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_vr(filtered_brsp16);
  baryon_free_wordline(sbdata);
  return patch;
}

baryon_wordline_map_t *
baryon_rl_op_eq_sb_and_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_ternary_op_t op1, baryon_binary_op_t op2,
                           baryon_vr_t *vrs[], size_t num_vrs, void *src,
                           baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_GL: // fallthrough
  case BARYON_SRC_INV_GL: {
    return baryon_rl_op_eq_sb_and_gl(apuc, mask, op1, op2, vrs, num_vrs, src);
  }
  case BARYON_SRC_GGL: // fallthrough
  case BARYON_SRC_INV_GGL: {
    return baryon_rl_op_eq_sb_and_ggl(apuc, mask, op1, op2, vrs, num_vrs, src);
  }
  case BARYON_SRC_RL:      // fallthrough
  case BARYON_SRC_NRL:     // fallthrough
  case BARYON_SRC_ERL:     // fallthrough
  case BARYON_SRC_WRL:     // fallthrough
  case BARYON_SRC_SRL:     // fallthrough
  case BARYON_SRC_INV_RL:  // fallthrough
  case BARYON_SRC_INV_NRL: // fallthrough
  case BARYON_SRC_INV_ERL: // fallthrough
  case BARYON_SRC_INV_WRL: // fallthrough
  case BARYON_SRC_INV_SRL: {
    return baryon_rl_op_eq_sb_and_rl(apuc, mask, op1, op2, vrs, num_vrs, src);
  }
  case BARYON_SRC_RSP16: // fallthrough
  case BARYON_SRC_INV_RSP16: {
    return baryon_rl_op_eq_sb_and_rsp16(apuc, mask, op1, op2, vrs, num_vrs,
                                        src);
  }
  }
}

baryon_wordline_map_t *baryon_rl_from_sb_and_src(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask,
                                                 baryon_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_right_in_place,
                                    baryon_left_and_right, vrs, num_vrs, src,
                                    src_type);
}

baryon_wordline_map_t *baryon_rl_or_eq_sb_and_src(baryon_apuc_t *apuc,
                                                  baryon_sm_t mask,
                                                  baryon_vr_t *vrs[],
                                                  size_t num_vrs, void *src,
                                                  baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_left_or_right_in_place,
                                    baryon_left_and_right, vrs, num_vrs, src,
                                    src_type);
}

baryon_wordline_map_t *baryon_rl_or_eq_sb_and_inv_src(baryon_apuc_t *apuc,
                                                      baryon_sm_t mask,
                                                      baryon_vr_t *vrs[],
                                                      size_t num_vrs, void *src,
                                                      baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_left_or_right_in_place,
                                    baryon_left_and_inv_right, vrs, num_vrs,
                                    src, src_type);
}

baryon_wordline_map_t *baryon_rl_and_eq_sb_and_src(baryon_apuc_t *apuc,
                                                   baryon_sm_t mask,
                                                   baryon_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_left_and_right_in_place,
                                    baryon_left_and_right, vrs, num_vrs,
                                    src, src_type);
}

baryon_wordline_map_t *
baryon_rl_and_eq_sb_and_inv_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                                baryon_vr_t *vrs[], size_t num_vrs, void *src,
                                baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_left_and_right_in_place,
                                    baryon_left_and_inv_right, vrs, num_vrs,
                                    src, src_type);
}

baryon_wordline_map_t *baryon_rl_xor_eq_sb_and_src(baryon_apuc_t *apuc,
                                                   baryon_sm_t mask,
                                                   baryon_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_left_xor_right_in_place,
                                    baryon_left_and_right, vrs, num_vrs, src,
                                    src_type);
}

baryon_wordline_map_t *
baryon_rl_xor_eq_sb_and_inv_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                                baryon_vr_t *vrs[], size_t num_vrs, void *src,
                                baryon_src_t src_type)
{
  return baryon_rl_op_eq_sb_and_src(apuc, mask, baryon_left_xor_right_in_place,
                                    baryon_left_and_inv_right, vrs, num_vrs,
                                    src, src_type);
}

void baryon_rl_from_sb_binop_gl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                         baryon_vr_t *vrs[], size_t num_vrs,
                                         baryon_binary_op_t op,
                                         baryon_gl_t *gl) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    memcpy(&apuc->rl[section], result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_from_sb_binop_gl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_vr_t *vrs[], size_t num_vrs,
                           baryon_binary_op_t op, baryon_gl_t *gl) {
  if (apuc->in_place) {
    baryon_rl_from_sb_binop_gl_in_place(apuc, mask, vrs, num_vrs, op, gl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

void baryon_rl_from_sb_binop_ggl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                          baryon_vr_t *vrs[], size_t num_vrs,
                                          baryon_binary_op_t op,
                                          baryon_ggl_t *ggl) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = pseudo_gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    memcpy(&apuc->rl[section], result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_from_sb_binop_ggl(baryon_apuc_t *apuc, baryon_sm_t mask,
                            baryon_vr_t *vrs[], size_t num_vrs,
                            baryon_binary_op_t op, baryon_ggl_t *ggl) {
  if (apuc->in_place) {
    baryon_rl_from_sb_binop_ggl_in_place(apuc, mask, vrs, num_vrs, op, ggl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *pseudo_gl = &(*ggl)[section / BARYON_NUM_GROUPS];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = pseudo_gl;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

void baryon_rl_from_sb_binop_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask,
                                         baryon_vr_t *vrs[], size_t num_vrs,
                                         baryon_binary_op_t op,
                                         baryon_rl_t *rl) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *wordline = &(*rl)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = wordline;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    memcpy(&apuc->rl[section], result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_from_sb_binop_rl(baryon_apuc_t *apuc, baryon_sm_t mask,
                           baryon_vr_t *vrs[], size_t num_vrs,
                           baryon_binary_op_t op, baryon_rl_t *rl) {
  if (apuc->in_place) {
    baryon_rl_from_sb_binop_rl_in_place(apuc, mask, vrs, num_vrs, op, rl);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *wordline = &(*rl)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = wordline;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_wordline(sbdata);
  return patch;
}

void baryon_rl_from_sb_binop_rsp16_in_place(baryon_apuc_t *apuc,
                                            baryon_sm_t mask,
                                            baryon_vr_t *vrs[], size_t num_vrs,
                                            baryon_binary_op_t op,
                                            baryon_rsp16_t *rsp16) {
  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *wordline = &(*filtered_brsp16)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = wordline;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    memcpy(&apuc->rl[section], result, BARYON_WORDLINE_SIZE);
    baryon_free_wordline(result);
  });

  baryon_free_vr(filtered_brsp16);
  baryon_free_wordline(sbdata);
}

baryon_wordline_map_t *
baryon_rl_from_sb_binop_rsp16(baryon_apuc_t *apuc, baryon_sm_t mask,
                              baryon_vr_t *vrs[], size_t num_vrs,
                              baryon_binary_op_t op, baryon_rsp16_t *rsp16) {
  if (apuc->in_place) {
    baryon_rl_from_sb_binop_rsp16_in_place(apuc, mask, vrs, num_vrs, op, rsp16);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_wordline_map_t *patch =
      malloc(sizeof(baryon_wordline_map_t) +
             num_sections * sizeof(baryon_wordline_patch_t));
  patch->size = num_sections;

  baryon_wordline_t *sbdata = malloc(sizeof(baryon_wordline_t));

  baryon_brsp16_t *filtered_brsp16 = baryon_brsp16(rsp16);
  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    baryon_wordline_t *wordline = &(*filtered_brsp16)[section];
    baryon_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    baryon_wordline_t *lhs = sbdata;
    baryon_wordline_t *rhs = wordline;
    baryon_wordline_t *result = op(lhs, rhs);
    baryon_rwinh_in_place(apuc, &apuc->rl[section], section, result);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  baryon_free_vr(filtered_brsp16);
  baryon_free_wordline(sbdata);
  return patch;
}

baryon_wordline_map_t *baryon_rl_from_sb_binop_src(
    baryon_apuc_t *apuc, baryon_sm_t mask, baryon_vr_t *vrs[], size_t num_vrs,
    baryon_binary_op_t op, void *src, baryon_src_t src_type) {
  switch (src_type) {
  case BARYON_SRC_GL: // fallthrough
  case BARYON_SRC_INV_GL: {
    return baryon_rl_from_sb_binop_gl(apuc, mask, vrs, num_vrs, op, src);
  }
  case BARYON_SRC_GGL: // fallthrough
  case BARYON_SRC_INV_GGL: {
    return baryon_rl_from_sb_binop_ggl(apuc, mask, vrs, num_vrs, op, src);
  }
  case BARYON_SRC_RL:      // fallthrough
  case BARYON_SRC_NRL:     // fallthrough
  case BARYON_SRC_ERL:     // fallthrough
  case BARYON_SRC_WRL:     // fallthrough
  case BARYON_SRC_SRL:     // fallthrough
  case BARYON_SRC_INV_RL:  // fallthrough
  case BARYON_SRC_INV_NRL: // fallthrough
  case BARYON_SRC_INV_ERL: // fallthrough
  case BARYON_SRC_INV_WRL: // fallthrough
  case BARYON_SRC_INV_SRL: {
    return baryon_rl_from_sb_binop_rl(apuc, mask, vrs, num_vrs, op, src);
  }
  case BARYON_SRC_RSP16: // fallthrough
  case BARYON_SRC_INV_RSP16: {
    return baryon_rl_from_sb_binop_rsp16(apuc, mask, vrs, num_vrs, op, src);
  }
  }
}

baryon_wordline_map_t *
baryon_rl_from_sb_or_src(baryon_apuc_t *apuc, baryon_sm_t mask, baryon_vr_t *vrs[],
                         size_t num_vrs, void *src, baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     baryon_left_or_right, src, src_type);
}

baryon_wordline_map_t *baryon_rl_from_sb_or_inv_src(baryon_apuc_t *apuc,
                                                    baryon_sm_t mask,
                                                    baryon_vr_t *vrs[],
                                                    size_t num_vrs, void *src,
                                                    baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     baryon_left_or_inv_right, src, src_type);
}

baryon_wordline_map_t *baryon_rl_from_sb_xor_src(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask,
                                                 baryon_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     baryon_left_xor_right, src, src_type);
}

baryon_wordline_map_t *baryon_rl_from_sb_xor_inv_src(baryon_apuc_t *apuc,
                                                     baryon_sm_t mask,
                                                     baryon_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     baryon_left_xor_inv_right, src, src_type);
}

baryon_wordline_map_t *baryon_rl_from_inv_sb_and_src(baryon_apuc_t *apuc,
                                                     baryon_sm_t mask,
                                                     baryon_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     baryon_inv_left_and_right, src, src_type);
}

baryon_wordline_map_t *
baryon_rl_from_inv_sb_and_inv_src(baryon_apuc_t *apuc, baryon_sm_t mask,
                                  baryon_vr_t *vrs[], size_t num_vrs, void *src,
                                  baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(
      apuc, mask, vrs, num_vrs, baryon_inv_left_and_inv_right, src, src_type);
}

baryon_wordline_map_t *baryon_rl_from_sb_and_inv_src(baryon_apuc_t *apuc,
                                                     baryon_sm_t mask,
                                                     baryon_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     baryon_src_t src_type) {
  return baryon_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     baryon_left_and_inv_right, src, src_type);
}

void baryon_rsp16_from_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask) {
  size_t step_size = BARYON_NUM_RL_PLATS / BARYON_NUM_RSP16_PLATS;
  size_t num_steps = BARYON_NUM_RSP16_PLATS;
  baryon_foreach_range(step, num_steps, {
    size_t lower = step * step_size;
    size_t upper = lower + step_size;
    baryon_foreach_masked_section(mask, section, {
      baryon_any_plat_in_place(&apuc->rsp16, &apuc->rl,
                               section, step, lower, upper);
    });
  });
}

baryon_rsp16_section_map_t *baryon_rsp16_from_rl(baryon_apuc_t *apuc,
                                                 baryon_sm_t mask) {
  apuc->rsp_mode = BARYON_RSP_MODE_RSP16_READ;

  if (apuc->in_place) {
    baryon_rsp16_from_rl_in_place(apuc, mask);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);
  baryon_rsp16_section_map_t *patch =
      malloc(sizeof(baryon_rsp16_section_map_t) +
             num_sections * sizeof(baryon_rsp16_section_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  baryon_foreach_masked_section(mask, section, {
    patch->updates[nth_update].section = section;
    nth_update += 1;
  });

  size_t step_size = BARYON_NUM_RL_PLATS / BARYON_NUM_RSP16_PLATS;
  size_t num_steps = BARYON_NUM_RSP16_PLATS;
  baryon_foreach_range(step, num_steps, {
    size_t lower = step * step_size;
    size_t upper = lower + step_size;
    size_t nth_update = 0;
    baryon_foreach_masked_section(mask, section, {
      patch->updates[nth_update].update[step] = false;
      baryon_foreach_range(plat, lower, upper, {
        if (apuc->rl[section][plat]) {
          patch->updates[nth_update].update[step] = true;
          break;
        }
      });
      nth_update += 1;
    });
  });

  return patch;
}

void baryon_gl_from_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask) {
  size_t num_sections = baryon_count_masked_sections(mask);

  memset(&apuc->gl, true, BARYON_GL_SIZE);

  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      apuc->gl[plat] &= apuc->rl[section][plat];
    });
  });
}

baryon_gl_t *baryon_gl_from_rl(baryon_apuc_t *apuc, baryon_sm_t mask) {
  if (apuc->in_place) {
    baryon_gl_from_rl_in_place(apuc, mask);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);

  baryon_gl_t *gl = malloc(BARYON_GL_SIZE);
  memset(gl, true, BARYON_GL_SIZE);

  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      (*gl)[plat] &= apuc->rl[section][plat];
    });
  });

  return gl;
}

void baryon_ggl_from_rl_in_place(baryon_apuc_t *apuc, baryon_sm_t mask) {
  size_t num_sections = baryon_count_masked_sections(mask);

  memset(&apuc->ggl, true, BARYON_GGL_SIZE);

  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      apuc->ggl[section / BARYON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });
}

baryon_ggl_t *baryon_ggl_from_rl(baryon_apuc_t *apuc, baryon_sm_t mask) {
  if (apuc->in_place) {
    baryon_ggl_from_rl_in_place(apuc, mask);
    return NULL;
  }

  size_t num_sections = baryon_count_masked_sections(mask);

  baryon_ggl_t *ggl = malloc(BARYON_GGL_SIZE);
  memset(ggl, true, BARYON_GGL_SIZE);

  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
      (*ggl)[section / BARYON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });

  return ggl;
}

void baryon_l1_from_ggl_in_place(baryon_apuc_t *apuc, size_t l1_addr) {
  memcpy(&apuc->l1[l1_addr], &apuc->ggl, BARYON_GGL_SIZE);
}

baryon_l1_patch_t *baryon_l1_from_ggl(baryon_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    baryon_l1_from_ggl_in_place(apuc, l1_addr);
    return NULL;
  }
  baryon_l1_patch_t *patch = malloc(sizeof(baryon_l1_patch_t));
  patch->src = BARYON_L1_SRC_GGL;
  patch->l1_addr = l1_addr;
  patch->ggl_patch = malloc(sizeof(baryon_ggl_t));
  memcpy(patch->ggl_patch, &apuc->ggl, BARYON_GGL_SIZE);
  return patch;
}

void baryon_lgl_from_l1_in_place(baryon_apuc_t *apuc, size_t l1_addr) {
  size_t bank, group, row;
  baryon_bank_group_row(l1_addr, &bank, &group, &row);
  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    apuc->lgl[lgl_plat] = apuc->l1[row][group][l1_plat];
  });
}

baryon_lgl_t *baryon_lgl_from_l1(baryon_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    baryon_lgl_from_l1_in_place(apuc, l1_addr);
    return NULL;
  }

  baryon_lgl_t *lgl = malloc(sizeof(baryon_lgl_t));

  size_t bank, group, row;
  baryon_bank_group_row(l1_addr, &bank, &group, &row);
  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    (*lgl)[lgl_plat] = apuc->l1[row][group][l1_plat];
  });

  return lgl;
}

void baryon_l2_from_lgl_in_place(baryon_apuc_t *apuc, size_t l2_addr) {
  memcpy(&apuc->l2[l2_addr], &apuc->lgl, BARYON_LGL_SIZE);
}

baryon_l2_patch_t *baryon_l2_from_lgl(baryon_apuc_t *apuc, size_t l2_addr) {
  if (apuc->in_place) {
    baryon_l2_from_lgl_in_place(apuc, l2_addr);
    return NULL;
  }
  baryon_l2_patch_t *patch = malloc(sizeof(baryon_l2_patch_t));
  patch->l2_addr = l2_addr;
  patch->update = malloc(sizeof(baryon_l2_t));
  memcpy(patch->update, &apuc->lgl, BARYON_LGL_SIZE);
  return patch;
}

void baryon_lgl_from_l2_in_place(baryon_apuc_t *apuc, size_t l2_addr) {
  memcpy(&apuc->lgl, &apuc->l2[l2_addr], BARYON_LGL_SIZE);
}

baryon_lgl_t *baryon_lgl_from_l2(baryon_apuc_t *apuc, size_t l2_addr) {
  if (apuc->in_place) {
    baryon_lgl_from_l2_in_place(apuc, l2_addr);
    return NULL;
  }
  baryon_lgl_t *lgl = malloc(sizeof(baryon_lgl_t));
  memcpy(lgl, &apuc->l2[l2_addr], BARYON_LGL_SIZE);
  return lgl;
}

void baryon_l1_from_lgl_in_place(baryon_apuc_t *apuc, size_t l1_addr) {
  size_t bank, group, row;
  baryon_bank_group_row(l1_addr, &bank, &group, &row);
  baryon_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    apuc->l1[row][group][l1_plat] = apuc->lgl[lgl_plat];
  });
}

baryon_l1_patch_t *baryon_l1_from_lgl(baryon_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    baryon_l1_from_lgl_in_place(apuc, l1_addr);
    return NULL;
  }
  baryon_l1_patch_t *patch = malloc(sizeof(baryon_l1_patch_t));
  patch->src = BARYON_L1_SRC_LGL;
  patch->l1_addr = l1_addr;
  patch->lgl_patch = malloc(sizeof(baryon_lgl_t));
  memcpy(patch->lgl_patch, &apuc->lgl, BARYON_LGL_SIZE);
  return patch;
}

void baryon_ggl_from_l1_in_place(baryon_apuc_t *apuc, size_t l1_addr) {
  memcpy(&apuc->ggl, &apuc->l1[l1_addr], BARYON_GGL_SIZE);
}

baryon_ggl_t *baryon_ggl_from_l1(baryon_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    baryon_ggl_from_l1_in_place(apuc, l1_addr);
    return NULL;
  }
  baryon_ggl_t *ggl = malloc(sizeof(baryon_ggl_t));
  memcpy(ggl, &apuc->l1[l1_addr], BARYON_GGL_SIZE);
  return ggl;
}

void baryon_ggl_from_rl_and_l1_in_place(baryon_apuc_t *apuc, size_t mask,
                                        size_t l1_addr) {
  baryon_ggl_from_rl_in_place(apuc, mask);
  baryon_foreach_l1_group_plat(group, plat, {
    apuc->ggl[group][plat] &= apuc->l1[l1_addr][group][plat];
  });
}

baryon_ggl_t *baryon_ggl_from_rl_and_l1(baryon_apuc_t *apuc, size_t mask,
                                        size_t l1_addr) {
  if (apuc->in_place) {
    baryon_ggl_from_rl_and_l1_in_place(apuc, mask, l1_addr);
    return NULL;
  }
  baryon_ggl_t *ggl = baryon_ggl_from_rl(apuc, mask);
  baryon_foreach_l1_group_plat(group, plat, {
    (*ggl)[group][plat] &= apuc->l1[l1_addr][group][plat];
  });
  return ggl;
}

void baryon_rwinh_set_in_place(baryon_apuc_t *apuc, size_t mask) {
  apuc->rwinh_sects |= mask;
  baryon_foreach_masked_section(mask, section, {
    memcpy(&apuc->rwinh_filter[section],
           &apuc->rl[section],
           BARYON_WORDLINE_SIZE);
  });
}

size_t baryon_rwinh_set(baryon_apuc_t *apuc, size_t mask) {
  if (apuc->in_place) {
    baryon_rwinh_set_in_place(apuc, mask);
    return 0x0000;
  }
  return mask;
}

void baryon_rwinh_rst_in_place(baryon_apuc_t *apuc, size_t mask, bool has_read) {
  if (!has_read) {
    baryon_foreach_masked_section(mask, section, {
      memcpy(&apuc->rl[section],
             &apuc->rwinh_filter[section],
             BARYON_WORDLINE_SIZE);
    });
  }

  apuc->rwinh_sects &= ~mask;
  baryon_foreach_masked_section(mask, section, {
    memset(&apuc->rwinh_filter[section], true, BARYON_WORDLINE_SIZE);
  });
}

baryon_rwinh_rst_patch_t *baryon_rwinh_rst(baryon_apuc_t *apuc, size_t mask,
                                           bool has_read) {
  if (apuc->in_place) {
    baryon_rwinh_rst_in_place(apuc, mask, has_read);
    return NULL;
  }
  baryon_rwinh_rst_patch_t *patch = malloc(sizeof(baryon_rwinh_rst_patch_t));
  patch->mask = mask;
  patch->has_read = has_read;
  return patch;
}

void baryon_rwinh_in_place(baryon_apuc_t *apuc, baryon_wordline_t *wordline,
                           size_t section, baryon_wordline_t *result) {
  if (apuc->rwinh_sects != 0x0000) {
    baryon_wordline_t *filter = &apuc->rwinh_filter[section];
    baryon_wordline_t *filtered = \
      baryon_left_and_right_in_place(result, filter, result);
    baryon_wordline_t *unfiltered = \
      baryon_left_and_inv_right(wordline, filter);
    baryon_left_or_right_in_place(filtered, unfiltered, result);
    baryon_free_wordline(unfiltered);
  }
}
