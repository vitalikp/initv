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

#include "conf.h"
#include "log.h"
#include "os.h"


static int parse_line(char* in, char** name, char** value)
{
	enum State
	{
		ST_NONE,
		ST_SPACE,
		ST_QUOTE
	};

	int i = 0;

	enum State state = ST_NONE;

	char c;
	char* p = NULL;
	while (i < LINE_MAX)
	{
		c = in[i++];
		if (c == '\n')
		{
			in[i-1] = '\0';
			break;
		}

		if (isspace(c))
		{
			if (state == ST_SPACE)
				in[i-1] = c;

			if (state == ST_NONE)
				state = ST_SPACE;
			continue;
		}

		if (c == '=')
		{
			in[i-1] = '\0';
			p = in + i;
			continue;
		}

		if (isquote(c))
		{
			if (!p)
				return -1;// quote in name

			if (state == ST_QUOTE)
			{
				in[i-1] = '\0';
				state = ST_NONE;
			}
			else
			{
				p++;
				state = ST_QUOTE;
			}
			continue;
		}

		if (state == ST_QUOTE)
			continue;

		if (!p && !isalnum(c) && c != '_')
		{
			log_error("syntax err: '%s' no in [0-9A-Za-z]", c);
//			state = ST_ERR;
//			continue;
			return -1;
		}
	}

	*name = in;
	*value = p;

	return i;
}

static option_t* find_option(const option_t* options, const char* name)
{
	option_t* curr = (option_t*)options;

	while (curr->name)
	{
		if (!strcmp(curr->name, name))
			return curr;

		curr++;
	}

	return NULL;
}

static void set_option(void** conf, option_t* opt, char* value)
{
	if (opt->conv)
		value = opt->conv(value);
	value = strdup(value);
	conf[opt->off/8] = value;
}

int conf_read(int fd, const option_t* options, void* conf)
{
	char buf[LINE_MAX];

	size_t size = 0;

	int sz;

	option_t* opt;

	char* name;
	char* value;

	int res;
	int off;
	while ((sz = read(fd, buf, LINE_MAX)) > 0)
	{
		off = 0;
		while (off < sz)
		{
			if (!isalpha(buf[0]))
				break;

			name = NULL;
			value = NULL;
			res = parse_line(buf + off, &name, &value);
			if (res < 0)
				return -1;
			off += res;

			opt = find_option(options, name);
			if (opt != NULL)
			{
				set_option(conf, opt, value);
//				printf("'%s': '%s'\n", name, value);
			}
		}

		size += sz;
	}

	return size;
}

int conf_load(const char* fn, const option_t* options, void* conf)
{
	int fd;

	fd = open(fn, O_RDONLY);
	if (fd < 0)
		return -1;

	int res;

	res = conf_read(fd, options, conf);

	close(fd);

	return res;
}

void conf_loadenv(const option_t* options, void* conf)
{
	option_t* curr = (option_t*)options;

	char* value;
	while (curr->name)
	{
		value = getenv(curr->name);
		if (value)
			set_option(conf, curr, value);

		curr++;
	}
}