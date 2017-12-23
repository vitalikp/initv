/*
 * Copyright © 2016 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _LOC_H_
#define _LOC_H_

#include "conf.h"


typedef struct loc_t loc_t;

struct loc_t
{
	/**
	 * format: <lc>[_<cc>[.<codeset>]][@modifier]
	 * 	lc - language code (iso 639-1 - alpha-2 code)
	 * 	cc - country code (iso 3166 - alpha-2 code)
	 */
	const char* lang;
};

static const option_t loc_conf[] =
{
	{ "LANG",	offsetof(loc_t, lang) },
	NULL
};

#endif /* _LOC_H_ */