#ifndef __LEPTON_TEST_APUC_H__
#define __LEPTON_TEST_APUC_H__

#include <stdbool.h>
#include <stdio.h>

#include <gsi/lepton/apuc.h>

#include <gtest/gtest.h>

class LeptonAPUCTest : public ::testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;
  lepton_apuc_t *apuc;
};

#define LEPTON_ASSERT_VR_EQ(actual, expected)                                  \
  lepton_foreach_vr_section_plat(section, plat, {                              \
    bool actual_value = (*actual)[section][plat];                              \
    bool expected_value = (*expected)[section][plat];                          \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << section << "][" << plat << "] to be "    \
        << expected_value << " but was " << actual_value;                      \
  });

#define LEPTON_ASSERT_VR_EQ_GL(actual, expected)                               \
  lepton_foreach_vr_section_plat(section, plat, {                              \
    bool actual_value = (*actual)[section][plat];                              \
    bool expected_value = (*expected)[plat];                                   \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << section << "][" << plat << "] to be "    \
        << expected_value << " but was " << actual_value;                      \
  });

#define LEPTON_ASSERT_VR_EQ_GGL(actual, expected)                              \
  lepton_foreach_vr_section_plat(section, plat, {                              \
    bool actual_value = (*actual)[section][plat];                              \
    bool expected_value = (*expected)[section / LEPTON_NUM_GROUPS][plat];      \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << section << "][" << plat << "] to be "    \
        << expected_value << " but was " << actual_value;                      \
  });

#define LEPTON_ASSERT_VR_EQ_RSP16(actual, expected)                            \
  lepton_foreach_vr_section_plat(section, plat, {                              \
    bool actual_value = (*actual)[section][plat];                              \
    bool expected_value = (*expected)[section][plat / 16];                     \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << section << "][" << plat << "] to be "    \
        << expected_value << " but was " << actual_value;                      \
  });

#define LEPTON_ASSERT_GGL_EQ(actual, expected)                                 \
  lepton_foreach_ggl_group_plat(group, plat, {                                 \
    bool actual_value = (*actual)[group][plat];                                \
    bool expected_value = (*expected)[group][plat];                            \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << group << "][" << plat << "] to be "      \
        << expected_value << " but was " << actual_value;                      \
  });

#define LEPTON_ASSERT_GL_EQ(actual, expected)                                  \
  lepton_foreach_gl_plat(plat, {                                               \
    bool actual_value = (*actual)[plat];                                       \
    bool expected_value = (*expected)[plat];                                   \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << plat << "] to be " << expected_value     \
        << " but was " << actual_value;                                        \
  });

#define LEPTON_ASSERT_L1_EQ LEPTON_ASSERT_GGL_EQ

#define LEPTON_ASSERT_L2_EQ(actual, expected)                                  \
  lepton_foreach_l2_plat(plat, {                                               \
    bool actual_value = (*actual)[plat];                                       \
    bool expected_value = (*expected)[plat];                                   \
    ASSERT_EQ(actual_value, expected_value)                                    \
        << "Expected " #actual "[" << plat << "] to be " << expected_value     \
        << " but was " << actual_value;                                        \
  });

#define LEPTON_ASSERT_LGL_EQ LEPTON_ASSERT_L2_EQ

#endif // __LEPTON_TEST_APUC_H__
