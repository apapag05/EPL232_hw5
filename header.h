#ifndef HEADER_H
#define HEADER_H

typedef unsigned char BYTE; //1 byte
typedef unsigned short int WORD; //2 bytes
typedef unsigned int DWORD; //4 bytes

typedef struct
{
    //BITMAPFILEHEADER
    BYTE bfType1;
    BYTE bfType2;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;

    //BITMAPINFOHEADER
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeimage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;

} __attribute__ ((__packed__)) HEADER;

#endif