/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdio.h>

#ifdef ENABLE_NLS
#include <locale.h>
#endif

#include "log.h"
#include "init.h"
#include "loc.h"


// locale config file
static const char* locfn = "/etc/locale.conf";


int locale_init(void)
{
	loc_t loc = { "C" };

	if (conf_load(locfn, loc_conf, &loc) < 0)
	{
		log_error("read %s file failed: %m!", locfn);
		return INIT_DONE;
	}

	conf_loadenv(loc_conf, &loc);

#ifdef ENABLE_NLS
	/* setup locale */
	setlocale(LC_ALL, loc.lang);

	/* support for gettext */
	bindtextdomain(PACKAGE_NAME, LOCALEDIR);
	textdomain(PACKAGE_NAME);
#endif

	return INIT_DONE;
}

const init_module module_locale =
{
	.name = "locale",
	.init = locale_init
};
