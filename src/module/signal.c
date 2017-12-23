/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include "log.h"
#include "init.h"


static void handler_default(int signo)
{
	log_info("signal '%s' received", strsignal(signo));
}


static __sighandler_t signals[_NSIG] =
{
	[SIGTERM] = handler_default,
	[SIGINT] = handler_default
};

static int signal_init(void)
{
	__sighandler_t handler;
	int signo = 0;

	while (signo < _NSIG)
	{
		handler = signals[signo++];

		if (!handler)
			continue;

		struct sigaction sa =
		{
			.sa_handler = handler,
			.sa_flags = SA_RESTART,
		};

		log_info("init signal '%s' handler to default", strsignal(signo));

		if (sigaction(signo, &sa, NULL) < 0)
			return -1;
	}

	return INIT_DONE;
}

const init_module module_signal =
{
	.name = "signal",
	.init = signal_init
};