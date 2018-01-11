/*
 * Copyright © 2018 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include "mount_s.h"


#define FSTYPE(type, name) [FS_TYPE_ ## type] = #name,
const char* fstypes[FS_TYPE_MAX] =
{
#include "fstype.h"
};
#undef FSTYPE


#ifdef TESTS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


static void test_fstype(const FsType fstype, const char *type)
{
	int res;

	res = strcmp(type, fstypes[fstype]);
	assert(!res);

	printf("test fs type 0x%x: '%s'\n", fstype, type);
}

int main()
{
	test_fstype(FS_TYPE_SYS, "sysfs");
	test_fstype(FS_TYPE_PROC, "proc");
	test_fstype(FS_TYPE_DEVTMP, "devtmpfs");
	test_fstype(FS_TYPE_SEC, "securityfs");

	return EXIT_SUCCESS;
}

#endif // TESTS