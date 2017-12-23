/*
 * Copyright © 2016 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _OS_H_
#define _OS_H_

#include "conf.h"


typedef struct os_t os_t;

struct os_t
{
	const char* name;
	const char* version;
	const char* ansi_color;
};

static const option_t os_conf[] =
{
	{ "NAME", offsetof(os_t, name) },
	{ "VERSION", offsetof(os_t, version) },
	{ "ANSI_COLOR", offsetof(os_t, ansi_color) },
	NULL
};

#endif /* _OS_H_ */