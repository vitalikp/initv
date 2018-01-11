/*
 * Copyright © 2017-2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <errno.h>

#include "log.h"
#include "init.h"
#include "core/mount.h"


typedef struct mount_t mount_t;


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
		res = mount(p->src, p->dir, p->fstype, p->flags, p->opts);
		if (res < 0)
		{
			if (errno == EBUSY)
			{
				log_warn("Skip %s, already mounted", p->dir);
				continue;
			}

			log_error("Failed to mount %s at %s: %m", p->fstype, p->dir);
			return -1;
		}
	}

	// TODO mount sysfs and other

	return 0;
}

const init_module module_mount =
{
	.name = "mount",
	.init = mount_init
};