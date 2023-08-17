/* By Dylon Edwards
 */

#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *rl = baryon_rl(apuc);
  RC_ASSERT(baryon_rl_eq(rl, &apuc->rl));
  baryon_free_rl(rl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, nrl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *nrl = baryon_nrl(apuc);
  baryon_foreach_rl_plat(plat, {
    RC_ASSERT(!(*nrl)[0][plat]);
    baryon_foreach_range(section, BARYON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*nrl)[section + 1][plat] == apuc->rl[section][plat]);
    });
  });
  baryon_free_rl(nrl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, erl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *erl = baryon_erl(apuc);
  baryon_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + BARYON_NUM_PLATS_PER_HALF_BANK;
    baryon_foreach_rl_section(section, {
      RC_ASSERT(!(*erl)[section][upper_plat - 1]);
      baryon_foreach_range(plat, lower_plat, upper_plat - 1, {
        RC_ASSERT((*erl)[section][plat] == apuc->rl[section][plat + 1]);
      });
    });
  });
  baryon_free_rl(erl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, wrl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *wrl = baryon_wrl(apuc);
  baryon_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + BARYON_NUM_PLATS_PER_HALF_BANK;
    baryon_foreach_rl_section(section, {
      RC_ASSERT(!(*wrl)[section][lower_plat]);
      baryon_foreach_range(plat, lower_plat + 1, upper_plat, {
        RC_ASSERT((*wrl)[section][plat] == apuc->rl[section][plat - 1]);
      });
    });
  });
  baryon_free_rl(wrl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, srl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *srl = baryon_srl(apuc);
  baryon_foreach_rl_plat(plat, {
    RC_ASSERT(!(*srl)[15][plat]);
    baryon_foreach_range(section, BARYON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*srl)[section][plat] == apuc->rl[section + 1][plat]);
    });
  });
  baryon_free_rl(srl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_rl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *inv_rl = baryon_inv_rl(apuc);
  baryon_foreach_rl_section_plat(section, plat, {
    RC_ASSERT((*inv_rl)[section][plat] == !apuc->rl[section][plat]);
  });
  baryon_free_rl(inv_rl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_nrl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *inv_nrl = baryon_inv_nrl(apuc);
  baryon_foreach_rl_plat(plat, {
    RC_ASSERT((*inv_nrl)[0][plat]);
    baryon_foreach_range(section, BARYON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*inv_nrl)[section + 1][plat] != apuc->rl[section][plat]);
    });
  });
  baryon_free_rl(inv_nrl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_erl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *inv_erl = baryon_inv_erl(apuc);
  baryon_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + BARYON_NUM_PLATS_PER_HALF_BANK;
    baryon_foreach_rl_section(section, {
      RC_ASSERT((*inv_erl)[section][upper_plat - 1]);
      baryon_foreach_range(plat, lower_plat, upper_plat - 1, {
        RC_ASSERT((*inv_erl)[section][plat] != apuc->rl[section][plat + 1]);
      });
    });
  });
  baryon_free_rl(inv_erl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_wrl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *inv_wrl = baryon_inv_wrl(apuc);
  baryon_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * BARYON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + BARYON_NUM_PLATS_PER_HALF_BANK;
    baryon_foreach_rl_section(section, {
      RC_ASSERT((*inv_wrl)[section][lower_plat]);
      baryon_foreach_range(plat, lower_plat + 1, upper_plat, {
        RC_ASSERT((*inv_wrl)[section][plat] != apuc->rl[section][plat - 1]);
      });
    });
  });
  baryon_free_rl(inv_wrl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_srl, ()) {
  uint32_t rl_seed = baryon_gen_seed();
  baryon_randomize_rl(&apuc->rl, rl_seed);
  baryon_rl_t *inv_srl = baryon_inv_srl(apuc);
  baryon_foreach_rl_plat(plat, {
    RC_ASSERT((*inv_srl)[15][plat]);
    baryon_foreach_range(section, BARYON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*inv_srl)[section][plat] != apuc->rl[section + 1][plat]);
    });
  });
  baryon_free_rl(inv_srl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, ggl, ()) {
  uint32_t ggl_seed = baryon_gen_seed();
  baryon_randomize_ggl(&apuc->ggl, ggl_seed);
  baryon_ggl_t *ggl = baryon_ggl(apuc);
  RC_ASSERT(baryon_ggl_eq(ggl, &apuc->ggl));
  baryon_free_ggl(ggl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_ggl, ()) {
  uint32_t inv_ggl_seed = baryon_gen_seed();
  baryon_randomize_ggl(&apuc->ggl, inv_ggl_seed);
  baryon_ggl_t *inv_ggl = baryon_inv_ggl(apuc);
  baryon_foreach_ggl_group_plat(group, plat, {
    RC_ASSERT((*inv_ggl)[group][plat] != apuc->ggl[group][plat]);
  });
  baryon_free_ggl(inv_ggl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, gl, ()) {
  uint32_t gl_seed = baryon_gen_seed();
  baryon_randomize_gl(&apuc->gl, gl_seed);
  baryon_gl_t *gl = baryon_gl(apuc);
  RC_ASSERT(baryon_gl_eq(gl, &apuc->gl));
  baryon_free_gl(gl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_gl, ()) {
  uint32_t inv_gl_seed = baryon_gen_seed();
  baryon_randomize_gl(&apuc->gl, inv_gl_seed);
  baryon_gl_t *inv_gl = baryon_inv_gl(apuc);
  baryon_foreach_gl_plat(plat, {
    RC_ASSERT((*inv_gl)[plat] != apuc->gl[plat]);
  });
  baryon_free_gl(inv_gl);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, rsp16, ()) {
  uint32_t rsp16_seed = baryon_gen_seed();
  baryon_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  baryon_rsp16_t *rsp16 = baryon_rsp16(apuc);
  RC_ASSERT(baryon_rsp16_eq(rsp16, &apuc->rsp16));
  baryon_free_rsp16(rsp16);
}

RC_GTEST_FIXTURE_PROP(BaryonAPUCTest, inv_rsp16, ()) {
  uint32_t inv_rsp16_seed = baryon_gen_seed();
  baryon_randomize_rsp16(&apuc->rsp16, inv_rsp16_seed);
  baryon_rsp16_t *inv_rsp16 = baryon_inv_rsp16(apuc);
  baryon_foreach_rsp16_section_plat(section, plat, {
    RC_ASSERT((*inv_rsp16)[section][plat] != apuc->rsp16[section][plat]);
  });
  baryon_free_rsp16(inv_rsp16);
}
