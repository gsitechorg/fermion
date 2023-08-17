/* By Dylon Edwards
 */

#ifndef __GSI__BARYON__LIBSYS__TYPES_H__
#define __GSI__BARYON__LIBSYS__TYPES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define GSI_PACKED __attribute__((packed))

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif // MAX

#define likely(x) __builtin_expect((x), true)
#define unlikely(x) __builtin_expect((x), false)

typedef uint16_t u16;
typedef int gsi_status_t;
typedef signed int gsi_prod_int_t;
typedef gsi_prod_int_t gsi_prod_status_t;

#ifdef __cplusplus
}
#endif

#endif // __GSI__BARYON__LIBSYS__TYPES_H__
