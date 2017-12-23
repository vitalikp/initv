/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <unistd.h>
#include <sys/wait.h>

#include "log.h"
#include "init.h"
#include "vcon.h"


// vconsole config file
static const char* vconfn = "/etc/vconsole.conf";


static void load_keymap(const char* keymap)
{
	if (!keymap)
		return;

	pid_t pid;

	pid = fork();
	if (!pid)
		execl("/bin/loadkeys", "/bin/loadkeys", keymap, NULL);

	int status;
	waitpid(pid, &status, 0);
}

static void load_sysfont(const char* font)
{
	if (!font)
		return;

	pid_t pid;

	pid = fork();
	if (!pid)
		execl("/bin/setfont", "/bin/setfont", font, NULL);

	int status;
	waitpid(pid, &status, 0);
}

int vconsole_init(void)
{
	vcon_t vcon = {};

	if (conf_load(vconfn, vcon_conf, &vcon) < 0)
	{
		log_error("read %s file failed", vconfn);
		return INIT_DONE;
	}

	conf_loadenv(vcon_conf, &vcon);

	int fd;

	fd = open("/dev/console", O_RDWR);
	if (fd < 0)
	{
		log_error("fail open console(%d)", fd);
		return -INIT_SKIP;
	}

	load_sysfont(vcon.font);
	load_keymap(vcon.keymap);

	close(fd);

	return INIT_DONE;
}

const init_module module_vconsole =
{
	.name = "vconsole",
	.init = vconsole_init
};