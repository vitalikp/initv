/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <string.h>
#include <errno.h>

#include "err.h"



__thread int err;
extern char * errlist[];

char* err_str()
{
	if (err > ERR_OK && err < ERR_MAX)
		return _(errlist[err]);

	if (!errno)
		return NULL;

	return strerror(errno);
}
