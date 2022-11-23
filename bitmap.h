#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#ifndef BITMAP_H
#define BITMAP_H


typedef struct
{
    HEADER *header; //not sure if pointer
    BYTE* data;
} BITMAP;

//void initializeBM(BITMAP *bm);

#endif