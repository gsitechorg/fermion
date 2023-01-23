#ifndef BARYON_GSI_LIBSYS_ASSERT_H
#define BARYON_GSI_LIBSYS_ASSERT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "log.h"

#define GSI_ASSERT_LOG(e, level, prompt) \
	(likely(e) ? true : (_gsi_log(__FILE__, __LINE__, __func__, level, prompt ": Assert failed", "(%s)", #e), false))
#define GSI_ASSERT_ERROR(e)	GSI_ASSERT_LOG(e, GSI_LOG_ERROR, "Error")
#define GSI_ASSERT_WARN(e)	GSI_ASSERT_LOG(e, GSI_LOG_WARNING, "Warning")

extern void (* gsi_assert_failed)(void);

#define GSI_ASSERT_ABORT(e)	(GSI_ASSERT_ERROR(e) || (gsi_assert_failed(), false))
#define GSI_ASSERT(e)		(void)GSI_ASSERT_ABORT(e)

#if defined(EXTRA_DEBUG_BUILD)
#define GSI_EXTRA_DEBUG_ASSERT(e)	GSI_ASSERT(e)
#define GSI_DEBUG_ASSERT(e)		GSI_ASSERT(e)
#elif defined(DEBUG_BUILD)
#define GSI_EXTRA_DEBUG_ASSERT(e)	((void)0)
#define GSI_DEBUG_ASSERT(e)		GSI_ASSERT(e)
#else
#define GSI_EXTRA_DEBUG_ASSERT(e)	((void)0)
#define GSI_DEBUG_ASSERT(e)		((void)0)
#endif

#define _GSI_BUILD_ASSERT(e)	((void)sizeof(char [!!(e) - 1]))

#define GSI_BUILD_ASSERT_CONST(name, expr) \
static inline void gsi_check_const_##name (void) \
{ \
	_GSI_BUILD_ASSERT(expr); \
}

#define GSI_BUILD_ASSERT_SIZE(struct_class, type, size) \
static inline void gsi_check_##type(void) \
{ \
	_GSI_BUILD_ASSERT(sizeof(struct_class type) == (size)); \
}

#define GSI_BUILD_ASSERT_MEMBER_SIZE(struct_class, type, member, size) \
static inline void gsi_check_##type##_##member##_size(void) \
{ \
	_GSI_BUILD_ASSERT(sizeof(((struct_class type *)(0))->member) == (size)); \
}

#define GSI_BUILD_ASSERT_MEMBER_MIN_BITS(struct_class, type, member, bits) \
static inline void gsi_check_##type##_##member##_min_bits(void) \
{ \
	_GSI_BUILD_ASSERT(sizeof(((struct_class type *)(0))->member) * 8 >= (bits)); \
}

#define GSI_BUILD_ASSERT_MEMBER_ELEM_MIN_BITS(struct_class, type, member, bits) \
static inline void gsi_check_##type##_##member##_min_bits(void) \
{ \
	_GSI_BUILD_ASSERT(sizeof(((struct_class type *)(0))->member[0]) * 8 >= (bits)); \
}

void some_function6();

#ifdef __cplusplus
}
#endif

#endif // BARYON_GSI_LIBSYS_ASSERT_H
