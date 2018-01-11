/*
 * Copyright © 2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _MOUNT_S_H_
#define _MOUNT_S_H_


#define FSTYPE(type, name) FS_TYPE_ ## type,
typedef enum
{
#include "fstype.h"
	FS_TYPE_MAX
} FsType;
#undef FSTYPE


struct mount_t
{
	/**
	 * source file system
	 */
	const char* src;

	/**
	 * target directory
	 */
	const char* dir;

	/**
	 * file system type
	 */
	const FsType fstype;

	/**
	 * mount flags
	 */
	unsigned long flags;

	/**
	 * mount options
	 */
	const char* opts;
};

#endif /* _MOUNT_H_ */