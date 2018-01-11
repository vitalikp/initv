/*
 * Copyright © 2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <errno.h>

#include "core/mount.h"
#include "mount_s.h"
#include "log.h"


int mnt_mount(mount_t *mnt)
{
	int res;

	res = mount(mnt->src, mnt->dir, mnt->fstype, mnt->flags, mnt->opts);
	if (res < 0)
	{
		if (errno == EBUSY)
		{
			log_warn("Skip %s, already mounted", mnt->dir);
			return 0;
		}

		log_error("Failed to mount %s at %s: %m", mnt->fstype, mnt->dir);
		return -1;
	}

	return res;
}