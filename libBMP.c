#include "list.h"
#include "header.h"
#include "bitmap.h"

static void readHeader(FILE *fp, HEADER *header)
{
    // HEADER *header;
    // header=(HEADER*)malloc(sizeof(HEADER));
    // char arr[1];
    fread(&(header->bfType1), 1, 1, fp);
    fread(&(header->bfType2), 1, 1, fp);
    fread(&(header->bfSize), 4, 1, fp);
    fread(&(header->bfReserved1), 2, 1, fp);
    fread(&(header->bfReserved2), 2, 1, fp);
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
}

static void printHeader(HEADER *header)
{
    printf("\nBITMAP_FILE_HEADER\n==================\n");
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

static void readData(char* filename, BITMAP *bm, int size)
{
    FILE *fp=fopen(filename, "rb");
    fseek(fp, 54, SEEK_SET);
    int padding = ((bm->header->biWidth) * 3) % 4;
    printf("\npadding %d\n", padding);
    int i=0;
    int j=0;
    //int index=0;
    for (i=0;i<bm->header->biHeight;i++) {
        for (j=0;j<bm->header->biWidth*3;j++) {
            fread(&(bm->data[i]), 1, 1, fp); //red
            printf("i: %d j: %d data[i] %02X\n", i, j, bm->data[i]);
        }
        fseek(fp, padding*3, SEEK_CUR);
    }
    fclose(fp);
}

void list(char *filename, BITMAP *bm)
{
    FILE *fp = fopen(filename, "rb");
    readHeader(fp, bm->header);
    printHeader(bm->header);
    fclose(fp);
}

int main(int argc, char *argv[])
{
    //read header and data
    int i = 1; // NEED TO CHANGE TO 2
    while (i < argc && argc > 1)
    { // CHANGE TO 2
        BITMAP bm;
        bm.header = (HEADER *)malloc(sizeof(HEADER));
        char* filename=argv[i];
        list(filename, &bm);
        i++;
        if (i != argc)
        {
            printf("\n*******************************");
        }
        //read data
        int numOfPixels=bm.header->biHeight*bm.header->biWidth;
        printf("\npixels: %d\n", numOfPixels);
        bm.data=(BYTE*)malloc(sizeof(BYTE)*numOfPixels*3);
        readData(filename, &bm, numOfPixels*3);
    }
}
