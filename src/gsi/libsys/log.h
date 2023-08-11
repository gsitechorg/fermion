/* By Dylon Edwards
 *
 * Copyright 2019 - 2023 GSI Technology, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the “Software”), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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
