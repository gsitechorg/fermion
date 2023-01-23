#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rsp_end, ()) {
  uint32_t rsp16_seed = lepton_gen_seed();
  uint32_t rsp256_seed = lepton_gen_seed();
  uint32_t rsp2k_seed = lepton_gen_seed();
  uint32_t rsp32k_seed = lepton_gen_seed();

  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  lepton_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  lepton_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);

  lepton_rsp_end(apuc);

  lepton_foreach_rsp16_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp16[section][plat]);
  });
  lepton_foreach_rsp256_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp256[section][plat]);
  });
  lepton_foreach_rsp2k_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp2k[section][plat]);
  });
  lepton_foreach_rsp32k_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp32k[section][plat]);
  });

  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_randomize_rsp256(&apuc->rsp256, rsp256_seed);
  lepton_randomize_rsp2k(&apuc->rsp2k, rsp2k_seed);
  lepton_randomize_rsp32k(&apuc->rsp32k, rsp32k_seed);

  apuc->in_place = false;
  lepton_rsp_patches_t *patch = lepton_rsp_end(apuc);
  lepton_patch_rsps(apuc, patch);
  lepton_free_rsp_patches(patch);
  apuc->in_place = true;

  lepton_foreach_rsp16_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp16[section][plat]);
  });
  lepton_foreach_rsp256_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp256[section][plat]);
  });
  lepton_foreach_rsp2k_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp2k[section][plat]);
  });
  lepton_foreach_rsp32k_section_plat(section, plat, {
    RC_ASSERT(!apuc->rsp32k[section][plat]);
  });
}
