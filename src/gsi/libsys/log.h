#ifndef __GSI__BARYON__LIBSYS__LOG_H__
#define __GSI__BARYON__LIBSYS__LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>

enum gsi_log_level {
	GSI_LOG_IGNORE,
	GSI_LOG_DEBUG,
	GSI_LOG_PRINTF,
	GSI_LOG_INFO,
	GSI_LOG_WARNING,
	GSI_LOG_ERROR,
	GSI_LOG_FATAL,
};

#define _gsi_log(file, line, func, level, prompt, ...)                         \
  {                                                                            \
    printf("[%s:%d:%s:%d] " prompt " ", file, line, func, level);              \
    printf(__VA_ARGS__);                                                       \
    printf("\n");                                                              \
  }

#define gsi_log(...)		  _gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_INFO, "", ##__VA_ARGS__)
#define gsi_info(...)		  _gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_INFO, "INFO", ##__VA_ARGS__)
#define gsi_warning(...)	_gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_WARNING, "WARNING", ##__VA_ARGS__)
#define gsi_error(...)		_gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_ERROR, "ERROR", ##__VA_ARGS__)
#define gsi_fatal(...)		_gsi_log_fatal(__FILE__, __LINE__, __func__, "FATAL", ##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBSYS__LOG_H__
