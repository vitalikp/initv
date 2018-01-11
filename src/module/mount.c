/*
 * Copyright © 2017-2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdlib.h>

#include "init.h"
#include "core/mount.h"
#include "core/mount/mount_s.h"


static const mount_t mount_sysfs[] =
{
	{ "sysfs",		"/sys",					"sysfs", 		MS_NOSUID|MS_NOEXEC|MS_NODEV,	NULL		},
	{ "proc",		"/proc",				"proc",			MS_NOSUID|MS_NOEXEC|MS_NODEV,	NULL 		},
//	{ "devtmpfs",	"/dev",					"devtmpfs",		MS_NOSUID|MS_STRICTATIME,		"mode=755"	},// mounted by kernel
	{ "securityfs", "/sys/kernel/security", "securityfs",	MS_NOSUID|MS_NOEXEC|MS_NODEV,	NULL		}
};


int mount_init(void)
{
	mount_t *p;
	int res;

	// TODO parse /etc/fstab

	int i = 0;
	while (i < 3)
	{
		p = (mount_t*)&mount_sysfs[i++];

		res = mnt_mount(p);
		if (res < 0)
			return -1;
	}

	// TODO mount sysfs and other

	return 0;
}

const init_module module_mount =
{
	.name = "mount",
	.init = mount_init
};