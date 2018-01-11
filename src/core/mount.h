/*
 * Copyright © 2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _MOUNT_H_
#define _MOUNT_H_

#include <sys/mount.h>


typedef struct mount_t mount_t;


int mnt_init(void);

int mnt_mount(mount_t *mnt);

#endif /* _MOUNT_H_ */