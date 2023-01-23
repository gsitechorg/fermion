#include <gtest/gtest.h>

#include <rapidcheck/gtest.h>

#include "comparators.h"
#include "fixtures.h"
#include "generators.h"

RC_GTEST_FIXTURE_PROP(LeptonAPUCTest, rwinh_standard_use, ()) {
  size_t out_vp = 0;
  size_t mrk_vp = 1;

  lepton_sm_t mask = lepton_gen_mask();

  uint32_t out_seed = lepton_gen_seed();
  uint32_t mrk_seed = lepton_gen_seed();
  uint32_t rl_seed = lepton_gen_seed();

  size_t num_vrs = 1;
  lepton_vr_t *out_vrs[] = { &apuc->vrs[out_vp] };
  lepton_vr_t *mrk_vrs[] = {&apuc->vrs[mrk_vp]};

  lepton_rsp16_t *src = lepton_inv_rsp16(apuc);
  lepton_src_t src_type = LEPTON_SRC_INV_RSP16;

  lepton_randomize_vr(&apuc->vrs[out_vp], out_seed);
  lepton_randomize_vr(&apuc->vrs[mrk_vp], mrk_seed);
  lepton_randomize_rl(&apuc->rl, rl_seed);

  lepton_vr_t *expected = (lepton_vr_t *) malloc(sizeof(lepton_vr_t));
  lepton_foreach_masked_section(mask, section, {
    memcpy(&(*expected)[section],
           &apuc->vrs[mrk_vp][section],
           LEPTON_WORDLINE_SIZE);
  });
  lepton_foreach_unmasked_section(mask, section, {
    memcpy(&(*expected)[section],
           &apuc->vrs[out_vp][section],
           LEPTON_WORDLINE_SIZE);
  });

  lepton_rl_from_sb(apuc, mask, mrk_vrs, num_vrs);
  lepton_rwinh_set(apuc, mask);

  lepton_sb_from_src(apuc, mask, out_vrs, num_vrs, src, src_type);

  lepton_rwinh_rst(apuc, mask, false);

  RC_ASSERT(lepton_vr_eq(&apuc->vrs[out_vp], expected));

  lepton_free_vr(expected);
  lepton_free_rsp16(src);
}
