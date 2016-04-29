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
#include "os_compat.h"
#include "drm.h"
#include "ug2864.h"

void drm_PutBitmap(DRM *drm, int x, int y, int width, int height, const unsigned char *bmp){
	UG2864_drawBitmap(x, y, bmp, width, height, WHITE);
}

void drm_InvertArea(DRM *drm, int x, int y, int width, int high){
}
