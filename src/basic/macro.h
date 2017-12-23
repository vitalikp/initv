/*
 * Copyright © 2017 - Vitaliy Perevertun
 *
 * This file is part of initv
 *
 * This file is licensed under the MIT license.
 * See the file LICENSE.
 */

#ifndef _MACRO_H_
#define _MACRO_H_

#define _cleanup_(x) __attribute__((cleanup(x)))

#define isspace(c) ((c >= '\t' && c <= '\r') || c == ' ')
#define isalpha(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
#define isdigit(c) (c >= '0' && c <= '9')
#define isalnum(c) (isalpha(c) || isdigit(c))
#define isquote(c) c == '\'' || c =='\"'

#endif /* _MACRO_H_ */