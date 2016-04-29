/**
 * @author  Pawel Wisniewski
 * @email   w_pawel74@tlen.pl
 * @version v1.0
 * @ide     CooCox
 * @license GNU GPL v3
 * @brief   Platform independent
 *
\verbatim
   ----------------------------------------------------------------------
    Copyright (C) Pawel Wisniewski, 2016

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

   ----------------------------------------------------------------------
\endverbatim
 */
#ifndef OS_COMPAT_H
#define OS_COMPAT_H
#include <stdio.h>
#include "stm32fxxx_hal.h"

#define ATTR_NO_RETURN   __attribute__ ((noreturn))
#define ATTR_UNUSED   __attribute__ ((unused))
#define ATTR_USED	__attribute__((used))
#define ATTR_WARN_UNUSED_RESULT   __attribute__ ((warn_unused_result))
#define ATTR_NON_NULL_PTR_ARG(...)   __attribute__ ((nonnull (__VA_ARGS__)))
#define ATTR_NON_NULL   __attribute__ ((nonnull))
#define ATTR_NAKED   __attribute__ ((naked))
#define ATTR_NO_INLINE   __attribute__ ((noinline))
#define ATTR_ALWAYS_INLINE   __attribute__ ((always_inline))
#define ATTR_PURE   __attribute__ ((pure))
#define ATTR_CONST   __attribute__ ((const))
#define ATTR_DEPRECATED   __attribute__ ((deprecated))
#define ATTR_WEAK   __attribute__ ((weak))
#define ATTR_NO_INIT   __attribute__ ((section (".noinit")))
#define ATTR_INIT_SECTION(SectionIndex)   __attribute__ ((used, naked, section (".init" #SectionIndex )))
#define ATTR_ALIAS(Func)   __attribute__ ((alias( #Func )))
#define ATTR_PACKED   __attribute__ ((packed))
#define ATTR_ALIGNED(Bytes)   __attribute__ ((aligned(Bytes)))
#define ATTR(attrs)	__attribute__(attrs)

#define ASSERT(condition)					do { } while( 0 );
#ifndef NULL
#define NULL	0
#endif // NULL

#define _D(MSG)					printf MSG

typedef uint32_t			u32;
typedef uint8_t				u8;
typedef u8					BOOLEAN;

#define TRUE				1
#define FALSE				0

#endif /* OS_COMPAT_H */
