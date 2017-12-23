/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _INIT_H_
#define _INIT_H_


typedef enum InitStatus
{
	INIT_DONE,
	INIT_SKIP,
	INIT_FAIL,
	INIT_MAX
} InitStatus;

typedef enum InitModule
{
	MODULE_LOCALE,
	MODULE_VCONSOLE,
	MODULE_WELCOME,
	MODULE_SIGNAL,
	MODULE_MOUNT,
	MODULE_MAC,
	MODULE_HOSTNAME,
	MODULE_MAX
} InitModule;

typedef int (*init_func)(void);

typedef struct init_module
{
	const char* name;
	init_func init;
} init_module;
extern const init_module module_vconsole;
extern const init_module module_locale;
extern const init_module module_welcome;
extern const init_module module_signal;
extern const init_module module_mount;
extern const init_module module_hostname;
extern const init_module module_mac;

#endif /* _INIT_H_ */
