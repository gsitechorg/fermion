#include <string.h>

#include <gsi/baryon/constants.h>

#include "comparators.h"

bool baryon_wordline_eq(baryon_wordline_t *lhs, baryon_wordline_t *rhs) {
  return memcmp(lhs, rhs, BARYON_WORDLINE_SIZE) == 0;
}

bool baryon_vr_eq(baryon_vr_t *lhs, baryon_vr_t *rhs) {
  return memcmp(lhs, rhs, BARYON_VR_SIZE) == 0;
}

bool baryon_vr_eq_gl(baryon_vr_t *lhs, baryon_gl_t *rhs) {
  baryon_foreach_vr_section(section, {
    baryon_wordline_t *wordline = &(*lhs)[section];
    if (memcmp(wordline, rhs, BARYON_WORDLINE_SIZE) != 0) {
      return false;
    }
  });
  return true;
}

bool baryon_vr_eq_ggl(baryon_vr_t *lhs, baryon_ggl_t *rhs) {
  baryon_foreach_vr_section_plat(section, plat, {
    bool lhs_value = (*lhs)[section][plat];
    bool rhs_value = (*rhs)[section / BARYON_NUM_GROUPS][plat];
    if (lhs_value != rhs_value) {
      return false;
    }
  });
  return true;
}

bool baryon_vr_eq_rsp16(baryon_vr_t *lhs, baryon_rsp16_t *rhs) {
  baryon_foreach_vr_section_plat(section, plat, {
    bool lhs_value = (*lhs)[section][plat];
    bool rhs_value = (*rhs)[section][plat / 16];
    if (lhs_value != rhs_value) {
      return false;
    }
  });
  return true;
}

bool baryon_ggl_eq(baryon_ggl_t *lhs, baryon_ggl_t *rhs) {
  return memcmp(lhs, rhs, BARYON_GGL_SIZE) == 0;
}

bool baryon_gl_eq(baryon_gl_t *lhs, baryon_gl_t *rhs) {
  return memcmp(lhs, rhs, BARYON_GL_SIZE) == 0;
}

bool baryon_l2_eq(baryon_l2_t *lhs, baryon_l2_t *rhs) {
  return memcmp(lhs, rhs, BARYON_L2_SIZE) == 0;
}

bool baryon_rsp16_eq(baryon_rsp16_t *lhs, baryon_rsp16_t *rhs) {
  return memcmp(lhs, rhs, BARYON_RSP16_SIZE) == 0;
}

bool baryon_rsp16_eq_rl(baryon_rsp16_t *lhs, baryon_rl_t *rhs) {
  return baryon_rl_eq_rsp16(rhs, lhs);
}

bool baryon_rsp16_eq_rsp256(baryon_rsp16_t *lhs, baryon_rsp256_t *rhs) {
  baryon_foreach_rsp256_plat(rsp256_plat, {
    size_t lower_rsp16 = rsp256_plat * 16;
    size_t upper_rsp16 = lower_rsp16 + 16;
    baryon_foreach_rsp16_section(section, {
      bool rhs_value = (*rhs)[section][rsp256_plat];
      baryon_foreach_range(rsp16_plat, lower_rsp16, upper_rsp16, {
        bool lhs_value = (*lhs)[section][rsp16_plat];
        if (lhs_value != rhs_value) {
          return false;
        }
      });
    });
  });
  return true;
}

bool baryon_rsp256_eq_rsp16(baryon_rsp256_t *lhs, baryon_rsp16_t *rhs) {
  baryon_foreach_rsp256_plat(rsp256_plat, {
    size_t lower_rsp16 = rsp256_plat * 16;
    size_t upper_rsp16 = lower_rsp16 + 16;
    baryon_foreach_rsp16_section(section, {
      bool any = false;
      baryon_foreach_range(rsp16_plat, lower_rsp16, upper_rsp16, {
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

bool baryon_rsp256_eq_rsp2k(baryon_rsp256_t *lhs, baryon_rsp2k_t *rhs) {
  baryon_foreach_rsp2k_plat(rsp2k_plat, {
    size_t lower_rsp256 = rsp2k_plat * 8;
    size_t upper_rsp256 = lower_rsp256 + 8;
    baryon_foreach_rsp256_section(section, {
      bool rhs_value = (*rhs)[section][rsp2k_plat];
      baryon_foreach_range(rsp256_plat, lower_rsp256, upper_rsp256, {
        bool lhs_value = (*lhs)[section][rsp256_plat];
        if (lhs_value != rhs_value) {
          return false;
        }
      });
    });
  });
  return true;
}

bool baryon_rsp2k_eq_rsp256(baryon_rsp2k_t *lhs, baryon_rsp256_t *rhs) {
  baryon_foreach_rsp2k_plat(rsp2k_plat, {
    size_t lower_rsp256 = rsp2k_plat * 8;
    size_t upper_rsp256 = lower_rsp256 + 8;
    baryon_foreach_rsp256_section(section, {
      bool any = false;
      baryon_foreach_range(rsp256_plat, lower_rsp256, upper_rsp256, {
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

bool baryon_rsp2k_eq_rsp32k(baryon_rsp2k_t *lhs, baryon_rsp32k_t *rhs) {
  baryon_foreach_half_bank(half_bank, {
    bool rhs_value = (*rhs)[half_bank];
    baryon_foreach_rsp2k_section(section, {
      bool lhs_value = (*lhs)[section][half_bank];
      if (lhs_value != rhs_value) {
        return false;
      }
    });
  });
  return true;
}

bool baryon_rsp32k_eq_rsp2k(baryon_rsp32k_t *lhs, baryon_rsp2k_t *rhs) {
  baryon_foreach_half_bank(half_bank, {
    bool any = false;
    baryon_foreach_rsp2k_section(section, {
      any |= (*rhs)[section][half_bank];
    });
    if ((*lhs)[half_bank] != any) {
      return false;
    }
  });
  return true;
}
