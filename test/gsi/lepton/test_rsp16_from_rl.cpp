#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rsp16_from_rl, ()) {
  lepton_sm_t mask = lepton_gen_mask();

  uint32_t rsp16_seed = lepton_gen_seed();
  uint32_t rl_seed = lepton_gen_seed();

  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_randomize_rl(&apuc->rl, rl_seed);

  lepton_rsp16_t *expected = (lepton_rsp16_t *) malloc(sizeof(lepton_rsp16_t));

  lepton_foreach_masked_section(mask, section, {
    memset(&(*expected)[section], false, LEPTON_RSP16_SECTION_SIZE);
    lepton_foreach_rl_plat(rl_plat, {
      size_t rsp16_plat = rl_plat / 16;
      (*expected)[section][rsp16_plat] |= apuc->rl[section][rl_plat];
    });
  });

  lepton_foreach_unmasked_section(mask, section, {
      memcpy(&(*expected)[section],
             &apuc->rsp16[section],
             LEPTON_RSP16_SECTION_SIZE);
  });

  lepton_rsp16_from_rl(apuc, mask);
  RC_ASSERT(lepton_rsp16_eq(&apuc->rsp16, expected));

  lepton_randomize_rsp16(&apuc->rsp16, rsp16_seed);
  lepton_randomize_rl(&apuc->rl, rl_seed);

  apuc->in_place = false;
  lepton_rsp16_section_map_t *patch = lepton_rsp16_from_rl(apuc, mask);
  lepton_patch_partial_rsp16(apuc, patch);
  lepton_free_rsp16_section_map(patch);
  apuc->in_place = true;
  RC_ASSERT(lepton_rsp16_eq(&apuc->rsp16, expected));

  lepton_free_rsp16(expected);
}
