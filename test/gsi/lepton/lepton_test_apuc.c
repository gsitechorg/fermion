#include "lepton_test_ggl_from_rl.h"
#include "lepton_test_gl_from_rl.h"
#include "lepton_test_rl_from_sb.h"
#include "lepton_test_rl_from_sb_or_src.h"
#include "lepton_test_rl_from_src.h"
#include "lepton_test_rl_or_eq_sb.h"
#include "lepton_test_rl_xor_eq_sb.h"
#include "lepton_test_sb_from_src.h"
#include "lepton_test_src.h"

void lepton_test_apuc() {
  lepton_test_ggl_from_rl();
  lepton_test_gl_from_rl();
  lepton_test_rl_from_sb();
  lepton_test_rl_from_sb_or_src();
  lepton_test_rl_from_src();
  lepton_test_rl_or_eq_sb();
  lepton_test_rl_xor_eq_sb();
  lepton_test_sb_from_src();
  lepton_test_src();
}
