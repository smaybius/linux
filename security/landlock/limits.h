/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Landlock LSM - Limits for different components
 *
 * Copyright © 2016-2020 Mickaël Salaün <mic@digikod.net>
 * Copyright © 2018-2020 ANSSI
 */

#ifndef _SECURITY_LANDLOCK_LIMITS_H
#define _SECURITY_LANDLOCK_LIMITS_H

#include <linux/bitops.h>
#include <linux/limits.h>
#include <uapi/linux/landlock.h>

/* clang-format off */

#define LANDLOCK_MAX_NUM_LAYERS		16
#define LANDLOCK_MAX_NUM_RULES		U32_MAX

/*
 * For file system access rights, Landlock distinguishes between the publicly
 * visible access rights (1 to LANDLOCK_LAST_PUBLIC_ACCESS_FS) and the private
 * ones which are not exposed to userspace (LANDLOCK_LAST_PUBLIC_ACCESS_FS + 1
 * to LANDLOCK_LAST_ACCESS_FS).  The private access rights are defined in fs.c.
 */
#define LANDLOCK_LAST_PUBLIC_ACCESS_FS	LANDLOCK_ACCESS_FS_IOCTL
#define LANDLOCK_MASK_PUBLIC_ACCESS_FS	((LANDLOCK_LAST_PUBLIC_ACCESS_FS << 1) - 1)

#define LANDLOCK_LAST_ACCESS_FS		(LANDLOCK_LAST_PUBLIC_ACCESS_FS << 2)
#define LANDLOCK_MASK_ACCESS_FS		((LANDLOCK_LAST_ACCESS_FS << 1) - 1)
#define LANDLOCK_NUM_ACCESS_FS		__const_hweight64(LANDLOCK_MASK_ACCESS_FS)
#define LANDLOCK_SHIFT_ACCESS_FS	0

#define LANDLOCK_LAST_ACCESS_NET	LANDLOCK_ACCESS_NET_CONNECT_TCP
#define LANDLOCK_MASK_ACCESS_NET	((LANDLOCK_LAST_ACCESS_NET << 1) - 1)
#define LANDLOCK_NUM_ACCESS_NET		__const_hweight64(LANDLOCK_MASK_ACCESS_NET)
#define LANDLOCK_SHIFT_ACCESS_NET	LANDLOCK_NUM_ACCESS_FS

/* clang-format on */

#endif /* _SECURITY_LANDLOCK_LIMITS_H */
