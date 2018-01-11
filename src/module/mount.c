/*
 * Copyright © 2017-2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include "init.h"
#include "core/mount.h"


int mount_init(void)
{
	// TODO parse /etc/fstab

	if (mnt_init() < 0)
		return -1;

	// TODO mount sysfs and other

	return 0;
}

const init_module module_mount =
{
	.name = "mount",
	.init = mount_init
};