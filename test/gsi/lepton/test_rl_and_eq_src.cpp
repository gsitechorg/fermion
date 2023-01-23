#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rl_and_eq_src, ()) {
  lepton_sm_t mask = lepton_gen_mask();
  lepton_src_t src_type = lepton_gen_src_type();

  uint32_t rl_seed = lepton_gen_seed();
  uint32_t src_seed = lepton_gen_seed();

  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_randomize_src(apuc, src_type, src_seed);

  // NOTE: Load src only after randomizing it
  void *src = lepton_src(apuc, src_type);

  lepton_vr_t *expected = (lepton_vr_t *)malloc(sizeof(lepton_vr_t));
  memcpy(expected, &apuc->rl, LEPTON_VR_SIZE);

  lepton_foreach_masked_section(mask, section, {
    lepton_foreach_rl_plat(plat, {
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
      case LEPTON_SRC_INV_SRL: // fallthrough
        (*expected)[section][plat] &= (*(lepton_rl_t *)src)[section][plat];
        break;
      case LEPTON_SRC_GGL: // fallthrough
      case LEPTON_SRC_INV_GGL:
        (*expected)[section][plat] &=
          (*(lepton_ggl_t *)src)[section / LEPTON_NUM_GROUPS][plat];
        break;
      case LEPTON_SRC_GL: // fallthrough
      case LEPTON_SRC_INV_GL:
        (*expected)[section][plat] &= (*(lepton_gl_t *)src)[plat];
        break;
      case LEPTON_SRC_RSP16: // fallthrough
      case LEPTON_SRC_INV_RSP16:
        (*expected)[section][plat] &=
          (*(lepton_rsp16_t *)src)[section][plat / 16];
        break;
      }
    });
  });

  lepton_rl_and_eq_src(apuc, mask, src, src_type);
  RC_ASSERT(lepton_rl_eq(&apuc->rl, expected));

  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_randomize_src(apuc, src_type, src_seed);

  // Refresh src
  lepton_free_src(src, src_type);
  src = lepton_src(apuc, src_type);

  apuc->in_place = false;
  lepton_wordline_map_t *patch =
    lepton_rl_and_eq_src(apuc, mask, src, src_type);
  lepton_patch_sb(apuc, patch);
  lepton_free_wordline_map(patch);
  RC_ASSERT(lepton_vr_eq(&apuc->rl, expected));
  apuc->in_place = true;

  lepton_free_vr(expected);
  lepton_free_src(src, src_type);
}
