#include "headerBitmap.h"
#ifndef BITMAP_H
#define BITMAP_H

typedef struct
{
    HEADER fileheader;
    DATAPIX data;
} BITMAP;

typedef struct
{

} DATAPIX;

#endif