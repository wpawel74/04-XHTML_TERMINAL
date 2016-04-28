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
