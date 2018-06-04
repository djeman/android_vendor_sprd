
#ifndef _GRALLOC_PUBLIC_
#define _GRALLOC_PUBLIC_
#define PARAM_IGNORE(x) (void)x

/*gpu version*/
#define	rogue   0x01
#define	midgard 0x02
#define	soft    0x04
#define	utgard  0x08

#define SPRD_GPU_PLATFORM_ROGUE (TARGET_GPU_PLATFORM & rogue)
#define SPRD_GPU_PLATFORM_MIDGARD (TARGET_GPU_PLATFORM & midgard)
#define SPRD_GPU_PLATFORM_SOFT (TARGET_GPU_PLATFORM & soft)
#define SPRD_GPU_PLATFORM_UTGARD (TARGET_GPU_PLATFORM & utgard)

#include <cutils/atomic.h>

#if SPRD_GPU_PLATFORM_MIDGARD
#include "midgard/gralloc_priv.h"
#include "midgard/format_chooser.h"
#else
#include "utgard/gralloc_priv.h"
#endif

static uint64_t getUniqueId() {
	static volatile int32_t nextId = 0;
	uint64_t id = static_cast<uint64_t>(getpid()) << 32;
	id |= static_cast<uint32_t>(android_atomic_inc(&nextId));
	return id;
}

static inline int ADP_FORMAT(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->format;
}

static inline int ADP_WIDTH(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->width;
}

static inline int ADP_HEIGHT(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->height;
}

static inline int ADP_STRIDE(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->stride;
}

static inline int ADP_BUFFD(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->share_fd;
}

static inline int ADP_YINFO(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->yuv_info;
}

static inline int ADP_USAGE(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->usage;
}

static inline int ADP_FLAGS(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->flags;
}

/*this interface only for sf process */
static inline void* ADP_BASE(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->base;
}

static inline int ADP_BUFSIZE(buffer_handle_t h)
{
	if (h == NULL)
		return 0;

	return ((private_handle_t*)h)->size;
}

static inline int ADP_FAKESETBUFATTR_CAMERAONLY(buffer_handle_t h, int size, int width, int height)
{
	if ((h == NULL) || (size <= 0) || (width <= 0) || (height <= 0))
		return 0;

	((private_handle_t*)h)->size = size;
	((private_handle_t*)h)->width = width;
	((private_handle_t*)h)->height = height;
	return ((private_handle_t*)h)->size;
}

#define ADP_PHYADDR(h)	((private_handle_t*)h)->phyaddr
#define ADP_BUFINDEX(h)	((private_handle_t*)h)->buf_idx

#endif

