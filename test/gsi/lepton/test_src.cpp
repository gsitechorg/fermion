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
