#ifndef BARYON_GSI_LIBSYS_LOG_H
#define BARYON_GSI_LIBSYS_LOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#define GSI_LOG_TRUNC_STR	"~~~\n"
//the last ' _' postfix wiil be replaced with 0-9 file index.
//#define LOG_ARC_FILE_PATH "/run/media/mmcblk0p1/logs/gsi_log_#.log"
#define LOG_ARC_FILE_PATH "/run/media/mmcblk0p2/logs/"
//#define LOG_ARC_FILE_PATH_1 "/run/media/mmcblk0p1/logs/

enum gsi_log_level {
	GSI_LOG_IGNORE,
	GSI_LOG_DEBUG,
	GSI_LOG_PRINTF,
	GSI_LOG_INFO,
	GSI_LOG_WARNING,
	GSI_LOG_ERROR,
	GSI_LOG_FATAL,
};

extern enum gsi_log_level gsi_min_log_level;
extern const char *_gsi_log_level_names[];

extern void _gsi_log(const char *file, int line, const char *func, enum gsi_log_level level,
                     const char *prompt, const char *fmt, ...) __attribute__((format(printf, 6, 7)));
extern void _gsi_log_fatal(const char *file, int line, const char *func, const char *prompt, const char *fmt, ...) __attribute__((format(printf, 5, 6), noreturn));
extern int _gsi_log_sn(char *buf, unsigned buf_sz, const char *file, int line, const char *func, enum gsi_log_level level,
                       const char *prompt, const char *trunc_str, const char *fmt, ...) __attribute__((format(printf, 9, 10)));

extern void _gsi_vlog(const char *file, int line, const char *func, enum gsi_log_level level,
                      const char *prompt, const char *fmt, va_list ap);
extern int _gsi_vlog_sn(char *buf, unsigned buf_sz, const char *file, int line, const char *func, enum gsi_log_level level,
                        const char *prompt, const char *trunc_str, const char *fmt, va_list ap);

typedef void gsi_log_writer_t(enum gsi_log_level level, const char *buf, unsigned size);
extern gsi_log_writer_t *gsi_log_writer;
extern void gsi_log_write(enum gsi_log_level level, const char *buf, unsigned size);

#if defined(GSI_LIBSYS_ARCHS36)
extern void gsi_set_log_write(void(*__gsi_log_write)(enum gsi_log_level, const char*, unsigned));
#endif
extern int gsi_get_log_fd(void);
extern int gsi_set_log_fd(int fd);
extern int get_gsi_log_write_counter(void);
extern void clear_gsi_log_write_counter(void);

extern void gsi_set_log_to_stdout(); /* set of log to stdout */
extern void gsi_set_log_to_syslog(); /* set of log to syslog */

#define _gsi_log_ext(level, prompt, ...)	_gsi_log(__FILE__, __LINE__, __func__, level, prompt, __VA_ARGS__)

#define gsi_log(...)		_gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_INFO, NULL, ##__VA_ARGS__)
#define gsi_info(...)		_gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_INFO, "INFO", ##__VA_ARGS__)
#define gsi_warning(...)	_gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_WARNING, "WARNING", ##__VA_ARGS__)
#define gsi_error(...)		_gsi_log(__FILE__, __LINE__, __func__, GSI_LOG_ERROR, "ERROR", ##__VA_ARGS__)
#define gsi_fatal(...)		_gsi_log_fatal(__FILE__, __LINE__, __func__, "FATAL", ##__VA_ARGS__)

void some_function2();

#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_LIBSYS_LOG_H
