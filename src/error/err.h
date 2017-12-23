/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _ERR_H_
#define _ERR_H_


typedef enum ErrorCode ErrorCode;

enum ErrorCode
{
	ERR_OK,
	ERR_NODATA,
	ERR_FORMAT,
	ERR_MAX
};

extern __thread int err;
#define __err_set(val) err = (val)
char* err_str();

#endif /* _ERROR_H_ */