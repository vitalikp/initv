/*
 * Copyright © 2016 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _CONF_H_
#define _CONF_H_

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>

#include "macro.h"


typedef void* (*conv_func)(void* data);

typedef struct option_t option_t;

struct option_t
{
	const char* name;
	const int off;
	conv_func conv;
};


int conf_read(int fd, const option_t* options, void* conf);
int conf_load(const char* fn, const option_t* options, void* conf);
void conf_loadenv(const option_t* options, void* conf);

#endif /* _CONF_H_ */