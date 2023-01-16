#include "lepton_test_apuc.h"
#include "lepton_test_src.h"

void lepton_test_nrl(lepton_apuc_t *apuc) {
  lepton_rl_t *nrl = lepton_nrl(apuc);
  lepton_foreach_rl_plat(plat, {
    if ((*nrl)[0][plat] != false) {
      LEPTON_FAIL_TEST("Expected nrl[0][%zu] to be 0 but was 1\n", plat);
      goto assertion_done;
    }
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      if ((*nrl)[section + 1][plat] != apuc->rl[section][plat]) {
        LEPTON_FAIL_TEST("Expected nrl[%zu][%zu] to be %d but was %d\n",
                         section + 1, plat, apuc->rl[section][plat],
                         (*nrl)[section + 1][plat]);
        goto assertion_done;
      }
    });
  });
assertion_done:
  lepton_free_rl(nrl);
}

void lepton_test_srl(lepton_apuc_t *apuc) {
  lepton_rl_t *srl = lepton_srl(apuc);
  lepton_foreach_rl_plat(plat, {
    if ((*srl)[15][plat] != false) {
      LEPTON_FAIL_TEST("Expected srl[15][%zu] to be 0 but was 1\n", plat);
      goto assertion_done;
    }
    lepton_foreach_range(section, LEPTON_NUM_RL_SECTIONS - 1, {
      if ((*srl)[section][plat] != apuc->rl[section + 1][plat]) {
        LEPTON_FAIL_TEST("Expected srl[%zu][%zu] to be %d but was %d\n",
                         section, plat, apuc->rl[section + 1][plat],
                         (*srl)[section][plat]);
        goto assertion_done;
      }
    });
  });
assertion_done:
  lepton_free_rl(srl);
}

void lepton_test_inv_rl(lepton_apuc_t *apuc) {
  lepton_rl_t *inv_rl = lepton_inv_rl(apuc);
  lepton_foreach_rl_section_plat(section, plat, {
    if ((*inv_rl)[section][plat] != !apuc->rl[section][plat]) {
      LEPTON_FAIL_TEST("Expected inv_rl[%zu][%zu] to be %d but was %d\n",
                        section, plat, !apuc->rl[section][plat],
                        (*inv_rl)[section][plat]);
      goto assertion_done;
    }
  });
assertion_done:
  lepton_free_rl(inv_rl);
}

void lepton_test_src() {
  LEPTON_RUN_APUC_TEST(lepton_test_nrl);
  LEPTON_RUN_APUC_TEST(lepton_test_srl);
  LEPTON_RUN_APUC_TEST(lepton_test_inv_rl);
}
