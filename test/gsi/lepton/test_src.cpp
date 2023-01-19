#include "test_apuc.h"

TEST_F(LeptonAPUCTest, nrl) {
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_foreach_rl_plat(plat, {
    ASSERT_FALSE((*nrl)[0][plat])
        << "Expected nrl[0][" << plat << "] to be 0 but was 1\n";
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      ASSERT_EQ((*nrl)[section + 1][plat], apuc->rl[section][plat])
          << "Expected nrl[" << section + 1 << "][" << plat << "] to be "
          << apuc->rl[section][plat] << " but was "
          << (*nrl)[section + 1][plat];
    });
  });
}

TEST_F(LeptonAPUCTest, srl) {
  lepton_rl_t *srl = lepton_srl(apuc);
  lepton_foreach_rl_plat(plat, {
    ASSERT_FALSE((*srl)[15][plat])
        << "Expected srl[15][" << plat << "] to be 0 but was 1\n";
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      ASSERT_EQ((*srl)[section][plat], apuc->rl[section + 1][plat])
          << "Expected srl[" << section << "][" << plat << "] to be "
          << apuc->rl[section + 1][plat] << " but was "
          << (*srl)[section][plat];
    });
  });
}

TEST_F(LeptonAPUCTest, inv_rl) {
  lepton_rl_t *inv_rl = lepton_inv_rl(apuc);
  lepton_foreach_rl_section_plat(section, plat, {
    ASSERT_EQ((*inv_rl)[section][plat], !apuc->rl[section][plat])
        << "Expected inv_rl[" << section << "][" << plat << "] to be "
        << !apuc->rl[section][plat] << " but was " << (*inv_rl)[section][plat];
  });
}
