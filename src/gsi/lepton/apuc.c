#include <string.h>

#include "apuc.h"
#include "operations.h"

const char *lepton_l1_patch_src_name(lepton_l1_patch_src l1_patch_src_type) {
  switch (l1_patch_src_type) {
  case LEPTON_L1_SRC_GGL:
    return "GGL";
  case LEPTON_L1_SRC_LGL:
    return "LGL";
  }
}

const char *lepton_src_name(lepton_src_t src_type) {
  switch (src_type) {
  case LEPTON_SRC_RL:
    return "RL";
  case LEPTON_SRC_NRL:
    return "NRL";
  case LEPTON_SRC_ERL:
    return "ERL";
  case LEPTON_SRC_WRL:
    return "WRL";
  case LEPTON_SRC_SRL:
    return "SRL";
  case LEPTON_SRC_INV_RL:
    return "INV_RL";
  case LEPTON_SRC_INV_NRL:
    return "INV_NRL";
  case LEPTON_SRC_INV_ERL:
    return "INV_ERL";
  case LEPTON_SRC_INV_WRL:
    return "INV_WRL";
  case LEPTON_SRC_INV_SRL:
    return "INV_SRL";
  case LEPTON_SRC_GGL:
    return "GGL";
  case LEPTON_SRC_INV_GGL:
    return "INV_GGL";
  case LEPTON_SRC_GL:
    return "GL";
  case LEPTON_SRC_INV_GL:
    return "INV_GL";
  case LEPTON_SRC_RSP16:
    return "RSP16";
  case LEPTON_SRC_INV_RSP16:
    return "INV_RSP16";
  }
}

void lepton_plats_for_bank(size_t bank, size_t *lower_plat_apc_0,
                           size_t *upper_plat_apc_0, size_t *lower_plat_apc_1,
                           size_t *upper_plat_apc_1) {
  // 1 low-order and 1 high-order half-bank per APC
  // DIRI orders low- and high-order half-banks consecutively
  // 2 APCs per APUC
  // .:. Need to slice 2 ranges of 2 half-banks
  *lower_plat_apc_0 = bank * LEPTON_NUM_PLATS_PER_HALF_BANK * 2;
  *upper_plat_apc_0 = (bank + 1) * LEPTON_NUM_PLATS_PER_HALF_BANK * 2;
  *lower_plat_apc_1 = (*lower_plat_apc_0) + LEPTON_NUM_PLATS_PER_APC;
  *upper_plat_apc_1 = (*upper_plat_apc_0) + LEPTON_NUM_PLATS_PER_APC;
}

void lepton_patch_whole_vr(lepton_apuc_t *apuc, lepton_vr_patch_t *patch) {
  lepton_vr_t *vr = patch->vr;
  lepton_vr_t *update = patch->update;
  if (update == NULL) {
    lepton_init_vr(vr, false);
  }
  else {
    memcpy(vr, update, LEPTON_VR_SIZE);
  }
}

void lepton_patch_sb(lepton_apuc_t *apuc, lepton_wordline_map_t *patch) {
  lepton_foreach_range(i, patch->size, {
    lepton_wordline_patch_t *section_patch = &patch->updates[i];
    lepton_vr_t *vr = section_patch->vr;
    size_t section = section_patch->section;
    lepton_wordline_t *update = section_patch->update;
    memcpy(&(*vr)[section], update, LEPTON_WORDLINE_SIZE);
  });
}

void lepton_patch_gl(lepton_apuc_t *apuc, lepton_gl_t *patch) {
  if (patch != NULL) {
    memcpy(&apuc->gl, patch, LEPTON_GL_SIZE);
  }
  else {
    lepton_init_gl(&apuc->gl, false);
  }
}

void lepton_patch_ggl(lepton_apuc_t *apuc, lepton_ggl_t *patch) {
  if (patch != NULL) {
    memcpy(&apuc->ggl, patch, LEPTON_GGL_SIZE);
  }
  else {
    lepton_init_ggl(&apuc->ggl, false);
  }
}

void lepton_patch_lgl(lepton_apuc_t *apuc, lepton_lgl_t *patch) {
  if (patch != NULL) {
    memcpy(&apuc->lgl, patch, LEPTON_LGL_SIZE);
  }
  else {
    lepton_init_lgl(&apuc->lgl, false);
  }
}

void lepton_patch_whole_l1(lepton_apuc_t *apuc,
                           lepton_l1_t (*patch)[LEPTON_NUM_L1_ROWS]) {
  if (patch == NULL) {
    memset(&apuc->l1, false, LEPTON_NUM_L1_ROWS * LEPTON_L1_SIZE);
  }
  else {
    memcpy(&apuc->l1, patch, LEPTON_NUM_L1_ROWS * LEPTON_L1_SIZE);
  }
}

void lepton_patch_l1(lepton_apuc_t *apuc, lepton_l1_patch_t *patch) {
  size_t l1_addr = patch->l1_addr;
  switch (patch->src) {
  case LEPTON_L1_SRC_GGL: {
    memcpy(&apuc->l1[l1_addr], patch->ggl_patch, LEPTON_GGL_SIZE);
    break;
  }
  case LEPTON_L1_SRC_LGL: {
    size_t bank, group, row;
    lepton_bank_group_row(l1_addr, &bank, &group, &row);
    lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
      apuc->l1[row][group][l1_plat] = (*patch->lgl_patch)[lgl_plat];
    });
    break;
  }
  }
}

void lepton_patch_whole_l2(lepton_apuc_t *apuc,
                           lepton_l2_t (*patch)[LEPTON_NUM_L2_ROWS]) {
  if (patch == NULL) {
    memset(&apuc->l2, false, LEPTON_NUM_L2_ROWS * LEPTON_L2_SIZE);
  }
  else {
    memcpy(&apuc->l2, patch, LEPTON_NUM_L2_ROWS * LEPTON_L2_SIZE);
  }
}

void lepton_patch_l2(lepton_apuc_t *apuc, lepton_l2_patch_t *patch) {
  size_t l2_addr = patch->l2_addr;
  memcpy(&apuc->l2[l2_addr], patch->update, LEPTON_L2_SIZE);
}

void lepton_patch_rsp16(lepton_apuc_t *apuc, lepton_rsp16_t *patch) {
  memcpy(&apuc->rsp16, patch, LEPTON_RSP16_SIZE);
}

void lepton_patch_partial_rsp16(lepton_apuc_t *apuc,
                                lepton_rsp16_section_map_t *patch) {
  lepton_foreach_range(i, patch->size, {
    lepton_rsp16_section_patch_t *section_patch = &patch->updates[i];
    size_t section = section_patch->section;
    lepton_rsp16_section_t *update = &section_patch->update;
    memcpy(&apuc->rsp16[section], update, LEPTON_RSP16_SECTION_SIZE);
  });
}

void lepton_patch_rsp256(lepton_apuc_t *apuc, lepton_rsp256_t *patch) {
  memcpy(&apuc->rsp256, patch, LEPTON_RSP256_SIZE);
}

void lepton_patch_rsp2k(lepton_apuc_t *apuc, lepton_rsp2k_t *patch) {
  memcpy(&apuc->rsp2k, patch, LEPTON_RSP2K_SIZE);
}

void lepton_patch_rsp32k(lepton_apuc_t *apuc, lepton_rsp32k_t *patch) {
  memcpy(&apuc->rsp32k, patch, LEPTON_RSP32K_SIZE);
}

void lepton_patch_rsps(lepton_apuc_t *apuc, lepton_rsp_patches_t *patches) {
  if (patches != NULL && patches->rsp16_update != NULL) {
    lepton_patch_rsp16(apuc, patches->rsp16_update);
  }
  else {
    lepton_init_rsp16(&apuc->rsp16, false);
  }

  if (patches != NULL && patches->rsp256_update != NULL) {
    lepton_patch_rsp256(apuc, patches->rsp256_update);
  }
  else {
    lepton_init_rsp256(&apuc->rsp256, false);
  }

  if (patches != NULL && patches->rsp2k_update != NULL) {
    lepton_patch_rsp2k(apuc, patches->rsp2k_update);
  }
  else {
    lepton_init_rsp2k(&apuc->rsp2k, false);
  }

  if (patches != NULL && patches->rsp32k_update != NULL) {
    lepton_patch_rsp32k(apuc, patches->rsp32k_update);
  }
  else {
    lepton_init_rsp32k(&apuc->rsp32k, false);
  }
}

void lepton_patch_noop(lepton_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void lepton_patch_rsp_end(lepton_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void lepton_patch_rsp_start_ret(lepton_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void lepton_patch_l2_end(lepton_apuc_t *apuc, void *patch) {
  // nothing to do, for now
}

void lepton_patch_rwinh_set(lepton_apuc_t *apuc, lepton_sm_t mask) {
  lepton_rwinh_set_in_place(apuc, mask);
}

void lepton_patch_rwinh_rst(lepton_apuc_t *apuc,
                            lepton_rwinh_rst_patch_t *patch) {
  lepton_rwinh_rst_in_place(apuc, patch->mask, patch->has_read);
}

void lepton_init_vrs(lepton_vr_t (*vrs)[LEPTON_NUM_SBS], bool value) {
  memset(vrs, false, LEPTON_NUM_SBS * LEPTON_VR_SIZE);
}

void lepton_init_vr(lepton_vr_t *vr, bool value) {
  memset(vr, value, LEPTON_VR_SIZE);
}

void lepton_init_gl(lepton_gl_t *gl, bool value) {
  memset(gl, value, LEPTON_GL_SIZE);
}

void lepton_init_ggl(lepton_ggl_t *ggl, bool value) {
  memset(ggl, value, LEPTON_GGL_SIZE);
}

void lepton_init_rsp16(lepton_rsp16_t *rsp16, bool value) {
  memset(rsp16, value, LEPTON_RSP16_SIZE);
}

void lepton_init_rsp256(lepton_rsp256_t *rsp256, bool value) {
  memset(rsp256, value, LEPTON_RSP256_SIZE);
}

void lepton_init_rsp2k(lepton_rsp2k_t *rsp2k, bool value) {
  memset(rsp2k, value, LEPTON_RSP2K_SIZE);
}

void lepton_init_rsp32k(lepton_rsp32k_t *rsp32k, bool value) {
  memset(rsp32k, value, LEPTON_RSP32K_SIZE);
}

void lepton_init_l1(lepton_l1_t *l1, bool value) {
  memset(l1, value, LEPTON_L1_SIZE);
}

void lepton_init_l2(lepton_l2_t *l2, bool value) {
  memset(l2, value, LEPTON_L2_SIZE);
}

void lepton_init_lgl(lepton_lgl_t *lgl, bool value) {
  memset(lgl, value, LEPTON_LGL_SIZE);
}

void lepton_init_apuc(lepton_apuc_t *apuc) {
  apuc->in_place = true;

  lepton_init_vrs(&apuc->vrs, false);

  lepton_reset_rl(apuc);
  lepton_reset_gl(apuc);
  lepton_reset_ggl(apuc);

  lepton_reset_rsp16(apuc);
  lepton_reset_rsp256(apuc);
  lepton_reset_rsp2k(apuc);
  lepton_reset_rsp32k(apuc);

  lepton_reset_l1(apuc);
  lepton_reset_l2(apuc);
  lepton_reset_lgl(apuc);

  lepton_init_vr(&apuc->rwinh_filter, true);
  apuc->rwinh_sects = 0x0000;
}

void lepton_free_apuc(lepton_apuc_t *apuc) {
  if (apuc != NULL) {
    free(apuc);
  }
}

void lepton_free_vr(lepton_vr_t *vr) {
  if (vr != NULL) {
    free(vr);
  }
}

void lepton_free_rl(lepton_rl_t *rl) {
  if (rl != NULL) {
    free(rl);
  }
}

void lepton_free_gl(lepton_gl_t *gl) {
  if (gl != NULL) {
    free(gl);
  }
}

void lepton_free_ggl(lepton_ggl_t *ggl) {
  if (ggl != NULL) {
    free(ggl);
  }
}

void lepton_free_rsp16(lepton_rsp16_t *rsp16) {
  if (rsp16 != NULL) {
    free(rsp16);
  }
}

void lepton_free_rsp256(lepton_rsp256_t *rsp256) {
  if (rsp256 != NULL) {
    free(rsp256);
  }
}

void lepton_free_rsp2k(lepton_rsp2k_t *rsp2k) {
  if (rsp2k != NULL) {
    free(rsp2k);
  }
}

void lepton_free_rsp32k(lepton_rsp32k_t *rsp32k) {
  if (rsp32k != NULL) {
    free(rsp32k);
  }
}

void lepton_free_l1(lepton_l1_t *l1) {
  if (l1 != NULL) {
    free(l1);
  }
}

void lepton_free_l2(lepton_l2_t *l2) {
  if (l2 != NULL) {
    free(l2);
  }
}

void lepton_free_lgl(lepton_lgl_t *lgl) {
  if (lgl != NULL) {
    free(lgl);
  }
}

void lepton_free_wordline(lepton_wordline_t *wordline) {
  if (wordline != NULL) {
    free(wordline);
  }
}

void lepton_free_rsp16_section(lepton_rsp16_section_t *rsp16_section) {
  if (rsp16_section != NULL) {
    free(rsp16_section);
  }
}

void lepton_free_vr_patch(lepton_vr_patch_t *patch) {
  if (patch != NULL) {
    lepton_free_vr(patch->vr);
    lepton_free_vr(patch->update);
    free(patch);
  }
}

void lepton_free_wordline_patch(lepton_wordline_patch_t *patch) {
  if (patch != NULL) {
    // NOTE: Do not free patch->vr because it points to memory in apuc.
    /* lepton_free_vr(patch->vr); */
    lepton_free_wordline(patch->update);
    free(patch);
  }
}

void lepton_free_wordline_map(lepton_wordline_map_t *patches) {
  if (patches != NULL) {
    lepton_foreach_range(i, patches->size, {
      lepton_wordline_patch_t *patch = &patches->updates[i];
      lepton_free_wordline(patch->update);
    });
    free(patches);
  }
}

void lepton_free_l1_patch(lepton_l1_patch_t *patch) {
  if (patch != NULL) {
    switch (patch->src) {
    case LEPTON_L1_SRC_GGL:
      lepton_free_ggl(patch->ggl_patch);
      break;
    case LEPTON_L1_SRC_LGL:
      lepton_free_lgl(patch->lgl_patch);
      break;
    }
    free(patch);
  }
}

void lepton_free_l2_patch(lepton_l2_patch_t *patch) {
  if (patch != NULL) {
    lepton_free_l2(patch->update);
    free(patch);
  }
}

void lepton_free_rsp16_section_patch(lepton_rsp16_section_patch_t *patch) {
  if (patch != NULL) {
    free(patch);
  }
}

void lepton_free_rsp16_section_map(lepton_rsp16_section_map_t *patch) {
  if (patch != NULL) {
    free(patch);
  }
}

void lepton_free_rsp_patches(lepton_rsp_patches_t *patch) {
  if (patch != NULL) {
    lepton_free_rsp16(patch->rsp16_update);
    lepton_free_rsp256(patch->rsp256_update);
    lepton_free_rsp2k(patch->rsp2k_update);
    lepton_free_rsp32k(patch->rsp32k_update);
    free(patch);
  }
}

void lepton_free_rwinh_rst_patch(lepton_rwinh_rst_patch_t *patch) {
  if (patch != NULL) {
    free(patch);
  }
}

void lepton_reset_rl_in_place(lepton_apuc_t *apuc) {
  lepton_init_vr(&apuc->rl, false);
}

lepton_vr_patch_t *lepton_reset_rl(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_rl_in_place(apuc);
    return NULL;
  }

  lepton_vr_patch_t *patch = malloc(sizeof(lepton_vr_patch_t));
  patch->vr = &apuc->rl;
  patch->update = NULL;
  return patch;
}

void lepton_reset_gl_in_place(lepton_apuc_t *apuc) {
  lepton_init_gl(&apuc->gl, false);
}

lepton_gl_t *lepton_reset_gl(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_gl_in_place(apuc);
  }
  return NULL;
}

void lepton_reset_ggl_in_place(lepton_apuc_t *apuc) {
  lepton_init_ggl(&apuc->ggl, false);
}

lepton_ggl_t *lepton_reset_ggl(lepton_apuc_t *apuc)
{
  if (apuc->in_place) {
    lepton_reset_ggl_in_place(apuc);
  }
  return NULL;
}

void lepton_reset_rsp16_in_place(lepton_apuc_t *apuc) {
  lepton_init_rsp16(&apuc->rsp16, false);
}

lepton_rsp16_t *lepton_reset_rsp16(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_rsp16_in_place(apuc);
  }
  return NULL;
}

void lepton_reset_rsp256_in_place(lepton_apuc_t *apuc) {
  lepton_init_rsp256(&apuc->rsp256, false);
}

lepton_rsp256_t *lepton_reset_rsp256(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_rsp256_in_place(apuc);
  }
  return NULL;
}

void lepton_reset_rsp2k_in_place(lepton_apuc_t *apuc) {
  lepton_init_rsp2k(&apuc->rsp2k, false);
}

lepton_rsp2k_t *lepton_reset_rsp2k(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_rsp2k_in_place(apuc);
  }
  return NULL;
}

void lepton_reset_rsp32k_in_place(lepton_apuc_t *apuc) {
  lepton_init_rsp32k(&apuc->rsp32k, false);
}

lepton_rsp32k_t *lepton_reset_rsp32k(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_rsp32k_in_place(apuc);
  }
  return NULL;
}

void lepton_reset_l1_in_place(lepton_apuc_t *apuc) {
  memset(&apuc->l1, false, LEPTON_NUM_L1_ROWS * LEPTON_L1_SIZE);
}

lepton_l1_t (*lepton_reset_l1(lepton_apuc_t *apuc))[LEPTON_NUM_L1_ROWS] {
  if (apuc->in_place) {
    lepton_reset_l1_in_place(apuc);
  }

  return NULL;
}

void lepton_reset_l2_in_place(lepton_apuc_t *apuc) {
  memset(&apuc->l2, false, LEPTON_NUM_L2_ROWS * LEPTON_L2_SIZE);
}

lepton_l2_t (*lepton_reset_l2(lepton_apuc_t *apuc))[LEPTON_NUM_L2_ROWS] {
  if (apuc->in_place) {
    lepton_reset_l2_in_place(apuc);
  }

  return NULL;
}

void lepton_reset_lgl_in_place(lepton_apuc_t *apuc) {
  lepton_init_lgl(&apuc->lgl, false);
}

lepton_lgl_t *lepton_reset_lgl(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_reset_lgl_in_place(apuc);
  }

  return NULL;
}

void lepton_bank_group_row(size_t l1_addr, size_t *bank, size_t *group,
                           size_t *row) {
  *bank = (l1_addr >> 11) & 0x3;
  *group = (l1_addr >> 9) & 0x3;
  *row = l1_addr & 0x1FF;
}

void lepton_rsp16_from_rsp256_in_place(lepton_apuc_t *apuc) {
  lepton_rsp16_t *rsp_left = &apuc->rsp16;
  lepton_rsp256_t *rsp_right = &apuc->rsp256;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP16_PLATS,
                      LEPTON_NUM_RSP256_PLATS);
}

lepton_rsp16_t *lepton_rsp16_from_rsp256(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp16_from_rsp256_in_place(apuc);
    return NULL;
  }

  lepton_rsp16_t *rsp_left = malloc(sizeof(lepton_rsp16_t));
  lepton_rsp256_t *rsp_right = &apuc->rsp256;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP16_PLATS,
                      LEPTON_NUM_RSP256_PLATS);

  return rsp_left;
}

void lepton_rsp256_from_rsp16_in_place(lepton_apuc_t *apuc) {
  lepton_rsp256_t *rsp_left = &apuc->rsp256;
  lepton_rsp16_t *rsp_right = &apuc->rsp16;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP256_PLATS,
                      LEPTON_NUM_RSP16_PLATS);
}

lepton_rsp256_t *lepton_rsp256_from_rsp16(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp256_from_rsp16_in_place(apuc);
    return NULL;
  }

  lepton_rsp256_t *rsp_left = malloc(sizeof(lepton_rsp256_t));
  lepton_rsp16_t *rsp_right = &apuc->rsp16;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP256_PLATS,
                      LEPTON_NUM_RSP16_PLATS);

  return rsp_left;
}

void lepton_rsp256_from_rsp2k_in_place(lepton_apuc_t *apuc) {
  lepton_rsp256_t *rsp_left = &apuc->rsp256;
  lepton_rsp2k_t *rsp_right = &apuc->rsp2k;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP256_PLATS,
                      LEPTON_NUM_RSP2K_PLATS);
}

lepton_rsp256_t *lepton_rsp256_from_rsp2k(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp256_from_rsp2k_in_place(apuc);
    return NULL;
  }

  lepton_rsp256_t *rsp_left = malloc(sizeof(lepton_rsp256_t));
  lepton_rsp2k_t *rsp_right = &apuc->rsp2k;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP256_PLATS,
                      LEPTON_NUM_RSP2K_PLATS);

  return rsp_left;
}

void lepton_rsp2k_from_rsp256_in_place(lepton_apuc_t *apuc) {
  lepton_rsp2k_t *rsp_left = &apuc->rsp2k;
  lepton_rsp256_t *rsp_right = &apuc->rsp256;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP2K_PLATS,
                      LEPTON_NUM_RSP256_PLATS);
}

lepton_rsp2k_t *lepton_rsp2k_from_rsp256(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp2k_from_rsp256_in_place(apuc);
    return NULL;
  }

  lepton_rsp2k_t *rsp_left = malloc(sizeof(lepton_rsp2k_t));
  lepton_rsp256_t *rsp_right = &apuc->rsp256;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP2K_PLATS,
                      LEPTON_NUM_RSP256_PLATS);

  return rsp_left;
}

void lepton_rsp2k_from_rsp32k_in_place(lepton_apuc_t *apuc) {
  lepton_rsp2k_t *rsp_left = &apuc->rsp2k;
  lepton_rsp32k_t *rsp_right = &apuc->rsp32k;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP2K_PLATS,
                      LEPTON_NUM_RSP32K_PLATS);
}

lepton_rsp2k_t *lepton_rsp2k_from_rsp32k(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp2k_from_rsp32k_in_place(apuc);
    return NULL;
  }

  lepton_rsp2k_t *rsp_left = malloc(sizeof(lepton_rsp2k_t));
  lepton_rsp32k_t *rsp_right = &apuc->rsp32k;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP2K_PLATS,
                      LEPTON_NUM_RSP32K_PLATS);

  return rsp_left;
}

void lepton_rsp32k_from_rsp2k_in_place(lepton_apuc_t *apuc) {
  lepton_rsp32k_t *rsp_left = &apuc->rsp32k;
  lepton_rsp2k_t *rsp_right = &apuc->rsp2k;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP32K_PLATS,
                      LEPTON_NUM_RSP2K_PLATS);
}

lepton_rsp32k_t *lepton_rsp32k_from_rsp2k(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp32k_from_rsp2k_in_place(apuc);
    return NULL;
  }

  lepton_rsp32k_t *rsp_left = malloc(sizeof(lepton_rsp32k_t));
  lepton_rsp2k_t *rsp_right = &apuc->rsp2k;
  lepton_rsp_from_rsp(rsp_left, rsp_right,
                      LEPTON_NUM_RSP32K_PLATS,
                      LEPTON_NUM_RSP2K_PLATS);

  return rsp_left;
}

void lepton_noop_in_place(lepton_apuc_t *apuc) {
  // nothing to do
}

void *lepton_noop(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_noop_in_place(apuc);
  }
  return NULL;
}

void lepton_fsel_noop_in_place(lepton_apuc_t *apuc) {
  // nothing to do
}

void *lepton_fsel_noop(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_fsel_noop_in_place(apuc);
  }
  return NULL;
}

void lepton_rsp_end_in_place(lepton_apuc_t *apuc) {
  lepton_init_rsp16(&apuc->rsp16, false);
  lepton_init_rsp256(&apuc->rsp256, false);
  lepton_init_rsp2k(&apuc->rsp2k, false);
  lepton_init_rsp32k(&apuc->rsp32k, false);
}

lepton_rsp_patches_t *lepton_rsp_end(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp_end_in_place(apuc);
  }
  return NULL;
}

void lepton_rsp_start_ret_in_place(lepton_apuc_t *apuc) {
  // nothing to do
}

void *lepton_rsp_start_ret(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_rsp_start_ret_in_place(apuc);
  }
  return NULL;
}

void lepton_l2_end_in_place(lepton_apuc_t *apuc) {
  // nothing to do
}

void *lepton_l2_end(lepton_apuc_t *apuc) {
  if (apuc->in_place) {
    lepton_l2_end_in_place(apuc);
  }
  return NULL;
}

static inline void lepton_invert_rl(lepton_rl_t *tgt, lepton_rl_t *src) {
  lepton_foreach_rl_section_plat(section, plat, {
    (*tgt)[section][plat] = !(*src)[section][plat];
  });
}

lepton_rl_t *lepton_rl(lepton_apuc_t *apuc) {
  lepton_rl_t *rl = malloc(sizeof(lepton_rl_t));
  memcpy(rl, &apuc->rl, LEPTON_RL_SIZE);
  return rl;
}

lepton_rl_t *lepton_nrl(lepton_apuc_t *apuc) {
  lepton_rl_t *nrl = malloc(sizeof(lepton_rl_t));
  lepton_foreach_rl_plat(plat, {
    (*nrl)[0][plat] = false;
  });
  lepton_foreach_range(section, 1, LEPTON_NUM_SECTIONS, {
    lepton_foreach_rl_plat(plat, {
      (*nrl)[section][plat] = apuc->rl[section - 1][plat];
    });
  });
  return nrl;
}

lepton_rl_t *lepton_erl(lepton_apuc_t *apuc) {
  lepton_rl_t *erl = malloc(sizeof(lepton_rl_t));
  lepton_foreach_half_bank(half_bank, {
    size_t lower = half_bank * LEPTON_NUM_PLATS_PER_HALF_BANK;
    size_t upper = lower + LEPTON_NUM_PLATS_PER_HALF_BANK;
    lepton_foreach_rl_section(section, {
      (*erl)[section][upper - 1] = false;
      lepton_foreach_range(plat, lower, upper - 1, {
        (*erl)[section][plat] = apuc->rl[section][plat + 1];
      });
    });
  });
  return erl;
}

lepton_rl_t *lepton_wrl(lepton_apuc_t *apuc) {
  lepton_rl_t *wrl = malloc(sizeof(lepton_rl_t));
  lepton_foreach_half_bank(half_bank, {
    size_t lower = half_bank * LEPTON_NUM_PLATS_PER_HALF_BANK;
    size_t upper = lower + LEPTON_NUM_PLATS_PER_HALF_BANK;
    lepton_foreach_rl_section(section, {
      (*wrl)[section][lower] = false;
      lepton_foreach_range(plat, lower + 1, upper, {
        (*wrl)[section][plat] = apuc->rl[section][plat - 1];
      });
    });
  });
  return wrl;
}

lepton_rl_t *lepton_srl(lepton_apuc_t *apuc) {
  lepton_rl_t *srl = malloc(sizeof(lepton_rl_t));
  lepton_foreach_rl_plat(plat, {
    (*srl)[LEPTON_NUM_SECTIONS - 1][plat] = false;
  });
  lepton_foreach_range(section, LEPTON_NUM_SECTIONS - 1, {
    lepton_foreach_rl_plat(plat, {
      (*srl)[section][plat] = apuc->rl[section + 1][plat];
    });
  });
  return srl;
}

lepton_rl_t *lepton_inv_rl(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_rl = malloc(sizeof(lepton_rl_t));
  lepton_invert_rl(inv_rl, &apuc->rl);
  return inv_rl;
}

lepton_rl_t *lepton_inv_nrl(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_nrl = lepton_nrl(apuc);
  lepton_invert_rl(inv_nrl, inv_nrl);
  return inv_nrl;
}

lepton_rl_t *lepton_inv_erl(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_erl = lepton_erl(apuc);
  lepton_invert_rl(inv_erl, inv_erl);
  return inv_erl;
}

lepton_rl_t *lepton_inv_wrl(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_wrl = lepton_wrl(apuc);
  lepton_invert_rl(inv_wrl, inv_wrl);
  return inv_wrl;
}

lepton_rl_t *lepton_inv_srl(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_srl = lepton_srl(apuc);
  lepton_invert_rl(inv_srl, inv_srl);
  return inv_srl;
}

lepton_gl_t *lepton_gl(lepton_apuc_t *apuc) {
  lepton_gl_t *gl = malloc(sizeof(lepton_gl_t));
  memcpy(gl, &apuc->gl, LEPTON_GL_SIZE);
  return gl;
}

lepton_gl_t *lepton_inv_gl(lepton_apuc_t *apuc) {
  lepton_gl_t *inv_gl = malloc(sizeof(lepton_gl_t));
  lepton_foreach_gl_plat(plat, {
    (*inv_gl)[plat] = !apuc->gl[plat];
  });
  return inv_gl;
}

lepton_ggl_t *lepton_ggl(lepton_apuc_t *apuc) {
  lepton_ggl_t *ggl = malloc(sizeof(lepton_ggl_t));
  memcpy(ggl, &apuc->ggl, LEPTON_GGL_SIZE);
  return ggl;
}

lepton_ggl_t *lepton_inv_ggl(lepton_apuc_t *apuc) {
  lepton_ggl_t *inv_ggl = malloc(sizeof(lepton_ggl_t));
  lepton_foreach_ggl_group_plat(group, plat, {
    (*inv_ggl)[group][plat] = !apuc->ggl[group][plat];
  });
  return inv_ggl;
}

lepton_rsp16_t *lepton_rsp16(lepton_apuc_t *apuc) {
  lepton_rsp16_t *rsp16 = malloc(sizeof(lepton_rsp16_t));
  memcpy(rsp16, &apuc->rsp16, LEPTON_RSP16_SIZE);
  return rsp16;
}

lepton_rsp16_t *lepton_inv_rsp16(lepton_apuc_t *apuc) {
  lepton_rsp16_t *inv_rsp16 = malloc(sizeof(lepton_rsp16_t));
  lepton_foreach_rsp16_section_plat(section, plat, {
    (*inv_rsp16)[section][plat] = !apuc->rsp16[section][plat];
  });
  return inv_rsp16;
}

void *lepton_src(lepton_apuc_t *apuc, lepton_src_t src_type) {
  switch (src_type) {
  case LEPTON_SRC_RL:
    return lepton_rl(apuc);
  case LEPTON_SRC_NRL:
    return lepton_nrl(apuc);
  case LEPTON_SRC_ERL:
    return lepton_erl(apuc);
  case LEPTON_SRC_WRL:
    return lepton_wrl(apuc);
  case LEPTON_SRC_SRL:
    return lepton_srl(apuc);
  case LEPTON_SRC_INV_RL:
    return lepton_inv_rl(apuc);
  case LEPTON_SRC_INV_NRL:
    return lepton_inv_nrl(apuc);
  case LEPTON_SRC_INV_ERL:
    return lepton_inv_erl(apuc);
  case LEPTON_SRC_INV_WRL:
    return lepton_inv_wrl(apuc);
  case LEPTON_SRC_INV_SRL:
    return lepton_inv_srl(apuc);
  case LEPTON_SRC_GGL:
    return lepton_ggl(apuc);
  case LEPTON_SRC_INV_GGL:
    return lepton_inv_ggl(apuc);
  case LEPTON_SRC_GL:
    return lepton_gl(apuc);
  case LEPTON_SRC_INV_GL:
    return lepton_inv_gl(apuc);
  case LEPTON_SRC_RSP16:
    return lepton_rsp16(apuc);
  case LEPTON_SRC_INV_RSP16:
    return lepton_inv_rsp16(apuc);
  }
}

void lepton_free_src(void *src, lepton_src_t src_type) {
  switch (src_type) {
  case LEPTON_SRC_RL:      // fallthrough
  case LEPTON_SRC_NRL:     // fallthrough
  case LEPTON_SRC_ERL:     // fallthrough
  case LEPTON_SRC_WRL:     // fallthrough
  case LEPTON_SRC_SRL:     // fallthrough
  case LEPTON_SRC_INV_RL:  // fallthrough
  case LEPTON_SRC_INV_NRL: // fallthrough
  case LEPTON_SRC_INV_ERL: // fallthrough
  case LEPTON_SRC_INV_WRL: // fallthrough
  case LEPTON_SRC_INV_SRL:
    lepton_free_rl((lepton_rl_t *)src);
    break;
  case LEPTON_SRC_GGL: // fallthrough
  case LEPTON_SRC_INV_GGL:
    lepton_free_ggl((lepton_ggl_t *)src);
    break;
  case LEPTON_SRC_GL: // fallthrough
  case LEPTON_SRC_INV_GL:
    lepton_free_gl((lepton_gl_t *)src);
    break;
  case LEPTON_SRC_RSP16: // fallthrough
  case LEPTON_SRC_INV_RSP16:
    lepton_free_rsp16((lepton_rsp16_t *)src);
    break;
  }
}

lepton_gl_t *lepton_ternary_expr(lepton_apuc_t *apuc,
                                 lepton_gl_t *nth1,
                                 lepton_gl_t *nth2,
                                 lepton_gl_t *nth3,
                                 lepton_ternary_op_t op1,
                                 lepton_binary_op_t op2) {
  lepton_gl_t *result = op2(nth2, nth3);
  op1(nth1, result, result);
  return result;
}

size_t lepton_count_masked_sections(lepton_sm_t mask) {
  size_t num_masked_sections = 0;
  lepton_foreach_masked_section(mask, section, {
    num_masked_sections += 1;
  });
  return num_masked_sections;
}

lepton_brsp16_t *lepton_brsp16(lepton_rsp16_t *rsp16) {
  lepton_vr_t *brsp16 = malloc(sizeof(lepton_vr_t));
  lepton_foreach_rsp16_plat(rsp16_plat, {
    size_t lower = rsp16_plat * 16;
    size_t upper = lower + 16;
    lepton_foreach_range(vr_plat, lower, upper, {
      lepton_foreach_rsp16_section(section, {
        (*brsp16)[section][vr_plat] = (*rsp16)[section][rsp16_plat];
      });
    });
  });
  return brsp16;
}

void lepton_sb_op_eq_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_vr_t *vrs[], size_t num_vrs,
                                 lepton_binary_op_t op, lepton_gl_t *gl) {
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(gl, filter);
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
      lepton_free_wordline(result);
    });
    lepton_free_wordline(rhs);
  });
}

lepton_wordline_map_t *lepton_sb_op_eq_gl(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs,
                                          lepton_binary_op_t op,
                                          lepton_gl_t *gl) {
  if (apuc->in_place) {
    lepton_sb_op_eq_gl_in_place(apuc, mask, vrs, num_vrs, op, gl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_vrs * num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(gl, filter);
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
    lepton_free_wordline(rhs);
  });

  return patch;
}

void lepton_sb_op_eq_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                  lepton_vr_t *vrs[], size_t num_vrs,
                                  lepton_binary_op_t op, lepton_ggl_t *ggl) {
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(pseudo_gl, filter);
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
      lepton_free_wordline(result);
    });
    lepton_free_wordline(rhs);
  });
}

lepton_wordline_map_t *lepton_sb_op_eq_ggl(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           lepton_binary_op_t op,
                                           lepton_ggl_t *ggl) {
  if (apuc->in_place) {
    lepton_sb_op_eq_ggl_in_place(apuc, mask, vrs, num_vrs, op, ggl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_vrs * num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs =
      lepton_left_and_right(pseudo_gl, filter);
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
    lepton_free_wordline(rhs);
  });

  return patch;
}

void lepton_sb_op_eq_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_vr_t *vrs[], size_t num_vrs,
                                 lepton_binary_op_t op, lepton_rl_t *rl) {
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *wordline = &(*rl)[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(wordline, filter);
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
      lepton_free_wordline(result);
    });
    lepton_free_wordline(rhs);
  });
}

lepton_wordline_map_t *lepton_sb_op_eq_rl(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs,
                                          lepton_binary_op_t op,
                                          lepton_rl_t *rl) {
  if (apuc->in_place) {
    lepton_sb_op_eq_rl_in_place(apuc, mask, vrs, num_vrs, op, rl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_vrs * num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *wordline = &(*rl)[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs =
      lepton_left_and_right(wordline, filter);
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
    lepton_free_wordline(rhs);
  });

  return patch;
}

void lepton_sb_op_eq_rsp16_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                    lepton_vr_t *vrs[], size_t num_vrs,
                                    lepton_binary_op_t op,
                                    lepton_rsp16_t *rsp16) {
  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *rhs = &(*filtered_brsp16)[section];
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
      lepton_free_wordline(result);
    });
  });

  lepton_free_vr(filtered_brsp16);
}

lepton_wordline_map_t *lepton_sb_op_eq_rsp16(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_vr_t *vrs[],
                                             size_t num_vrs,
                                             lepton_binary_op_t op,
                                             lepton_rsp16_t *rsp16) {
  if (apuc->in_place) {
    lepton_sb_op_eq_rsp16_in_place(apuc, mask, vrs, num_vrs, op, rsp16);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_vrs * num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_vrs * num_sections;

  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *rhs = &(*filtered_brsp16)[section];
    lepton_foreach_range(i, num_vrs, {
      lepton_vr_t *vr = vrs[i];
      lepton_wordline_t *lhs = &(*vr)[section];
      lepton_wordline_t *result = op(lhs, rhs);
      patch->updates[nth_update].vr = vr;
      patch->updates[nth_update].section = section;
      patch->updates[nth_update].update = result;
      nth_update += 1;
    });
  });

  lepton_free_vr(filtered_brsp16);
  return patch;
}

lepton_wordline_map_t *lepton_sb_op_eq_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           lepton_binary_op_t op,
                                           void *src,
                                           lepton_src_t src_type) {
  switch (src_type) {
  case LEPTON_SRC_GL: // fallthrough
  case LEPTON_SRC_INV_GL: {
    return lepton_sb_op_eq_gl(apuc, mask, vrs, num_vrs, op, src);
  }
  case LEPTON_SRC_GGL: // fallthrough
  case LEPTON_SRC_INV_GGL: {
    return lepton_sb_op_eq_ggl(apuc, mask, vrs, num_vrs, op, src);
  }
  case LEPTON_SRC_RL: // fallthrough
  case LEPTON_SRC_NRL: // fallthrough
  case LEPTON_SRC_ERL: // fallthrough
  case LEPTON_SRC_WRL: // fallthrough
  case LEPTON_SRC_SRL: // fallthrough
  case LEPTON_SRC_INV_RL: // fallthrough
  case LEPTON_SRC_INV_NRL: // fallthrough
  case LEPTON_SRC_INV_ERL: // fallthrough
  case LEPTON_SRC_INV_WRL: // fallthrough
  case LEPTON_SRC_INV_SRL: {
    return lepton_sb_op_eq_rl(apuc, mask, vrs, num_vrs, op, src);
  }
  case LEPTON_SRC_RSP16: // fallthrough
  case LEPTON_SRC_INV_RSP16: {
    return lepton_sb_op_eq_rsp16(apuc, mask, vrs, num_vrs, op, src);
  }
  }
}

lepton_wordline_map_t * lepton_sb_from_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           void *src,
                                           lepton_src_t src_type) {
  return lepton_sb_op_eq_src(apuc, mask,
                             vrs, num_vrs,
                             lepton_right,
                             src, src_type);
}

lepton_wordline_map_t * lepton_sb_from_inv_src(lepton_apuc_t *apuc,
                                               lepton_sm_t mask,
                                               lepton_vr_t *vrs[],
                                               size_t num_vrs,
                                               void *src,
                                               lepton_src_t src_type) {
  return lepton_sb_op_eq_src(apuc, mask,
                             vrs, num_vrs,
                             lepton_inv_right,
                             src, src_type);
}

lepton_wordline_map_t * lepton_sb_cond_eq_src(lepton_apuc_t *apuc,
                                              lepton_sm_t mask,
                                              lepton_vr_t *vrs[],
                                              size_t num_vrs,
                                              void *src,
                                              lepton_src_t src_type) {
  return lepton_sb_op_eq_src(apuc, mask,
                             vrs, num_vrs,
                             lepton_left_or_right,
                             src, src_type);
}

lepton_wordline_map_t * lepton_sb_cond_eq_inv_src(lepton_apuc_t *apuc,
                                                  lepton_sm_t mask,
                                                  lepton_vr_t *vrs[],
                                                  size_t num_vrs,
                                                  void *src,
                                                  lepton_src_t src_type) {
  return lepton_sb_op_eq_src(apuc, mask,
                             vrs, num_vrs,
                             lepton_left_and_inv_right,
                             src, src_type);
}

void lepton_set_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask, bool bit) {
  lepton_wordline_t *wordline = malloc(LEPTON_WORDLINE_SIZE);
  memset(wordline, bit, LEPTON_WORDLINE_SIZE);

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *result = lepton_left_and_right(wordline, filter);
    memcpy(&apuc->rl[section], result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
  });

  lepton_free_wordline(wordline);
}

lepton_wordline_map_t *lepton_set_rl(lepton_apuc_t *apuc,
                                     lepton_sm_t mask,
                                     bool bit) {
  if (apuc->in_place) {
    lepton_set_rl_in_place(apuc, mask, bit);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *wordline = malloc(LEPTON_WORDLINE_SIZE);
  memset(wordline, bit, LEPTON_WORDLINE_SIZE);

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *result = lepton_left_and_right(wordline, filter);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  lepton_free_wordline(wordline);
  return patch;
}

lepton_wordline_t *lepton_conjoin_sections_in_place(lepton_vr_t *vrs[],
                                                    size_t num_vrs,
                                                    size_t section,
                                                    lepton_wordline_t *conj)
{
  memset(conj, true, LEPTON_WORDLINE_SIZE);
  lepton_foreach_range(i, num_vrs, {
    lepton_wordline_t *wordline = &(*vrs[i])[section];
    lepton_left_and_right_in_place(conj, wordline, conj);
  });
  return conj;
}

lepton_wordline_t *lepton_conjoin_sections(lepton_vr_t *vrs[],
                                           size_t num_vrs,
                                           size_t section)
{
  lepton_wordline_t *conj = malloc(LEPTON_WORDLINE_SIZE);
  return lepton_conjoin_sections_in_place(vrs, num_vrs, section, conj);
}

void lepton_rl_op_eq_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_binary_op_t op, lepton_gl_t *gl) {
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    lepton_free_wordline(rhs);
    memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
  });
}

lepton_wordline_map_t *lepton_rl_op_eq_gl(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_binary_op_t op,
                                          lepton_gl_t *gl) {
  if (apuc->in_place) {
    lepton_rl_op_eq_gl_in_place(apuc, mask, op, gl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    lepton_free_wordline(rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

void lepton_rl_op_eq_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                  lepton_binary_op_t op, lepton_ggl_t *ggl) {
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(pseudo_gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    lepton_free_wordline(rhs);
    memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
  });
}

lepton_wordline_map_t *lepton_rl_op_eq_ggl(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_binary_op_t op,
                                           lepton_ggl_t *ggl) {
  if (apuc->in_place) {
    lepton_rl_op_eq_ggl_in_place(apuc, mask, op, ggl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(pseudo_gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    lepton_free_wordline(rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

void lepton_rl_op_eq_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_binary_op_t op, lepton_rl_t *rl) {
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(&(*rl)[section], filter);
    lepton_wordline_t *result = op(lhs, rhs);
    lepton_free_wordline(rhs);
    memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
  });
}

lepton_wordline_map_t *lepton_rl_op_eq_rl(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_binary_op_t op,
                                          lepton_rl_t *rl) {
  if (apuc->in_place) {
    lepton_rl_op_eq_rl_in_place(apuc, mask, op, rl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *rhs = lepton_left_and_right(&(*rl)[section], filter);
    lepton_wordline_t *result = op(lhs, rhs);
    lepton_free_wordline(rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  return patch;
}

void lepton_rl_op_eq_rsp16_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                    lepton_binary_op_t op,
                                    lepton_rsp16_t *rsp16) {
  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *rhs = &(*filtered_brsp16)[section];
    lepton_wordline_t *result = op(lhs, rhs);
    memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
  });

  lepton_free_vr(filtered_brsp16);
}

lepton_wordline_map_t *lepton_rl_op_eq_rsp16(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_binary_op_t op,
                                             lepton_rsp16_t *rsp16) {
  if (apuc->in_place) {
    lepton_rl_op_eq_rsp16_in_place(apuc, mask, op, rsp16);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *rhs = &(*filtered_brsp16)[section];
    lepton_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
  });

  lepton_free_vr(filtered_brsp16);
  return patch;
}

lepton_wordline_map_t *lepton_rl_op_eq_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_binary_op_t op,
                                           void *src,
                                           lepton_src_t src_type)
{
  switch (src_type) {
  case LEPTON_SRC_GL: // fallthrough
  case LEPTON_SRC_INV_GL: {
    return lepton_rl_op_eq_gl(apuc, mask, op, src);
  }
  case LEPTON_SRC_GGL: // fallthrough
  case LEPTON_SRC_INV_GGL: {
    return lepton_rl_op_eq_ggl(apuc, mask, op, src);
  }
  case LEPTON_SRC_RL: // fallthrough
  case LEPTON_SRC_NRL: // fallthrough
  case LEPTON_SRC_ERL: // fallthrough
  case LEPTON_SRC_WRL: // fallthrough
  case LEPTON_SRC_SRL: // fallthrough
  case LEPTON_SRC_INV_RL: // fallthrough
  case LEPTON_SRC_INV_NRL: // fallthrough
  case LEPTON_SRC_INV_ERL: // fallthrough
  case LEPTON_SRC_INV_WRL: // fallthrough
  case LEPTON_SRC_INV_SRL: {
    return lepton_rl_op_eq_rl(apuc, mask, op, src);
  }
  case LEPTON_SRC_RSP16: // fallthrough
  case LEPTON_SRC_INV_RSP16: {
    return lepton_rl_op_eq_rsp16(apuc, mask, op, src);
  }
  }
}

lepton_wordline_map_t *lepton_rl_from_src(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          void *src,
                                          lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_from_inv_src(lepton_apuc_t *apuc,
                                              lepton_sm_t mask,
                                              void *src,
                                              lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_inv_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_or_eq_src(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           void *src,
                                           lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_left_or_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_or_eq_inv_src(lepton_apuc_t *apuc,
                                               lepton_sm_t mask,
                                               void *src,
                                               lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_left_or_inv_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_and_eq_src(lepton_apuc_t *apuc,
                                            lepton_sm_t mask,
                                            void *src,
                                            lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_left_and_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_and_eq_inv_src(lepton_apuc_t *apuc,
                                                lepton_sm_t mask,
                                                void *src,
                                                lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_left_and_inv_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_xor_eq_src(lepton_apuc_t *apuc,
                                            lepton_sm_t mask,
                                            void *src,
                                            lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_left_xor_right,
                             src, src_type);
}

lepton_wordline_map_t *lepton_rl_xor_eq_inv_src(lepton_apuc_t *apuc,
                                                lepton_sm_t mask,
                                                void *src,
                                                lepton_src_t src_type)
{
  return lepton_rl_op_eq_src(apuc, mask,
                             lepton_left_xor_inv_right,
                             src, src_type);
}

void lepton_rl_op_eq_sb_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                 lepton_binary_op_t op, lepton_vr_t *vrs[],
                                 size_t num_vrs) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *rhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    memcpy(lhs, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *lepton_rl_op_eq_sb(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_binary_op_t op,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs) {
  if (apuc->in_place) {
    lepton_rl_op_eq_sb_in_place(apuc, mask, op, vrs, num_vrs);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
    malloc(sizeof(lepton_wordline_map_t)
           + num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *lhs = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *rhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

lepton_wordline_map_t *lepton_rl_from_sb(lepton_apuc_t *apuc,
                                         lepton_sm_t mask,
                                         lepton_vr_t *vrs[],
                                         size_t num_vrs)
{
  return lepton_rl_op_eq_sb(apuc, mask, lepton_right, vrs, num_vrs);
}

lepton_wordline_map_t *lepton_rl_from_inv_sb(lepton_apuc_t *apuc,
                                             lepton_sm_t mask,
                                             lepton_vr_t *vrs[],
                                             size_t num_vrs)
{
  return lepton_rl_op_eq_sb(apuc, mask, lepton_inv_right, vrs, num_vrs);
}

lepton_wordline_map_t *lepton_rl_or_eq_sb(lepton_apuc_t *apuc,
                                          lepton_sm_t mask,
                                          lepton_vr_t *vrs[],
                                          size_t num_vrs)
{
  return lepton_rl_op_eq_sb(apuc, mask, lepton_left_or_right, vrs, num_vrs);
}

lepton_wordline_map_t *lepton_rl_and_eq_sb(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_vr_t *vrs[],
                                           size_t num_vrs)
{
  return lepton_rl_op_eq_sb(apuc, mask, lepton_left_and_right, vrs, num_vrs);
}

lepton_wordline_map_t *lepton_rl_and_eq_inv_sb(lepton_apuc_t *apuc,
                                               lepton_sm_t mask,
                                               lepton_vr_t *vrs[],
                                               size_t num_vrs)
{
  return lepton_rl_op_eq_sb(apuc, mask, lepton_left_and_inv_right, vrs, num_vrs);
}

lepton_wordline_map_t *lepton_rl_xor_eq_sb(lepton_apuc_t *apuc, lepton_sm_t mask,
                                           lepton_vr_t *vrs[], size_t num_vrs)
{
  return lepton_rl_op_eq_sb(apuc, mask, lepton_left_xor_right, vrs, num_vrs);
}

void lepton_rl_op_eq_sb_and_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                        lepton_ternary_op_t op1,
                                        lepton_binary_op_t op2,
                                        lepton_vr_t *vrs[], size_t num_vrs,
                                        lepton_gl_t *gl) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(gl, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    memcpy(nth1, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_gl(lepton_apuc_t *apuc, lepton_sm_t mask,
                          lepton_ternary_op_t op1, lepton_binary_op_t op2,
                          lepton_vr_t *vrs[], size_t num_vrs, lepton_gl_t *gl) {
  if (apuc->in_place) {
    lepton_rl_op_eq_sb_and_gl_in_place(apuc, mask, op1, op2, vrs, num_vrs, gl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(gl, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

void lepton_rl_op_eq_sb_and_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                         lepton_ternary_op_t op1,
                                         lepton_binary_op_t op2,
                                         lepton_vr_t *vrs[], size_t num_vrs,
                                         lepton_ggl_t *ggl) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(pseudo_gl, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    memcpy(nth1, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_ggl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_ternary_op_t op1, lepton_binary_op_t op2,
                           lepton_vr_t *vrs[], size_t num_vrs, lepton_ggl_t *ggl) {
  if (apuc->in_place) {
    lepton_rl_op_eq_sb_and_ggl_in_place(apuc, mask, op1, op2, vrs, num_vrs, ggl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(pseudo_gl, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

void lepton_rl_op_eq_sb_and_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                        lepton_ternary_op_t op1,
                                        lepton_binary_op_t op2,
                                        lepton_vr_t *vrs[], size_t num_vrs,
                                        lepton_rl_t *rl) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*rl)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    memcpy(nth1, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_rl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_ternary_op_t op1, lepton_binary_op_t op2,
                           lepton_vr_t *vrs[], size_t num_vrs, lepton_rl_t *rl) {
  if (apuc->in_place) {
    lepton_rl_op_eq_sb_and_rl_in_place(apuc, mask, op1, op2, vrs, num_vrs, rl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*rl)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

void lepton_rl_op_eq_sb_and_rsp16_in_place(lepton_apuc_t *apuc,
                                           lepton_sm_t mask,
                                           lepton_ternary_op_t op1,
                                           lepton_binary_op_t op2,
                                           lepton_vr_t *vrs[], size_t num_vrs,
                                           lepton_rsp16_t *rsp16) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*filtered_brsp16)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    memcpy(nth1, result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_vr(filtered_brsp16);
  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_rsp16(lepton_apuc_t *apuc, lepton_sm_t mask,
                             lepton_ternary_op_t op1, lepton_binary_op_t op2,
                             lepton_vr_t *vrs[], size_t num_vrs,
                             lepton_rsp16_t *rsp16) {
  if (apuc->in_place) {
    lepton_rl_op_eq_sb_and_rsp16_in_place(apuc, mask, op1, op2, vrs, num_vrs, rsp16);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *nth1 = &apuc->rl[section];
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*filtered_brsp16)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *nth2 = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *nth3 = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result =
      lepton_ternary_expr(apuc, nth1, nth2, nth3, op1, op2);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(nth2);
    lepton_free_wordline(nth3);
  });

  lepton_free_vr(filtered_brsp16);
  lepton_free_wordline(sbdata);
  return patch;
}

lepton_wordline_map_t *
lepton_rl_op_eq_sb_and_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_ternary_op_t op1, lepton_binary_op_t op2,
                           lepton_vr_t *vrs[], size_t num_vrs, void *src,
                           lepton_src_t src_type) {
  switch (src_type) {
  case LEPTON_SRC_GL: // fallthrough
  case LEPTON_SRC_INV_GL: {
    return lepton_rl_op_eq_sb_and_gl(apuc, mask, op1, op2, vrs, num_vrs, src);
  }
  case LEPTON_SRC_GGL: // fallthrough
  case LEPTON_SRC_INV_GGL: {
    return lepton_rl_op_eq_sb_and_ggl(apuc, mask, op1, op2, vrs, num_vrs, src);
  }
  case LEPTON_SRC_RL:      // fallthrough
  case LEPTON_SRC_NRL:     // fallthrough
  case LEPTON_SRC_ERL:     // fallthrough
  case LEPTON_SRC_WRL:     // fallthrough
  case LEPTON_SRC_SRL:     // fallthrough
  case LEPTON_SRC_INV_RL:  // fallthrough
  case LEPTON_SRC_INV_NRL: // fallthrough
  case LEPTON_SRC_INV_ERL: // fallthrough
  case LEPTON_SRC_INV_WRL: // fallthrough
  case LEPTON_SRC_INV_SRL: {
    return lepton_rl_op_eq_sb_and_rl(apuc, mask, op1, op2, vrs, num_vrs, src);
  }
  case LEPTON_SRC_RSP16: // fallthrough
  case LEPTON_SRC_INV_RSP16: {
    return lepton_rl_op_eq_sb_and_rsp16(apuc, mask, op1, op2, vrs, num_vrs,
                                        src);
  }
  }
}

lepton_wordline_map_t *lepton_rl_from_sb_and_src(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask,
                                                 lepton_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_right_in_place,
                                    lepton_left_and_right, vrs, num_vrs, src,
                                    src_type);
}

lepton_wordline_map_t *lepton_rl_or_eq_sb_and_src(lepton_apuc_t *apuc,
                                                  lepton_sm_t mask,
                                                  lepton_vr_t *vrs[],
                                                  size_t num_vrs, void *src,
                                                  lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_left_or_right_in_place,
                                    lepton_left_and_right, vrs, num_vrs, src,
                                    src_type);
}

lepton_wordline_map_t *lepton_rl_or_eq_sb_and_inv_src(lepton_apuc_t *apuc,
                                                      lepton_sm_t mask,
                                                      lepton_vr_t *vrs[],
                                                      size_t num_vrs, void *src,
                                                      lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_left_or_right_in_place,
                                    lepton_left_and_inv_right, vrs, num_vrs,
                                    src, src_type);
}

lepton_wordline_map_t *lepton_rl_and_eq_sb_and_src(lepton_apuc_t *apuc,
                                                   lepton_sm_t mask,
                                                   lepton_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_left_and_right_in_place,
                                    lepton_left_and_right, vrs, num_vrs,
                                    src, src_type);
}

lepton_wordline_map_t *
lepton_rl_and_eq_sb_and_inv_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                                lepton_vr_t *vrs[], size_t num_vrs, void *src,
                                lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_left_and_right_in_place,
                                    lepton_left_and_inv_right, vrs, num_vrs,
                                    src, src_type);
}

lepton_wordline_map_t *lepton_rl_xor_eq_sb_and_src(lepton_apuc_t *apuc,
                                                   lepton_sm_t mask,
                                                   lepton_vr_t *vrs[],
                                                   size_t num_vrs, void *src,
                                                   lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_left_xor_right_in_place,
                                    lepton_left_and_right, vrs, num_vrs, src,
                                    src_type);
}

lepton_wordline_map_t *
lepton_rl_xor_eq_sb_and_inv_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                                lepton_vr_t *vrs[], size_t num_vrs, void *src,
                                lepton_src_t src_type)
{
  return lepton_rl_op_eq_sb_and_src(apuc, mask, lepton_left_xor_right_in_place,
                                    lepton_left_and_inv_right, vrs, num_vrs,
                                    src, src_type);
}

void lepton_rl_from_sb_binop_gl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                         lepton_vr_t *vrs[], size_t num_vrs,
                                         lepton_binary_op_t op,
                                         lepton_gl_t *gl) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    memcpy(&apuc->rl[section], result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_from_sb_binop_gl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_vr_t *vrs[], size_t num_vrs,
                           lepton_binary_op_t op, lepton_gl_t *gl) {
  if (apuc->in_place) {
    lepton_rl_from_sb_binop_gl_in_place(apuc, mask, vrs, num_vrs, op, gl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

void lepton_rl_from_sb_binop_ggl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                          lepton_vr_t *vrs[], size_t num_vrs,
                                          lepton_binary_op_t op,
                                          lepton_ggl_t *ggl) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(pseudo_gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    memcpy(&apuc->rl[section], result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_from_sb_binop_ggl(lepton_apuc_t *apuc, lepton_sm_t mask,
                            lepton_vr_t *vrs[], size_t num_vrs,
                            lepton_binary_op_t op, lepton_ggl_t *ggl) {
  if (apuc->in_place) {
    lepton_rl_from_sb_binop_ggl_in_place(apuc, mask, vrs, num_vrs, op, ggl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *pseudo_gl = &(*ggl)[section / LEPTON_NUM_GROUPS];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(pseudo_gl, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

void lepton_rl_from_sb_binop_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask,
                                         lepton_vr_t *vrs[], size_t num_vrs,
                                         lepton_binary_op_t op,
                                         lepton_rl_t *rl) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*rl)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    memcpy(&apuc->rl[section], result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_from_sb_binop_rl(lepton_apuc_t *apuc, lepton_sm_t mask,
                           lepton_vr_t *vrs[], size_t num_vrs,
                           lepton_binary_op_t op, lepton_rl_t *rl) {
  if (apuc->in_place) {
    lepton_rl_from_sb_binop_rl_in_place(apuc, mask, vrs, num_vrs, op, rl);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*rl)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_wordline(sbdata);
  return patch;
}

void lepton_rl_from_sb_binop_rsp16_in_place(lepton_apuc_t *apuc,
                                            lepton_sm_t mask,
                                            lepton_vr_t *vrs[], size_t num_vrs,
                                            lepton_binary_op_t op,
                                            lepton_rsp16_t *rsp16) {
  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*filtered_brsp16)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    memcpy(&apuc->rl[section], result, LEPTON_WORDLINE_SIZE);
    lepton_free_wordline(result);
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_vr(filtered_brsp16);
  lepton_free_wordline(sbdata);
}

lepton_wordline_map_t *
lepton_rl_from_sb_binop_rsp16(lepton_apuc_t *apuc, lepton_sm_t mask,
                              lepton_vr_t *vrs[], size_t num_vrs,
                              lepton_binary_op_t op, lepton_rsp16_t *rsp16) {
  if (apuc->in_place) {
    lepton_rl_from_sb_binop_rsp16_in_place(apuc, mask, vrs, num_vrs, op, rsp16);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_wordline_map_t *patch =
      malloc(sizeof(lepton_wordline_map_t) +
             num_sections * sizeof(lepton_wordline_patch_t));
  patch->size = num_sections;

  lepton_wordline_t *sbdata = malloc(sizeof(lepton_wordline_t));

  lepton_brsp16_t *filtered_brsp16 = lepton_brsp16(rsp16);
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      (*filtered_brsp16)[section][plat] &= apuc->rwinh_filter[section][plat];
    });
  });

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    lepton_wordline_t *filter = &apuc->rwinh_filter[section];
    lepton_wordline_t *wordline = &(*filtered_brsp16)[section];
    lepton_conjoin_sections_in_place(vrs, num_vrs, section, sbdata);
    lepton_wordline_t *lhs = lepton_left_and_right(sbdata, filter);
    lepton_wordline_t *rhs = lepton_left_and_right(wordline, filter);
    lepton_wordline_t *result = op(lhs, rhs);
    patch->updates[nth_update].vr = &apuc->rl;
    patch->updates[nth_update].section = section;
    patch->updates[nth_update].update = result;
    nth_update += 1;
    lepton_free_wordline(lhs);
    lepton_free_wordline(rhs);
  });

  lepton_free_vr(filtered_brsp16);
  lepton_free_wordline(sbdata);
  return patch;
}

lepton_wordline_map_t *lepton_rl_from_sb_binop_src(
    lepton_apuc_t *apuc, lepton_sm_t mask, lepton_vr_t *vrs[], size_t num_vrs,
    lepton_binary_op_t op, void *src, lepton_src_t src_type) {
  switch (src_type) {
  case LEPTON_SRC_GL: // fallthrough
  case LEPTON_SRC_INV_GL: {
    return lepton_rl_from_sb_binop_gl(apuc, mask, vrs, num_vrs, op, src);
  }
  case LEPTON_SRC_GGL: // fallthrough
  case LEPTON_SRC_INV_GGL: {
    return lepton_rl_from_sb_binop_ggl(apuc, mask, vrs, num_vrs, op, src);
  }
  case LEPTON_SRC_RL:      // fallthrough
  case LEPTON_SRC_NRL:     // fallthrough
  case LEPTON_SRC_ERL:     // fallthrough
  case LEPTON_SRC_WRL:     // fallthrough
  case LEPTON_SRC_SRL:     // fallthrough
  case LEPTON_SRC_INV_RL:  // fallthrough
  case LEPTON_SRC_INV_NRL: // fallthrough
  case LEPTON_SRC_INV_ERL: // fallthrough
  case LEPTON_SRC_INV_WRL: // fallthrough
  case LEPTON_SRC_INV_SRL: {
    return lepton_rl_from_sb_binop_rl(apuc, mask, vrs, num_vrs, op, src);
  }
  case LEPTON_SRC_RSP16: // fallthrough
  case LEPTON_SRC_INV_RSP16: {
    return lepton_rl_from_sb_binop_rsp16(apuc, mask, vrs, num_vrs, op, src);
  }
  }
}

lepton_wordline_map_t *
lepton_rl_from_sb_or_src(lepton_apuc_t *apuc, lepton_sm_t mask, lepton_vr_t *vrs[],
                         size_t num_vrs, void *src, lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     lepton_left_or_right, src, src_type);
}

lepton_wordline_map_t *lepton_rl_from_sb_or_inv_src(lepton_apuc_t *apuc,
                                                    lepton_sm_t mask,
                                                    lepton_vr_t *vrs[],
                                                    size_t num_vrs, void *src,
                                                    lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     lepton_left_or_inv_right, src, src_type);
}

lepton_wordline_map_t *lepton_rl_from_sb_xor_src(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask,
                                                 lepton_vr_t *vrs[],
                                                 size_t num_vrs, void *src,
                                                 lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     lepton_left_xor_right, src, src_type);
}

lepton_wordline_map_t *lepton_rl_from_sb_xor_inv_src(lepton_apuc_t *apuc,
                                                     lepton_sm_t mask,
                                                     lepton_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     lepton_left_xor_inv_right, src, src_type);
}

lepton_wordline_map_t *lepton_rl_from_inv_sb_and_src(lepton_apuc_t *apuc,
                                                     lepton_sm_t mask,
                                                     lepton_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     lepton_inv_left_and_right, src, src_type);
}

lepton_wordline_map_t *
lepton_rl_from_inv_sb_and_inv_src(lepton_apuc_t *apuc, lepton_sm_t mask,
                                  lepton_vr_t *vrs[], size_t num_vrs, void *src,
                                  lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(
      apuc, mask, vrs, num_vrs, lepton_inv_left_and_inv_right, src, src_type);
}

lepton_wordline_map_t *lepton_rl_from_sb_and_inv_src(lepton_apuc_t *apuc,
                                                     lepton_sm_t mask,
                                                     lepton_vr_t *vrs[],
                                                     size_t num_vrs, void *src,
                                                     lepton_src_t src_type) {
  return lepton_rl_from_sb_binop_src(apuc, mask, vrs, num_vrs,
                                     lepton_left_and_inv_right, src, src_type);
}

void lepton_rsp16_from_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask) {
  size_t step_size = LEPTON_NUM_RL_PLATS / LEPTON_NUM_RSP16_PLATS;
  size_t num_steps = LEPTON_NUM_RSP16_PLATS;
  lepton_foreach_range(step, num_steps, {
    size_t lower = step * step_size;
    size_t upper = lower + step_size;
    lepton_foreach_masked_section(mask, section, {
      lepton_any_plat_in_place(&apuc->rsp16, &apuc->rl,
                               section, step, lower, upper);
    });
  });
}

lepton_rsp16_section_map_t *lepton_rsp16_from_rl(lepton_apuc_t *apuc,
                                                 lepton_sm_t mask) {
  if (apuc->in_place) {
    lepton_rsp16_from_rl_in_place(apuc, mask);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);
  lepton_rsp16_section_map_t *patch =
      malloc(sizeof(lepton_rsp16_section_map_t) +
             num_sections * sizeof(lepton_rsp16_section_patch_t));
  patch->size = num_sections;

  size_t nth_update = 0;
  lepton_foreach_masked_section(mask, section, {
    patch->updates[nth_update].section = section;
    nth_update += 1;
  });

  size_t step_size = LEPTON_NUM_RL_PLATS / LEPTON_NUM_RSP16_PLATS;
  size_t num_steps = LEPTON_NUM_RSP16_PLATS;
  lepton_foreach_range(step, num_steps, {
    size_t lower = step * step_size;
    size_t upper = lower + step_size;
    size_t nth_update = 0;
    lepton_foreach_masked_section(mask, section, {
      patch->updates[nth_update].update[step] = false;
      lepton_foreach_range(plat, lower, upper, {
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

void lepton_gl_from_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask) {
  size_t num_sections = lepton_count_masked_sections(mask);

  memset(&apuc->gl, true, LEPTON_GL_SIZE);

  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
      apuc->gl[plat] &= apuc->rl[section][plat];
    });
  });
}

lepton_gl_t *lepton_gl_from_rl(lepton_apuc_t *apuc, lepton_sm_t mask) {
  if (apuc->in_place) {
    lepton_gl_from_rl_in_place(apuc, mask);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);

  lepton_gl_t *gl = malloc(LEPTON_GL_SIZE);
  memset(gl, true, LEPTON_GL_SIZE);

  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
      (*gl)[plat] &= apuc->rl[section][plat];
    });
  });

  return gl;
}

void lepton_ggl_from_rl_in_place(lepton_apuc_t *apuc, lepton_sm_t mask) {
  size_t num_sections = lepton_count_masked_sections(mask);

  memset(&apuc->ggl, true, LEPTON_GGL_SIZE);

  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
      apuc->ggl[section / LEPTON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });
}

lepton_ggl_t *lepton_ggl_from_rl(lepton_apuc_t *apuc, lepton_sm_t mask) {
  if (apuc->in_place) {
    lepton_ggl_from_rl_in_place(apuc, mask);
    return NULL;
  }

  size_t num_sections = lepton_count_masked_sections(mask);

  lepton_ggl_t *ggl = malloc(LEPTON_GGL_SIZE);
  memset(ggl, true, LEPTON_GGL_SIZE);

  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
      (*ggl)[section / LEPTON_NUM_GROUPS][plat] &= apuc->rl[section][plat];
    });
  });

  return ggl;
}

void lepton_l1_from_ggl_in_place(lepton_apuc_t *apuc, size_t l1_addr) {
  memcpy(&apuc->l1[l1_addr], &apuc->ggl, LEPTON_GGL_SIZE);
}

lepton_l1_patch_t *lepton_l1_from_ggl(lepton_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    lepton_l1_from_ggl_in_place(apuc, l1_addr);
    return NULL;
  }
  lepton_l1_patch_t *patch = malloc(sizeof(lepton_l1_patch_t));
  patch->src = LEPTON_L1_SRC_GGL;
  patch->l1_addr = l1_addr;
  patch->ggl_patch = malloc(sizeof(lepton_ggl_t));
  memcpy(patch->ggl_patch, &apuc->ggl, LEPTON_GGL_SIZE);
  return patch;
}

void lepton_lgl_from_l1_in_place(lepton_apuc_t *apuc, size_t l1_addr) {
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    apuc->lgl[lgl_plat] = apuc->l1[row][group][l1_plat];
  });
}

lepton_lgl_t *lepton_lgl_from_l1(lepton_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    lepton_lgl_from_l1_in_place(apuc, l1_addr);
    return NULL;
  }

  lepton_lgl_t *lgl = malloc(sizeof(lepton_lgl_t));

  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    (*lgl)[lgl_plat] = apuc->l1[row][group][l1_plat];
  });

  return lgl;
}

void lepton_l2_from_lgl_in_place(lepton_apuc_t *apuc, size_t l2_addr) {
  memcpy(&apuc->l2[l2_addr], &apuc->lgl, LEPTON_LGL_SIZE);
}

lepton_l2_patch_t *lepton_l2_from_lgl(lepton_apuc_t *apuc, size_t l2_addr) {
  if (apuc->in_place) {
    lepton_l2_from_lgl_in_place(apuc, l2_addr);
    return NULL;
  }
  lepton_l2_patch_t *patch = malloc(sizeof(lepton_l2_patch_t));
  patch->l2_addr = l2_addr;
  patch->update = malloc(sizeof(lepton_l2_t));
  memcpy(patch->update, &apuc->lgl, LEPTON_LGL_SIZE);
  return patch;
}

void lepton_lgl_from_l2_in_place(lepton_apuc_t *apuc, size_t l2_addr) {
  memcpy(&apuc->lgl, &apuc->l2[l2_addr], LEPTON_LGL_SIZE);
}

lepton_lgl_t *lepton_lgl_from_l2(lepton_apuc_t *apuc, size_t l2_addr) {
  if (apuc->in_place) {
    lepton_lgl_from_l2_in_place(apuc, l2_addr);
    return NULL;
  }
  lepton_lgl_t *lgl = malloc(sizeof(lepton_lgl_t));
  memcpy(lgl, &apuc->l2[l2_addr], LEPTON_LGL_SIZE);
  return lgl;
}

void lepton_l1_from_lgl_in_place(lepton_apuc_t *apuc, size_t l1_addr) {
  size_t bank, group, row;
  lepton_bank_group_row(l1_addr, &bank, &group, &row);
  lepton_foreach_bank_plat(bank, lgl_plat, l1_plat, {
    apuc->l1[row][group][l1_plat] = apuc->lgl[lgl_plat];
  });
}

lepton_l1_patch_t *lepton_l1_from_lgl(lepton_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    lepton_l1_from_lgl_in_place(apuc, l1_addr);
    return NULL;
  }
  lepton_l1_patch_t *patch = malloc(sizeof(lepton_l1_patch_t));
  patch->src = LEPTON_L1_SRC_LGL;
  patch->l1_addr = l1_addr;
  patch->lgl_patch = malloc(sizeof(lepton_lgl_t));
  memcpy(patch->lgl_patch, &apuc->lgl, LEPTON_LGL_SIZE);
  return patch;
}

void lepton_ggl_from_l1_in_place(lepton_apuc_t *apuc, size_t l1_addr) {
  memcpy(&apuc->ggl, &apuc->l1[l1_addr], LEPTON_GGL_SIZE);
}

lepton_ggl_t *lepton_ggl_from_l1(lepton_apuc_t *apuc, size_t l1_addr) {
  if (apuc->in_place) {
    lepton_ggl_from_l1_in_place(apuc, l1_addr);
    return NULL;
  }
  lepton_ggl_t *ggl = malloc(sizeof(lepton_ggl_t));
  memcpy(ggl, &apuc->l1[l1_addr], LEPTON_GGL_SIZE);
  return ggl;
}

void lepton_ggl_from_rl_and_l1_in_place(lepton_apuc_t *apuc, size_t mask,
                                        size_t l1_addr) {
  lepton_ggl_from_rl_in_place(apuc, mask);
  lepton_foreach_l1_group_plat(group, plat, {
    apuc->ggl[group][plat] &= apuc->l1[l1_addr][group][plat];
  });
}

lepton_ggl_t *lepton_ggl_from_rl_and_l1(lepton_apuc_t *apuc, size_t mask,
                                        size_t l1_addr) {
  if (apuc->in_place) {
    lepton_ggl_from_rl_and_l1_in_place(apuc, mask, l1_addr);
    return NULL;
  }
  lepton_ggl_t *ggl = lepton_ggl_from_rl(apuc, mask);
  lepton_foreach_l1_group_plat(group, plat, {
    (*ggl)[group][plat] &= apuc->l1[l1_addr][group][plat];
  });
  return ggl;
}

void lepton_rwinh_set_in_place(lepton_apuc_t *apuc, size_t mask) {
  apuc->rwinh_sects |= mask;
  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_vr_plat(plat, {
      apuc->rwinh_filter[section][plat] = apuc->rl[section][plat];
    });
  });
}

size_t lepton_rwinh_set(lepton_apuc_t *apuc, size_t mask) {
  if (apuc->in_place) {
    lepton_rwinh_set_in_place(apuc, mask);
    return 0x0000;
  }
  return mask;
}

void lepton_rwinh_rst_in_place(lepton_apuc_t *apuc, size_t mask, bool has_read) {
  if (!has_read) {
    lepton_foreach_masked_section(mask, section, {
      memcpy(&apuc->rl[section], &apuc->rwinh_filter[section], LEPTON_WORDLINE_SIZE);
    });
  }

  apuc->rwinh_sects &= ~mask;
  lepton_foreach_masked_section(~apuc->rwinh_sects, section, {
    memset(&apuc->rwinh_filter[section], true, LEPTON_WORDLINE_SIZE);
  });
}

lepton_rwinh_rst_patch_t *lepton_rwinh_rst(lepton_apuc_t *apuc, size_t mask,
                                           bool has_read) {
  if (apuc->in_place) {
    lepton_rwinh_rst_in_place(apuc, mask, has_read);
    return NULL;
  }
  lepton_rwinh_rst_patch_t *patch = malloc(sizeof(lepton_rwinh_rst_patch_t));
  patch->mask = mask;
  patch->has_read = has_read;
  return patch;
}
