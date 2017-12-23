/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

#include "log.h"
#include "err.h"


static int outfd = STDOUT_FILENO;
static int errfd = STDERR_FILENO;


void log_open()
{

}

void log_close()
{

}

int dump_err(char* buf, int off, int len)
{
	if (off >= len)
		return off;

	char* err = err_str();
	if (!err || err[0] == '\0')
		return off;

	if (off + 2 > len)
		return off;

	buf[off++] = ':';
	buf[off++] = ' ';

	int i = 0;
	while (err[i])
	{
		if (off == len)
			return off;

		buf[off++] = err[i++];
	}

	return off;
}

void log_info(const char *fmt, ...)
{
	char buf[LINE_MAX];

	int sz;
	va_list args;

	va_start(args, fmt);
	sz = vsnprintf(buf, LINE_MAX, fmt, args);
	va_end(args);
	if (sz < 0)
		return;

	buf[sz++] = '\n';

	write(outfd, buf, sz);
}

void log_warn(const char *fmt, ...)
{
	char buf[LINE_MAX];

	int sz;
	va_list args;

	va_start(args, fmt);
	sz = vsnprintf(buf, LINE_MAX, fmt, args);
	va_end(args);
	if (sz < 0)
		return;

	sz = dump_err(buf, sz, LINE_MAX);
	if (sz < 0)
		return;

	buf[sz++] = '\n';

	write(outfd, buf, sz);
}

void log_error(const char *fmt, ...)
{
	char buf[LINE_MAX];

	int sz;
	va_list args;

	va_start(args, fmt);
	sz = vsnprintf(buf, LINE_MAX, fmt, args);
	va_end(args);
	if (sz < 0)
		return;

	sz = dump_err(buf, sz, LINE_MAX);
	if (sz < 0)
		return;

	buf[sz++] = '\n';

	write(errfd, buf, sz);
}