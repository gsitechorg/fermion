#include <string.h>

#include <gsi/lepton/constants.h>

#include "comparators.h"

bool lepton_wordline_eq(lepton_wordline_t *actual, lepton_wordline_t *expected) {
  return memcmp(actual, expected, LEPTON_WORDLINE_SIZE) == 0;
}

bool lepton_vr_eq(lepton_vr_t *actual, lepton_vr_t *expected) {
  return memcmp(actual, expected, LEPTON_VR_SIZE) == 0;
}

bool lepton_vr_eq_gl(lepton_vr_t *actual, lepton_gl_t *expected) {
  lepton_foreach_vr_section(section, {
    lepton_wordline_t *wordline = &(*actual)[section];
    if (memcmp(wordline, expected, LEPTON_WORDLINE_SIZE) != 0) {
      return false;
    }
  });
  return true;
}

bool lepton_vr_eq_ggl(lepton_vr_t *actual, lepton_ggl_t *expected) {
  lepton_foreach_vr_section_plat(section, plat, {
    bool actual_value = (*actual)[section][plat];
    bool expected_value = (*expected)[section / LEPTON_NUM_GROUPS][plat];
    if (actual_value != expected_value) {
      return false;
    }
  });
  return true;
}

bool lepton_vr_eq_rsp16(lepton_vr_t *actual, lepton_rsp16_t *expected) {
  lepton_foreach_vr_section_plat(section, plat, {
    bool actual_value = (*actual)[section][plat];
    bool expected_value = (*expected)[section][plat / 16];
    if (actual_value != expected_value) {
      return false;
    }
  });
  return true;
}

bool lepton_ggl_eq(lepton_ggl_t *actual, lepton_ggl_t *expected) {
  return memcmp(actual, expected, LEPTON_GGL_SIZE) == 0;
}

bool lepton_gl_eq(lepton_gl_t *actual, lepton_gl_t *expected) {
  return memcmp(actual, expected, LEPTON_GL_SIZE) == 0;
}

bool lepton_l2_eq(lepton_l2_t *actual, lepton_l2_t *expected) {
  return memcmp(actual, expected, LEPTON_L2_SIZE) == 0;
}

bool lepton_rsp16_eq(lepton_rsp16_t *actual, lepton_rsp16_t *expected) {
  return memcmp(actual, expected, LEPTON_RSP16_SIZE) == 0;
}
