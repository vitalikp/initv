/*
 * Copyright © 2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdlib.h>

#include "core/mount.h"
#include "mount_s.h"


static const mount_t mount_sysfs[] =
{
	{ "sysfs",		"/sys",					FS_TYPE_SYS, 	MS_NOSUID|MS_NOEXEC|MS_NODEV,	NULL		},
	{ "proc",		"/proc",				FS_TYPE_PROC,	MS_NOSUID|MS_NOEXEC|MS_NODEV,	NULL 		},
//	{ "devtmpfs",	"/dev",					FS_TYPE_DEVTMP,	MS_NOSUID|MS_STRICTATIME,		"mode=755"	},// mounted by kernel
	{ "securityfs", "/sys/kernel/security", FS_TYPE_SEC,	MS_NOSUID|MS_NOEXEC|MS_NODEV,	NULL		}
};


int mnt_init(void)
{
	mount_t *p;
	int res, i;

	i = 0;
	while (i < 3)
	{
		p = (mount_t*)&mount_sysfs[i++];

		res = mnt_mount(p);
		if (res < 0)
			return -1;
	}

	return 0;
}