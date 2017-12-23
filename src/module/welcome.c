/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "log.h"
#include "init.h"
#include "conf.h"
#include "os.h"


// OS info file
static const char* osfn = "/etc/os-release";


static int welcome_init(void)
{
	os_t os = {};

	if (conf_load(osfn, os_conf, &os) < 0)
	{
		log_error("read %s file failed", osfn);
		return INIT_DONE;
	}

	printf("\n%s \x1B[%sm%s %s\x1B[0m!\n", _("Welcome to"), os.ansi_color, os.name, os.version);

	return INIT_DONE;
}

const init_module module_welcome =
{
	.name = "welcome",
	.init = welcome_init
};