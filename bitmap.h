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

typedef struct
{
    int size;
    unsigned char bfType1;
    unsigned char bfType2;
    unsigned int bfSize;
    unsigned int bfReserved1;
    unsigned int bfReserved2;
    unsigned int bfOffBits;
    unsigned int biSize;
    unsigned int biWidth;
    unsigned int biHeight;
    unsigned int biPlanes;
    unsigned int biBitCount;
    unsigned int biCompression;
    unsigned int biSizeimage;
    unsigned int biXPelsPerMeter;
    unsigned int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;

} HEADER;



#endif