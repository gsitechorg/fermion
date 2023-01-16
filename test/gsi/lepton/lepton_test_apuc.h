#ifndef __LEPTON_TEST_APUC_H__
#define __LEPTON_TEST_APUC_H__

#include <stdbool.h>
#include <stdio.h>

#include <gsi/lepton/apuc.h>

#include "../../lepton_test.h"

#define LEPTON_RUN_APUC_TEST(test_fn)                                          \
  {                                                                            \
    LEPTON_TEST_PASSED = true;                                                 \
    LEPTON_NUM_TESTS += 1;                                                     \
    lepton_apuc_t *apuc = malloc(sizeof(lepton_apuc_t));                       \
    lepton_init_apuc(apuc);                                                    \
    lepton_repeatably_randomize_apuc(apuc);                                    \
    test_fn(apuc);                                                             \
    if (LEPTON_TEST_PASSED) {                                                  \
      printf("[SUCCESS] " #test_fn "\n");                                      \
    } else {                                                                   \
      printf("[FAILURE] " #test_fn "\n");                                      \
      LEPTON_NUM_FAILED_TESTS += 1;                                            \
    }                                                                          \
    lepton_free_apuc(apuc);                                                    \
  }

#define LEPTON_ASSERT_VR_EQ(actual, expected)                                    \
  if (LEPTON_TEST_PASSED) {                                                      \
    lepton_foreach_vr_section_plat(section, plat, {                              \
      bool actual_value = (*actual)[section][plat];                              \
      bool expected_value = (*expected)[section][plat];                          \
      if (actual_value != expected_value) {                                      \
        LEPTON_FAIL_TEST("Expected " #actual "[%zu][%zu] to be %d but was %d\n", \
                         section, plat, actual_value, expected_value);           \
        goto assertion_done;                                                     \
      }                                                                          \
    });                                                                          \
    assertion_done:                                                              \
    ;;                                                                           \
  }

#define LEPTON_ASSERT_VR_EQ_GL(actual, expected)                                 \
  if (LEPTON_TEST_PASSED) {                                                      \
    lepton_foreach_vr_section_plat(section, plat, {                              \
      bool actual_value = (*actual)[section][plat];                              \
      bool expected_value = (*expected)[plat];                                   \
      if (actual_value != expected_value) {                                      \
        LEPTON_FAIL_TEST("Expected " #actual "[%zu][%zu] to be %d but was %d\n", \
                         section, plat, actual_value, expected_value);           \
        goto assertion_done;                                                     \
      }                                                                          \
    });                                                                          \
    assertion_done:                                                              \
    ;;                                                                           \
  }

#define LEPTON_ASSERT_VR_EQ_GGL(actual, expected)                                \
  if (LEPTON_TEST_PASSED) {                                                      \
    lepton_foreach_vr_section_plat(section, plat, {                              \
      bool actual_value = (*actual)[section][plat];                              \
      bool expected_value = (*expected)[section / LEPTON_NUM_GROUPS][plat];      \
      if (actual_value != expected_value) {                                      \
        LEPTON_FAIL_TEST("Expected " #actual "[%zu][%zu] to be %d but was %d\n", \
                         section, plat, actual_value, expected_value);           \
        goto assertion_done;                                                     \
      }                                                                          \
    });                                                                          \
    assertion_done:                                                              \
    ;;                                                                           \
  }

#define LEPTON_ASSERT_VR_EQ_RSP16(actual, expected)                              \
  if (LEPTON_TEST_PASSED) {                                                      \
    lepton_foreach_vr_section_plat(section, plat, {                              \
      bool actual_value = (*actual)[section][plat];                              \
      bool expected_value = (*expected)[section][plat / 16];                     \
      if (actual_value != expected_value) {                                      \
        LEPTON_FAIL_TEST("Expected " #actual "[%zu][%zu] to be %d but was %d\n", \
               section, plat, actual_value, expected_value);                     \
        goto assertion_done;                                                     \
      }                                                                          \
    });                                                                          \
    assertion_done:                                                              \
    ;;                                                                           \
  }

#define LEPTON_ASSERT_GGL_EQ(actual, expected)                                   \
  if (LEPTON_TEST_PASSED) {                                                      \
    lepton_foreach_ggl_group_plat(group, plat, {                                 \
      bool actual_value = (*actual)[group][plat];                                \
      bool expected_value = (*expected)[group][plat];                            \
      if (actual_value != expected_value) {                                      \
        LEPTON_FAIL_TEST("Expected " #actual "[%zu][%zu] to be %d but was %d\n", \
                         group, plat, actual_value, expected_value);             \
        goto assertion_done;                                                     \
      }                                                                          \
    });                                                                          \
    assertion_done:                                                              \
    ;;                                                                           \
  }

#define LEPTON_ASSERT_GL_EQ(actual, expected)                               \
  if (LEPTON_TEST_PASSED) {                                                 \
    lepton_foreach_gl_plat(plat, {                                          \
      bool actual_value = (*actual)[plat];                                  \
      bool expected_value = (*expected)[plat];                              \
      if (actual_value != expected_value) {                                 \
        LEPTON_FAIL_TEST("Expected " #actual "[%zu] to be %d but was %d\n", \
                         plat, actual_value, expected_value);               \
        goto assertion_done;                                                \
      }                                                                     \
    });                                                                     \
    assertion_done:                                                         \
    ;;                                                                      \
  }

void lepton_test_apuc(void);

#endif // __LEPTON_TEST_APUC_H__
