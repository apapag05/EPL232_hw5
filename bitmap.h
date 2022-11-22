#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#ifndef BITMAP_H
#define BITMAP_H


typedef struct
{
    HEADER fileheader;
    BYTE* data;
} BITMAP;

#endif