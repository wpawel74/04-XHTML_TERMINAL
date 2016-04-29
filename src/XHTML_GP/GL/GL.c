/**
 * |----------------------------------------------------------------------
 * | Copyright (C) Pawel Wisniewski, 2016
 * |
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * |----------------------------------------------------------------------
 */
#include "GL.h"
#include "os_compat.h"
#include "xhtml_gp.h"

/**
 * get char width in pixels
 * \param c					char
 * \param *font				pointer to font
 * \retval (int)			width in pixels
 */
static int GL_getCharWidth( char c, const GL_FONT *font ){
	return font->Width;
}

/**
 * get font height in pixels
 * \param *font				pointer to font
 * \retval (int)			height in pixels
 */
static int GL_getFontHeight( const GL_FONT *font ){
	return font->Height;
}

/**
 * get binary representation for char
 * \param c					char
 * \param *font				pointer to font
 * \retval (const char *)	binary representation
 */
static const char* GL_getCharData( char c, const GL_FONT *font ){
	return  font->table + (((unsigned char)c - 32) * font->Height );
}

GL* GL_getHandler(void){
	static GL _GL = { .style = { .font = &Font8, .style = ALIGN_LEFT | FONT_NORMAL },
					  .coord = { .X = 0, .Y = 0 },
					  .drm = NULL };
	return &_GL;
}

void GL_setStyle( GL *nGL, GL_STYLE style ){
	nGL->style.style = style;
}

const GL_STYLE GL_getStyle( const GL *nGL ){
	return nGL->style.style;
}

const COORD* GL_getCursor( const GL *nGL ){
	return &nGL->coord;
}

void GL_setCursor( GL *nGL, int X, int Y ){
	nGL->coord.X = X;
	nGL->coord.Y = Y;
}

static BOOLEAN GL_isInside( const COORD *coord ){
	return TRUE;
}

static void GL_HL_drawText( GL *nGL, GL_STYLE style, const char *text, int len ){
	const char *ptr = text;

	while ( *ptr && len-- ){
		COORD dr = { GL_getCursor(nGL)->X + GL_getCharWidth( *ptr, nGL->style.font ),
					 GL_getCursor(nGL)->Y + GL_getFontHeight( nGL->style.font ) };
		if( GL_isInside( GL_getCursor(nGL) ) && GL_isInside(&dr) ){
			drm_PutBitmap( nGL->drm,
					GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y,
					GL_getCharWidth( *ptr, nGL->style.font ),
					GL_getFontHeight( nGL->style.font ),
					(const unsigned char *)GL_getCharData( *ptr, nGL->style.font ) );

			if( (STYLE_GET_DECOR( style ) & DECOR_BLINK)  )
				drm_InvertArea( nGL->drm,
						GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y,
						GL_getCharWidth( *ptr, nGL->style.font ),
						GL_getFontHeight( nGL->style.font ) );
		}
		GL_setCursor( nGL,
					  GL_getCursor(nGL)->X + GL_getCharWidth( *ptr, nGL->style.font ),
					  GL_getCursor(nGL)->Y );
		ptr++;
	}
}

void GL_setNL( GL *nGL ){
	GL_setCursor( nGL, GL_getCursor(nGL)->X, GL_getCursor(nGL)->Y + GL_getFontHeight( nGL->style.font ) );
}

static int GL_getTextLenghtInPixel( const GL_FONT *font, const char *text, int len ){
	int width = 0;
	while( len-- ){
		width += GL_getCharWidth( *text, font );
		text++;
	}
	return width;
}

void GL_drawText( GL *nGL, const char *text, int len, struct XHTML_GP_BASE *b ){
	const char *text_ptr = text;
	const char *text_begin = text;
	const char *text_stop = text;
	int width = GL_getCursor(nGL)->X;
	int c_width = 0;
	int xlen = 0;

	do {
		do {
			c_width = GL_getCharWidth( *text_ptr, nGL->style.font );

			if( width + c_width < nGL->drm->width ){
				width += c_width;
				xlen++;

				if( *text_ptr == ' ' )
					text_stop = text_ptr;

				text_ptr++;
			} else {
				if( text_stop != text_begin )
					xlen = text_stop - text_begin;
			}
		} while ( ((width + c_width) < nGL->drm->width) );

		if(STYLE_GET_ALIGN(GL_getStyle(nGL)) == ALIGN_LEFT ){
			GL_HL_drawText( nGL, GL_getStyle(nGL), text_begin, xlen );
		} else if(STYLE_GET_ALIGN(GL_getStyle(nGL)) == ALIGN_CENTER ){
			c_width = GL_getTextLenghtInPixel( nGL->style.font, text_begin, xlen );
			GL_setCursor( nGL, (nGL->drm->width - c_width) / 2, GL_getCursor(nGL)->Y );
			GL_HL_drawText( nGL, GL_getStyle(nGL), text_begin, xlen );
		} else if(STYLE_GET_ALIGN(GL_getStyle(nGL)) == ALIGN_RIGHT ){
			c_width = GL_getTextLenghtInPixel( nGL->style.font, text_begin, xlen );
			GL_setCursor( nGL, (nGL->drm->width - c_width), GL_getCursor(nGL)->Y );
			GL_HL_drawText( nGL, GL_getStyle(nGL), text_begin, xlen );
		}

		GL_setNL(nGL);

		text_begin += xlen;
		text_stop = text_begin;
		width = 0;
		xlen = 0;

	} while( (text_begin) < (text + len) );
}
