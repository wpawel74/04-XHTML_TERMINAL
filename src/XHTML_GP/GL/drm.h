/**
 * @author  Pawel Wisniewski
 * @email   w_pawel74@tlen.pl
 * @version v1.0
 * @ide     CooCox
 * @license GNU GPL v3
 * @brief   Simple Drawing Library for XHTML Gigaset Profile
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
#ifndef DRM_H
#define DRM_H
#include <sys/types.h>
#include "os_compat.h"

/**
 * handler to surface
 */
typedef struct DRM {
    u32			width;				/**< szerokosc wirtualnego ekranu*/
    u32			high;				/**< wysokosc wirtualnego ekranu*/
    u32			bits;				/**< ilosc bitow na kolor*/
    u8			*data;				/**< dane ekranu*/
} DRM;

void drm_PutBitmap(DRM *drm, int x, int y, int width, int height, const unsigned char *bmp);

void drm_InvertArea(DRM *drm, int x, int y, int width, int high);

#endif /* DRM_H */
