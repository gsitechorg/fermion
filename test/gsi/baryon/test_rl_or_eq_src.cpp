/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rl_or_eq_src, ()) {
  baryon_sm_t mask = baryon_gen_mask();
  baryon_src_t src_type = baryon_gen_src_type();

  uint32_t rl_seed = baryon_gen_seed();
  uint32_t src_seed = baryon_gen_seed();

  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_randomize_src(apuc, src_type, src_seed);

  // NOTE: Load src only after randomizing it
  void *src = baryon_src(apuc, src_type);

  baryon_vr_t *expected = (baryon_vr_t *)malloc(sizeof(baryon_vr_t));
  memcpy(expected, &apuc->rl, BARYON_VR_SIZE);

  baryon_foreach_masked_section(mask, section, {
    baryon_foreach_rl_plat(plat, {
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
      case BARYON_SRC_INV_SRL: // fallthrough
        (*expected)[section][plat] |= (*(baryon_rl_t *)src)[section][plat];
        break;
      case BARYON_SRC_GGL: // fallthrough
      case BARYON_SRC_INV_GGL:
        (*expected)[section][plat] |=
          (*(baryon_ggl_t *)src)[section / BARYON_NUM_GROUPS][plat];
        break;
      case BARYON_SRC_GL: // fallthrough
      case BARYON_SRC_INV_GL:
        (*expected)[section][plat] |= (*(baryon_gl_t *)src)[plat];
        break;
      case BARYON_SRC_RSP16: // fallthrough
      case BARYON_SRC_INV_RSP16:
        (*expected)[section][plat] |=
          (*(baryon_rsp16_t *)src)[section][plat / 16];
        break;
      }
    });
  });

  baryon_rl_or_eq_src(apuc, mask, src, src_type);
  RC_ASSERT(baryon_rl_eq(&apuc->rl, expected));

  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_randomize_src(apuc, src_type, src_seed);

  // Refresh src
  baryon_free_src(src, src_type);
  src = baryon_src(apuc, src_type);

  apuc->in_place = false;
  baryon_wordline_map_t *patch =
    baryon_rl_or_eq_src(apuc, mask, src, src_type);
  baryon_patch_sb(apuc, patch);
  baryon_free_wordline_map(patch);
  RC_ASSERT(baryon_vr_eq(&apuc->rl, expected));
  apuc->in_place = true;

  baryon_free_vr(expected);
  baryon_free_src(src, src_type);
}
