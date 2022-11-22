#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include "bitmap.h"

void readHeader(FILE *fp) {
    HEADER *header;
    header=(HEADER*)malloc(sizeof(HEADER));
    //char arr[1];
    printf("\nBITMAP_FILE_HEADER\n==================\n");
    fread(&(header->bfType1),1,1,fp);
    fread(&(header->bfType2),1,1,fp);
    fread(&(header->bfSize), 4, 1, fp);
    fread(&(header->bfReserved1), 2,1,fp);
    fread(&(header->bfReserved2), 2,1,fp);
    fread(&(header->bfOffBits), 4, 1, fp);
    fread(&(header->biSize), 4, 1, fp);
    fread(&(header->biWidth), 4, 1, fp);
    fread(&(header->biHeight), 4, 1, fp);
    fread(&(header->biPlanes), 2, 1, fp);
    fread(&(header->biBitCount), 2, 1, fp);
    fread(&(header->biCompression), 4, 1, fp);
    fread(&(header->biSizeimage), 4, 1, fp);
    fread(&(header->biXPelsPerMeter), 4, 1, fp);
    fread(&(header->biYPelsPerMeter), 4, 1, fp);
    fread(&(header->biClrUsed), 4, 1, fp);
    fread(&(header->biClrImportant), 4, 1, fp);
   
    printf("bfType: %c%c\n", header->bfType1, header->bfType2);
    printf("bfSize: %d\n", header->bfSize);
    printf("bfResereved1: %hu\n", header->bfReserved1);
    printf("bfResereved2: %hu\n", header->bfReserved2);
    printf("bfOffBits: %d\n", header->bfOffBits);
    printf("\nBITMAP_INFO_HEADER\n==================\n");
    printf("biSize: %d\n", header->biSize);
    printf("biWidth: %d\n", header->biWidth);
    printf("biHeight: %d\n", header->biHeight);
    printf("biPlanes: %hu\n", header->biPlanes);
    printf("biBitCount: %hu\n", header->biBitCount);
    printf("biCompression %d\n", header->biCompression);
    printf("biSizeImage: %d\n", header->biSizeimage);
    printf("biXPelsPerMeter: %d\n", header->biXPelsPerMeter);
    printf("biYPelsPerMeter: %d\n", header->biYPelsPerMeter);
    printf("biClrUsed: %d\n", header->biClrUsed);
    printf("biClrImportant: %d\n", header->biClrImportant);

}

int main(int argc, char *argv[]) {
    FILE *fp=fopen(argv[1], "rb");
    readHeader(fp);
}
