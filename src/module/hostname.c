/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>

#include "init.h"
#include "macro.h"
#include "err.h"
#include "log.h"


// hostname config file
static const char* hostfn = "/etc/hostname";


static int hn_conf_read(char *name, const size_t size)
{
	int fd;

	fd = open(hostfn, O_RDONLY);
	if (fd < 0)
	{
		log_warn(_("error opening file '%s'"), hostfn);
		return -1;
	}

	int sz;

	int off = 0;
	int len = 0;
	while ((sz = read(fd, name + off, size - off)) > 0)
	{
		// skip whitespace at the beginning
		while (off < size && isspace(name[off])) off++;

		// skip whitespace at the end
		while (sz > 0 && isspace(name[sz-1])) sz--;

		sz -= off;

		// skip if no whitespace
		if (off == len)
		{
			len += sz;
			continue;
		}

		while (sz-- > 0)
			name[len++] = name[off++];
	}

	close(fd);

	name[len] = '\0';

	return len;
}

static int hn_check(char *name, const size_t len)
{
	if (!len)
	{
		__err_set(ERR_NODATA);
		return 0;
	}

	if (!isalpha(name[0]) || (len > 1 && !isalnum(name[len-1])))
	{
		__err_set(ERR_FORMAT);
		return 0;
	}

	int i = 0;
	while (++i < len)
	{
		if (isalnum(name[i]) || name[i] == '-')
			continue;

		if (name[i] == '.' && name[i-1] != '.')
			continue;

		__err_set(ERR_FORMAT);
		return 0;
	}

	return 1;
}

static int hs_set(const char* name, size_t len)
{
	int fd;

	fd = open("/proc/sys/kernel/hostname", O_RDWR);
	if (fd < 0)
		return -1;

	int res;

	res = write(fd, name, len);

	close(fd);

	if (res < 0)
		return -1;

	return 0;
}

int hn_init(void)
{
	char name[HOST_NAME_MAX] = {};

	int len;

	len = hn_conf_read(name, HOST_NAME_MAX);
	if (len < 0)
		return -INIT_SKIP;

	if (!hn_check(name, len))
	{
		log_error(_("error checking hostname '%s'"), name);
		return -INIT_SKIP;
	}

	if (hs_set(name, len) < 0)
	{
		log_error(_("error setting hostname '%s'"), name);
		return -INIT_SKIP;
	}

	return INIT_DONE;
}

const init_module module_hostname =
{
	.name = "hostname",
	.init = hn_init
};
