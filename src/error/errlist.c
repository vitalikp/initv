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


const char* const errlist[ERR_MAX] =
{
	[ERR_NODATA] = N_("data not present"),
	[ERR_FORMAT] = N_("wrong format")
};