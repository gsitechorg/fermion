#include <string.h>

#include <gsi/lepton/constants.h>

#include "comparators.h"

bool lepton_wordline_eq(lepton_wordline_t *lhs, lepton_wordline_t *rhs) {
  return memcmp(lhs, rhs, LEPTON_WORDLINE_SIZE) == 0;
}

bool lepton_vr_eq(lepton_vr_t *lhs, lepton_vr_t *rhs) {
  return memcmp(lhs, rhs, LEPTON_VR_SIZE) == 0;
}

bool lepton_vr_eq_gl(lepton_vr_t *lhs, lepton_gl_t *rhs) {
  lepton_foreach_vr_section(section, {
    lepton_wordline_t *wordline = &(*lhs)[section];
    if (memcmp(wordline, rhs, LEPTON_WORDLINE_SIZE) != 0) {
      return false;
    }
  });
  return true;
}

bool lepton_vr_eq_ggl(lepton_vr_t *lhs, lepton_ggl_t *rhs) {
  lepton_foreach_vr_section_plat(section, plat, {
    bool lhs_value = (*lhs)[section][plat];
    bool rhs_value = (*rhs)[section / LEPTON_NUM_GROUPS][plat];
    if (lhs_value != rhs_value) {
      return false;
    }
  });
  return true;
}

bool lepton_vr_eq_rsp16(lepton_vr_t *lhs, lepton_rsp16_t *rhs) {
  lepton_foreach_vr_section_plat(section, plat, {
    bool lhs_value = (*lhs)[section][plat];
    bool rhs_value = (*rhs)[section][plat / 16];
    if (lhs_value != rhs_value) {
      return false;
    }
  });
  return true;
}

bool lepton_ggl_eq(lepton_ggl_t *lhs, lepton_ggl_t *rhs) {
  return memcmp(lhs, rhs, LEPTON_GGL_SIZE) == 0;
}

bool lepton_gl_eq(lepton_gl_t *lhs, lepton_gl_t *rhs) {
  return memcmp(lhs, rhs, LEPTON_GL_SIZE) == 0;
}

bool lepton_l2_eq(lepton_l2_t *lhs, lepton_l2_t *rhs) {
  return memcmp(lhs, rhs, LEPTON_L2_SIZE) == 0;
}

bool lepton_rsp16_eq(lepton_rsp16_t *lhs, lepton_rsp16_t *rhs) {
  return memcmp(lhs, rhs, LEPTON_RSP16_SIZE) == 0;
}

bool lepton_rsp16_eq_rl(lepton_rsp16_t *lhs, lepton_rl_t *rhs) {
  return lepton_rl_eq_rsp16(rhs, lhs);
}

bool lepton_rsp16_eq_rsp256(lepton_rsp16_t *lhs, lepton_rsp256_t *rhs) {
  lepton_foreach_rsp256_plat(rsp256_plat, {
    size_t lower_rsp16 = rsp256_plat * 16;
    size_t upper_rsp16 = lower_rsp16 + 16;
    lepton_foreach_rsp16_section(section, {
      bool rhs_value = (*rhs)[section][rsp256_plat];
      lepton_foreach_range(rsp16_plat, lower_rsp16, upper_rsp16, {
        bool lhs_value = (*lhs)[section][rsp16_plat];
        if (lhs_value != rhs_value) {
          return false;
        }
      });
    });
  });
  return true;
}

bool lepton_rsp256_eq_rsp16(lepton_rsp256_t *lhs, lepton_rsp16_t *rhs) {
  lepton_foreach_rsp256_plat(rsp256_plat, {
    size_t lower_rsp16 = rsp256_plat * 16;
    size_t upper_rsp16 = lower_rsp16 + 16;
    lepton_foreach_rsp16_section(section, {
      bool any = false;
      lepton_foreach_range(rsp16_plat, lower_rsp16, upper_rsp16, {
        if ((*rhs)[section][rsp16_plat]) {
          any = true;
          break;
        }
      });
      if ((*lhs)[section][rsp256_plat] != any) {
        return false;
      }
    });
  });
  return true;
}

bool lepton_rsp256_eq_rsp2k(lepton_rsp256_t *lhs, lepton_rsp2k_t *rhs) {
  lepton_foreach_rsp2k_plat(rsp2k_plat, {
    size_t lower_rsp256 = rsp2k_plat * 8;
    size_t upper_rsp256 = lower_rsp256 + 8;
    lepton_foreach_rsp256_section(section, {
      bool rhs_value = (*rhs)[section][rsp2k_plat];
      lepton_foreach_range(rsp256_plat, lower_rsp256, upper_rsp256, {
        bool lhs_value = (*lhs)[section][rsp256_plat];
        if (lhs_value != rhs_value) {
          return false;
        }
      });
    });
  });
  return true;
}

bool lepton_rsp2k_eq_rsp256(lepton_rsp2k_t *lhs, lepton_rsp256_t *rhs) {
  lepton_foreach_rsp2k_plat(rsp2k_plat, {
    size_t lower_rsp256 = rsp2k_plat * 8;
    size_t upper_rsp256 = lower_rsp256 + 8;
    lepton_foreach_rsp256_section(section, {
      bool any = false;
      lepton_foreach_range(rsp256_plat, lower_rsp256, upper_rsp256, {
        if ((*rhs)[section][rsp256_plat]) {
          any = true;
          break;
        }
      });
      if ((*lhs)[section][rsp2k_plat] != any) {
        return false;
      }
    });
  });
  return true;
}

bool lepton_rsp2k_eq_rsp32k(lepton_rsp2k_t *lhs, lepton_rsp32k_t *rhs) {
  lepton_foreach_rsp32k_plat(rsp32k_plat, {
    size_t lower_rsp2k = rsp32k_plat * 16;
    size_t upper_rsp2k = lower_rsp2k + 16;
    lepton_foreach_rsp2k_section(section, {
      bool rhs_value = (*rhs)[section][rsp32k_plat];
      lepton_foreach_range(rsp2k_plat, lower_rsp2k, upper_rsp2k, {
        bool lhs_value = (*lhs)[section][rsp2k_plat];
        if (lhs_value != rhs_value) {
          return false;
        }
      });
    });
  });
  return true;
}

bool lepton_rsp32k_eq_rsp2k(lepton_rsp32k_t *lhs, lepton_rsp2k_t *rhs) {
  lepton_foreach_rsp32k_plat(rsp32k_plat, {
    size_t lower_rsp2k = rsp32k_plat * 16;
    size_t upper_rsp2k = lower_rsp2k + 16;
    lepton_foreach_rsp2k_section(section, {
      bool any = false;
      lepton_foreach_range(rsp2k_plat, lower_rsp2k, upper_rsp2k, {
        if ((*rhs)[section][rsp2k_plat]) {
          any = true;
          break;
        }
      });
      if ((*lhs)[section][rsp32k_plat] != any) {
        return false;
      }
    });
  });
  return true;
}
