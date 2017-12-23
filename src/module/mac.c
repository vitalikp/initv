/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#ifdef HAVE_SELINUX
#include <selinux/selinux.h>
#endif

#include "mac.h"
#include "log.h"
#include "init.h"


static int selinux_init()
{
#ifdef HAVE_SELINUX
	int enforce = -1;

	char *scon = NULL, *tcon = NULL;
	int res;

	res = selinux_init_load_policy(&enforce);
	if (res < 0)
	{
		log_error("selinux_init_load_policy(): %m");
		return -1;
	}

	char *label = NULL;

	res = getcon(&scon);
	log_info("selinux context: '%s'", scon);

	if (!res)
	{
		res = getfilecon("/usr/local/sbin/initv", &tcon);
		log_info("selinux /usr/local/sbin/initv context: '%s'", tcon);
	}

	if (!res)
	{
		security_class_t sclass;

		sclass = string_to_security_class("process");

		res = security_compute_create_name(scon, tcon, sclass, NULL, &label);
		log_info("selinux context label: '%s'", label);
	}

	freecon(scon);
	freecon(tcon);

	if (res < 0)
		return -1;
#endif

	return 0;
}

int mac_init(void)
{
	struct timespec start;
	struct timespec end;

	clock_gettime(CLOCK_MONOTONIC, &start);

	if (selinux_init() < 0)
		return -1;

	clock_gettime(CLOCK_MONOTONIC, &end);

	uint64_t time;

	time = end.tv_sec - start.tv_sec;
	time *= 1000000UL;
	time += end.tv_nsec - start.tv_nsec;

	log_info("Successfully loaded SELinux policy in %lu.", time);

	return 0;
}

const init_module module_mac =
{
	.name = "MAC",
	.init = mac_init
};