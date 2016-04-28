#include "os_compat.h"
#include "drm.h"
#include "ug2864.h"

void drm_PutBitmap(DRM *drm, int x, int y, int width, int height, const unsigned char *bmp){
	UG2864_drawBitmap(x, y, bmp, width, height, WHITE);
}

void drm_InvertArea(DRM *drm, int x, int y, int width, int high){
}
