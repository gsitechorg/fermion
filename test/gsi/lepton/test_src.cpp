#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *rl = lepton_rl(apuc);
  RC_ASSERT(lepton_rl_eq(rl, &apuc->rl));
  lepton_free_rl(rl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, nrl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_foreach_rl_plat(plat, {
    RC_ASSERT(!(*nrl)[0][plat]);
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*nrl)[section + 1][plat] == apuc->rl[section][plat]);
    });
  });
  lepton_free_rl(nrl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, erl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *erl = lepton_erl(apuc);
  lepton_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * LEPTON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + LEPTON_NUM_PLATS_PER_HALF_BANK;
    lepton_foreach_rl_section(section, {
      RC_ASSERT(!(*erl)[section][upper_plat - 1]);
      lepton_foreach_range(plat, lower_plat, upper_plat - 1, {
        RC_ASSERT((*erl)[section][plat] == apuc->rl[section][plat + 1]);
      });
    });
  });
  lepton_free_rl(erl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, wrl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *wrl = lepton_wrl(apuc);
  lepton_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * LEPTON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + LEPTON_NUM_PLATS_PER_HALF_BANK;
    lepton_foreach_rl_section(section, {
      RC_ASSERT(!(*wrl)[section][lower_plat]);
      lepton_foreach_range(plat, lower_plat + 1, upper_plat, {
        RC_ASSERT((*wrl)[section][plat] == apuc->rl[section][plat - 1]);
      });
    });
  });
  lepton_free_rl(wrl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, srl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *srl = lepton_srl(apuc);
  lepton_foreach_rl_plat(plat, {
    RC_ASSERT(!(*srl)[15][plat]);
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*srl)[section][plat] == apuc->rl[section + 1][plat]);
    });
  });
  lepton_free_rl(srl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_rl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *inv_rl = lepton_inv_rl(apuc);
  lepton_foreach_rl_section_plat(section, plat, {
    RC_ASSERT((*inv_rl)[section][plat] == !apuc->rl[section][plat]);
  });
  lepton_free_rl(inv_rl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_nrl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *inv_nrl = lepton_inv_nrl(apuc);
  lepton_foreach_rl_plat(plat, {
    RC_ASSERT((*inv_nrl)[0][plat]);
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*inv_nrl)[section + 1][plat] != apuc->rl[section][plat]);
    });
  });
  lepton_free_rl(inv_nrl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_erl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *inv_erl = lepton_inv_erl(apuc);
  lepton_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * LEPTON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + LEPTON_NUM_PLATS_PER_HALF_BANK;
    lepton_foreach_rl_section(section, {
      RC_ASSERT((*inv_erl)[section][upper_plat - 1]);
      lepton_foreach_range(plat, lower_plat, upper_plat - 1, {
        RC_ASSERT((*inv_erl)[section][plat] != apuc->rl[section][plat + 1]);
      });
    });
  });
  lepton_free_rl(inv_erl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_wrl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *inv_wrl = lepton_inv_wrl(apuc);
  lepton_foreach_half_bank(half_bank, {
    size_t lower_plat = half_bank * LEPTON_NUM_PLATS_PER_HALF_BANK;
    size_t upper_plat = lower_plat + LEPTON_NUM_PLATS_PER_HALF_BANK;
    lepton_foreach_rl_section(section, {
      RC_ASSERT((*inv_wrl)[section][lower_plat]);
      lepton_foreach_range(plat, lower_plat + 1, upper_plat, {
        RC_ASSERT((*inv_wrl)[section][plat] != apuc->rl[section][plat - 1]);
      });
    });
  });
  lepton_free_rl(inv_wrl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_srl, ()) {
  uint32_t rl_seed = lepton_gen_seed();
  lepton_randomize_rl(&apuc->rl, rl_seed);
  lepton_rl_t *inv_srl = lepton_inv_srl(apuc);
  lepton_foreach_rl_plat(plat, {
    RC_ASSERT((*inv_srl)[15][plat]);
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      RC_ASSERT((*inv_srl)[section][plat] != apuc->rl[section + 1][plat]);
    });
  });
  lepton_free_rl(inv_srl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, ggl, ()) {
  uint32_t ggl_seed = lepton_gen_seed();
  lepton_randomize_ggl(&apuc->ggl, ggl_seed);
  lepton_ggl_t *ggl = lepton_ggl(apuc);
  RC_ASSERT(lepton_ggl_eq(ggl, &apuc->ggl));
  lepton_free_ggl(ggl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_ggl, ()) {
  uint32_t inv_ggl_seed = lepton_gen_seed();
  lepton_randomize_ggl(&apuc->ggl, inv_ggl_seed);
  lepton_ggl_t *inv_ggl = lepton_inv_ggl(apuc);
  lepton_foreach_ggl_group_plat(group, plat, {
    RC_ASSERT((*inv_ggl)[group][plat] != apuc->ggl[group][plat]);
  });
  lepton_free_ggl(inv_ggl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, gl, ()) {
  uint32_t gl_seed = lepton_gen_seed();
  lepton_randomize_gl(&apuc->gl, gl_seed);
  lepton_gl_t *gl = lepton_gl(apuc);
  RC_ASSERT(lepton_gl_eq(gl, &apuc->gl));
  lepton_free_gl(gl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_gl, ()) {
  uint32_t inv_gl_seed = lepton_gen_seed();
  lepton_randomize_gl(&apuc->gl, inv_gl_seed);
  lepton_gl_t *inv_gl = lepton_inv_gl(apuc);
  lepton_foreach_gl_plat(plat, {
    RC_ASSERT((*inv_gl)[plat] != apuc->gl[plat]);
  });
  lepton_free_gl(inv_gl);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rsp16, ()) {
  uint32_t rsp16_seed = lepton_gen_seed();
  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_rsp16_t *rsp16 = lepton_rsp16(apuc);
  RC_ASSERT(lepton_rsp16_eq(rsp16, &apuc->rsp16));
  lepton_free_rsp16(rsp16);
}

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, inv_rsp16, ()) {
  uint32_t inv_rsp16_seed = lepton_gen_seed();
  lepton_randomize_rsp16(&apuc->rsp16, inv_rsp16_seed);
  lepton_rsp16_t *inv_rsp16 = lepton_inv_rsp16(apuc);
  lepton_foreach_rsp16_section_plat(section, plat, {
    RC_ASSERT((*inv_rsp16)[section][plat] != apuc->rsp16[section][plat]);
  });
  lepton_free_rsp16(inv_rsp16);
}
