/*
 * Copyright © 2016 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _VCON_H_
#define _VCON_H_

#include "conf.h"


typedef struct vcon_t vcon_t;

struct vcon_t
{
	/**
	 * keymap name
	 */
	const char* keymap;

	/**
	 * font name
	 */
	const char* font;
};

static const option_t vcon_conf[] =
{
	{ "KEYMAP",	offsetof(vcon_t, keymap) },
	{ "FONT",	offsetof(vcon_t, font) },
	NULL
};

#endif /* _VCON_H_ */