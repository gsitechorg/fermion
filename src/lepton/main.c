#include <stdbool.h>
#include <stdio.h>

#include "lepton/apuc.h"

int main(int argc, char *argv[])
{
  // must use malloc to avoid stack overflow and subsequent segfault
  lepton_apuc_t *apuc = malloc(sizeof(lepton_apuc_t));
  lepton_init_apuc(apuc);

  lepton_vr_t *vrs[1];
  vrs[0] = malloc(sizeof(lepton_vr_t));

  lepton_wordline_map_t *patch;

  // msk: <SB> = <SRC>;

  patch = lepton_sb_from_src(apuc, 0xFFFF, vrs, 1, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_from_src(apuc, 0xFFFF, vrs, 1, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_from_src(apuc, 0xFFFF, vrs, 1, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_from_src(apuc, 0xFFFF, vrs, 1, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: <SB> = ~<SRC>;

  patch = lepton_sb_from_inv_src(apuc, 0xFFFF, vrs, 1, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_from_inv_src(apuc, 0xFFFF, vrs, 1, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_from_inv_src(apuc, 0xFFFF, vrs, 1, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_from_inv_src(apuc, 0xFFFF, vrs, 1,
                                 &apuc->rsp16,
                                 LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: <SB> ?= <SRC>;

  patch = lepton_sb_cond_equals_src(apuc, 0xFFFF, vrs, 1,
                                    &apuc->gl,
                                    LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_cond_equals_src(apuc, 0xFFFF, vrs, 1,
                                    &apuc->ggl,
                                    LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_cond_equals_src(apuc, 0xFFFF, vrs, 1,
                                    &apuc->rl,
                                    LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_cond_equals_src(apuc, 0xFFFF, vrs, 1,
                                    &apuc->rsp16,
                                    LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: <SB> ?= ~<SRC>;

  patch = lepton_sb_cond_equals_inv_src(apuc, 0xFFFF, vrs, 1,
                                        &apuc->gl,
                                        LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_cond_equals_inv_src(apuc, 0xFFFF, vrs, 1,
                                        &apuc->ggl,
                                        LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_cond_equals_inv_src(apuc, 0xFFFF, vrs, 1,
                                        &apuc->rl,
                                        LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_sb_cond_equals_inv_src(apuc, 0xFFFF, vrs, 1,
                                        &apuc->rsp16,
                                        LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL = <bit>

  patch = lepton_set_rl(apuc, 0xFFFF, true);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_set_rl(apuc, 0xFFFF, false);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL = <SRC>;

  patch = lepton_rl_from_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL = ~<SRC>;

  patch = lepton_rl_from_inv_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_inv_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_inv_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_inv_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL |= <SRC>;

  patch = lepton_rl_or_eq_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_or_eq_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_or_eq_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_or_eq_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL |= ~<SRC>;

  patch = lepton_rl_or_eq_inv_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_or_eq_inv_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_or_eq_inv_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_or_eq_inv_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL &= <SRC>;

  patch = lepton_rl_and_eq_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_and_eq_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_and_eq_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_and_eq_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL &= ~<SRC>;

  patch = lepton_rl_and_eq_inv_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_and_eq_inv_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_and_eq_inv_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_and_eq_inv_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL ^= <SRC>;

  patch = lepton_rl_xor_eq_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_xor_eq_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_xor_eq_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_xor_eq_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL ^= ~<SRC>;

  patch = lepton_rl_xor_eq_inv_src(apuc, 0xFFFF, &apuc->gl, LEPTON_SRC_GL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_xor_eq_inv_src(apuc, 0xFFFF, &apuc->ggl, LEPTON_SRC_GGL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_xor_eq_inv_src(apuc, 0xFFFF, &apuc->rl, LEPTON_SRC_RL);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_xor_eq_inv_src(apuc, 0xFFFF, &apuc->rsp16, LEPTON_SRC_RSP16);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL = <SB>;

  patch = lepton_rl_from_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  // msk: RL = ~<SB>;

  patch = lepton_rl_from_inv_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_inv_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_inv_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  patch = lepton_rl_from_inv_sb(apuc, 0xFFFF, vrs, 1);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);

  lepton_free_apuc(apuc);
  return 0;
}
