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
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <sys/wait.h>

#include "err.h"
#include "init.h"
#include "log.h"
#include "conf.h"


static const init_module* modules[MODULE_MAX] =
{
	[MODULE_LOCALE] = &module_locale,
	[MODULE_VCONSOLE] = &module_vconsole,
	[MODULE_WELCOME] = &module_welcome,
	[MODULE_SIGNAL] = &module_signal,
	[MODULE_MOUNT] = &module_mount,
	[MODULE_MAC] = &module_mac,
	[MODULE_HOSTNAME] = &module_hostname,
};

typedef struct status_t status_t;

struct status_t
{
	const char* color;
	const char* descr;
};

static const status_t statuses[INIT_MAX] =
{
	[INIT_DONE] = { "\x1b[32m",			N_("Done")	},
	[INIT_SKIP] = { "\x1b[38;5;11m",	N_("Skip")	},
	[INIT_FAIL] = { "\x1b[38;5;9m", 	N_("Fail")	}
};


static void log_status(InitStatus status, const char* info)
{
	const status_t* st = &statuses[status];

	printf("[ %s%10s\x1B[0m ] %s\n", st->color, _(st->descr), info);
}

int main(int argc, char* argv[])
{
	int i = 0;

	init_module* module;

	char info[LINE_MAX];

	int res;
	while (i < MODULE_MAX)
	{
		module = (init_module*)modules[i++];
		if (!module)
			continue;

		if (!module->init)
			continue;

		res = module->init();
		snprintf(info, LINE_MAX, _("Init %s module"), module->name);
		if (res < 0)
		{
			if (res == -2)
			{
				log_status(INIT_FAIL, info);
				return EXIT_FAILURE;
			}

			log_status(INIT_SKIP, info);
			continue;
		}
		log_status(INIT_DONE, info);
	}

	log_info("init done");

	pid_t pid;

	pid = fork();
	if (!pid)
		execl("/bin/sh", "/bin/sh", NULL);

	int status;
	waitpid(pid, &status, 0);
	log_info("exiting... %d", status);

	return EXIT_SUCCESS;
}