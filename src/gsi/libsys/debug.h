#ifndef __GSI__BARYON__LIBSYS__DEBUG_H__
#define __GSI__BARYON__LIBSYS__DEBUG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"

/*
 * if level < 0, gsi_debug() acts like gsi_info()
 */
#define gsi_debug(_level, ...)                                                 \
  if ((_level) < 0) {                                                          \
    _gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_INFO, "INFO",               \
             ##__VA_ARGS__);                                                   \
  } else {                                                                     \
    _gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_DEBUG, "DEBUG",             \
             ##__VA_ARGS__);                                                   \
  }

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBSYS__DEBUG_H__
