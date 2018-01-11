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


#define FSTYPE(type, name) [FS_TYPE_ ## type] = #name,
static const char* fstypes[FS_TYPE_MAX] =
{
#include "fstype.h"
};
#undef FSTYPE


int mnt_mount(mount_t *mnt)
{
	const char *type;
	int res;

	type = fstypes[mnt->fstype];
	if (!type)
		return -1;

	res = mount(mnt->src, mnt->dir, type, mnt->flags, mnt->opts);
	if (res < 0)
	{
		if (errno == EBUSY)
		{
			log_warn("Skip %s, already mounted", mnt->dir);
			return 0;
		}

		log_error("Failed to mount %s at %s: %m", type, mnt->dir);
		return -1;
	}

	return res;
}