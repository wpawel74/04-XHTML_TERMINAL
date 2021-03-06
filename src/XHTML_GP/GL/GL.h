/**
 * @author  Pawel Wisniewski
 * @email   w_pawel74@tlen.pl
 * @version v1.0
 * @ide     CooCox
 * @license GNU GPL v3
 * @brief   Graphics Library for XHTML Gigaset Profile
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
#ifndef GL_H
#define GL_H
#include "os_compat.h"
#include "drm.h"
#include "fonts.h"

typedef sFONT GL_FONT;

typedef enum STYLE {
	ALIGN_LEFT			= 0x0000,
	ALIGN_CENTER		= 0x0001,
	ALIGN_RIGHT			= 0x0002,

	FLOAT_LEFT			= 0x0004,
	FLOAT_RIGHT			= 0x0010,

	MARGIN_LEFT			= 0x0000,
	MARGIN_CENTER		= 0x0100,
	MARGIN_RIGHT		= 0x0200,

	FONT_NORMAL			= 0x0000,
	FONT_BOLD			= 0x1000,

	DECOR_NONE			= 0x4000,
	DECOR_BLINK			= 0x8000
} GL_STYLE;

typedef struct GL_TEXT_STYLE {
	GL_FONT			*font;
	GL_STYLE		style;
} GL_TEXT_STYLE;

typedef struct COORD {
	int				X;
	int				Y;
} COORD;

typedef struct _GL {
	GL_TEXT_STYLE	style;
	COORD			coord;			// cursor coordinate
	DRM				*drm;
} GL;

#define STYLE_GET_ALIGN( s )				(s & 0x0003)
#define STYLE_GET_FLOAT( s )				(s & 0x001c)
#define STYLE_GET_MARGIN( s )				(s & 0x0f00)
#define STYLE_GET_FONT( s )					(s & 0x1000)
#define STYLE_GET_DECOR( s )				(s & 0xc000)

#define __GL_ATTR__

/**
 * get handler to Graphics Library
 */
__GL_ATTR__ GL* GL_getHandler(void);

/**
 * set new style for GL
 */
__GL_ATTR__ void GL_setStyle( GL *nGL, GL_STYLE style );


/**
 * get current used style
 */
__GL_ATTR__ const GL_STYLE GL_getStyle( const GL *nGL );

/**
 * get cursor position
 */
__GL_ATTR__ const COORD* GL_getCursor( const GL *nGL );

/**
 * set cursor
 */
__GL_ATTR__ void GL_setCursor( GL *nGL, int X, int Y );

struct XHTML_GP_BASE;
__GL_ATTR__ void GL_drawText( GL *nGL, const char *text, int len, struct XHTML_GP_BASE *base );

__GL_ATTR__ void GL_setNL( GL *nGL);

__GL_ATTR__ void GL_clear( GL *nGL );
__GL_ATTR__ void GL_flush( GL *nGL );

#endif /* GL_H */
