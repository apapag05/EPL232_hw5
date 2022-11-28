#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "list.h"
#include "header.h"
#include "bitmap.h"

static void writeImage(BITMAP bm, char *filename, int dataBytes);
static void readData(char *filename, BITMAP *bm, int size);
static void printHeader(HEADER *header);
void list(int argc, char *argv[]);
static void copyHeader(BITMAP *bm, BITMAP *bm2);
void encodeStegano(int argc, char *argv[]);
static void printBinary(BYTE *data, int index);
static void decToBin(int num);
void decodeStegano(int argc, char *argv[]);
void encodeText(int argc, char *argv[]);
static int getBit(char *m, int n);
static int *createPermutationFunction(int N, unsigned int systemkey);
static void putBit(char *m, int n, int b);
void stringToImage(int argc, char *argv[]);

static void printHeader(HEADER *header)
{
    printf("\nBITMAP_FILE_HEADER\n==================\n");
    printf("bfType: %c%c\n", header->bfType1, header->bfType2);
    printf("bfSize: %u\n", header->bfSize);
    printf("bfResereved1: %hu\n", header->bfReserved1);
    printf("bfResereved2: %hu\n", header->bfReserved2);
    printf("bfOffBits: %u\n", header->bfOffBits);
    printf("\nBITMAP_INFO_HEADER\n==================\n");
    printf("biSize: %u\n", header->biSize);
    printf("biWidth: %u\n", header->biWidth);
    printf("biHeight: %u\n", header->biHeight);
    printf("biPlanes: %hu\n", header->biPlanes);
    printf("biBitCount: %hu\n", header->biBitCount);
    printf("biCompression %u\n", header->biCompression);
    printf("biSizeImage: %u\n", header->biSizeimage);
    printf("biXPelsPerMeter: %u\n", header->biXPelsPerMeter);
    printf("biYPelsPerMeter: %u\n", header->biYPelsPerMeter);
    printf("biClrUsed: %u\n", header->biClrUsed);
    printf("biClrImportant: %u\n", header->biClrImportant);
}

void grayscale(int argc, char *argv[])
{

    int i = 2; // CHANGE TO 2
    while (i < argc && argc > 2)
    { // CHANGE TO 2
        BITMAP bm;
        BITMAP bmGray;
        char *filename = argv[i];

        FILE *fp = fopen(filename, "rb");
        fread(&(bm.header), sizeof(HEADER), 1, fp); // read header
        int numOfPixels = bm.header.biHeight * bm.header.biWidth;
        int padding = ((bm.header.biWidth) * 3) % 4;
        printf("\npadding %d\n", padding);
        int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
        printf("\npixels: %d\n and data bytes %d\n", numOfPixels, dataBytes);
        bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        readData(filename, &bm, dataBytes);

        printHeader(&(bm.header));

        int j = 0;
        BYTE luminance = 0;

        copyHeader(&bm, &bmGray);
        bmGray.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);

        for (j = 0; j < dataBytes; j = j + 3)
        {
            BYTE R = bm.data[j], G = bm.data[j + 1], B = bm.data[j + 2];

            luminance = round(R * 0.299 + G * 0.587 + B * 0.114);
            printf("liuminanve %d\n", luminance);
            printf("i %d byte 1 %hu byte2 %hu byte3 %hu\n", j, bm.data[j], bm.data[j + 1], bm.data[j + 2]);
            bmGray.data[j] = luminance;
            bmGray.data[j + 1] = luminance;
            bmGray.data[j + 2] = luminance;
            printf("AFTERR byte 1 %hu byte2 %hu byte3 %hu\n", bm.data[j], bm.data[j + 1], bm.data[j + 2]);
            luminance = 0;
        }
        i++;
        writeImage(bmGray, "grayscale.bmp", dataBytes);
        // exit(0);
    }
}

static void copyHeader(BITMAP *bm, BITMAP *bm2)
{

    bm2->header.bfType1 = bm->header.bfType1;
    bm2->header.bfType2 = bm->header.bfType2;
    bm2->header.bfSize = bm->header.bfSize;
    bm2->header.bfReserved1 = bm->header.bfReserved1;
    bm2->header.bfReserved2 = bm->header.bfReserved2;
    bm2->header.bfOffBits = bm->header.bfOffBits;
    bm2->header.biSize = bm->header.biSize;
    bm2->header.biWidth = bm->header.biWidth;
    bm2->header.biHeight = bm->header.biHeight;
    bm2->header.biPlanes = bm->header.biPlanes;
    bm2->header.biBitCount = bm->header.biBitCount;
    bm2->header.biCompression = bm->header.biCompression;
    bm2->header.biSizeimage = bm->header.biSizeimage;
    bm2->header.biXPelsPerMeter = bm->header.biXPelsPerMeter;
    bm2->header.biYPelsPerMeter = bm->header.biYPelsPerMeter;
    bm2->header.biClrUsed = bm->header.biClrUsed;
    bm2->header.biClrImportant = bm->header.biClrImportant;
    printHeader(&(bm2->header));
}

static void writeImage(BITMAP bm, char *filename, int dataBytes)
{
    FILE *fp2 = fopen(filename, "wb");
    fwrite(&(bm.header.bfType1), sizeof(BYTE), 1, fp2);
    fwrite(&(bm.header.bfType2), sizeof(BYTE), 1, fp2);
    fwrite(&(bm.header.bfSize), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.bfReserved1), sizeof(WORD), 1, fp2);
    fwrite(&(bm.header.bfReserved2), sizeof(WORD), 1, fp2);
    fwrite(&(bm.header.bfOffBits), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biSize), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biWidth), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biHeight), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biPlanes), sizeof(WORD), 1, fp2);
    fwrite(&(bm.header.biBitCount), sizeof(WORD), 1, fp2);
    fwrite(&(bm.header.biCompression), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biSizeimage), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biXPelsPerMeter), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biYPelsPerMeter), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biClrUsed), sizeof(DWORD), 1, fp2);
    fwrite(&(bm.header.biClrImportant), sizeof(DWORD), 1, fp2);
    int k = 0;
    for (k = 0; k < dataBytes; k++)
    {
        fwrite(&(bm.data[k]), sizeof(BYTE), 1, fp2);
    }
}

void list(int argc, char *argv[])
{
    int i = 2; // CHANGE TO 2
    while (i < argc && argc > 2)
    { // CHANGE TO 2
        BITMAP bm;

        char *filename = argv[i];

        FILE *fp = fopen(filename, "rb");
        fread(&(bm.header), sizeof(HEADER), 1, fp); // read header

        printHeader(&(bm.header));

        int numOfPixels = bm.header.biHeight * bm.header.biWidth;
        int padding = ((bm.header.biWidth) * 3) % 4;
        printf("\npadding %d\n", padding);
        int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
        printf("\npixels: %d\n and data bytes %d\n", numOfPixels, dataBytes);

        // int numOfPixels = bm.header.biHeight * bm.header.biWidth;
        // int dataBytes = numOfPixels * 3;
        // printf("\npixels: %d\n", numOfPixels);
        bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        readData(filename, &bm, dataBytes);
        // int j = 0;
        // for (j = 0; j < dataBytes; j++) {
        //     printf("%d, ", bm.data[j]);
        // }

        i++;
        if (i != argc)
        {
            printf("\n*******************************");
        }
    }
}

static void readData(char *filename, BITMAP *bm, int size)
{
    // printf("filename %s\n", filename);
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 54, SEEK_SET);
    int padding = ((bm->header.biWidth) * 3) % 4;
    printf("\npadding %d\n", padding);
    int i = 0;
    int j = 0;
    int count = 0;
    int index = 0;
    //%02X
    printf("count: %d should be: %d\n", count, size);
    // exit(0);
    for (i = 0; i < bm->header.biHeight; i++)
    {
        for (j = 0; j < (bm->header.biWidth + padding) * 3; j++)
        {
            count++;
            fread(&(bm->data[index]), 1, 1, fp); // red
            // printf("i: %d j: %d data[%d] %02X\n", i, j, index, bm->data[index]);

            index++;
        }
        // if (padding != 0) //do not skip
        // {
        //     fseek(fp, padding * 3, SEEK_CUR);
        // }

        // printf("i: %d j: %d data[i] %02X\n", i, j, bm->data[i]);
    }
    printf("count: %d should be: %d\n", count, size);
    fclose(fp);
}

void encodeStegano(int argc, char *argv[])
{

    int nbBits = atoi(argv[2]);
    char *fp1 = argv[3];
    char *fp2 = argv[4];
    FILE *fpCover = fopen(fp1, "rb");
    FILE *fpSecret = fopen(fp2, "rb");
    BITMAP cover;
    BITMAP secret;

    fread(&(cover.header), sizeof(HEADER), 1, fpCover); // read header
    // printHeader(&(cover.header));
    fread(&(secret.header), sizeof(HEADER), 1, fpSecret); // read header
    // printHeader(&(secret.header));

    fclose(fpCover);
    fclose(fpSecret);

    // #define LOW_BIT 0x01  /* binary 00000001 */
    // #define HIGH_BIT 0x80 /* binary 10000000 */
    // int LowBit_Setting = TheChar &LOW_BIT
    // int HighBit_Setting = (TheChar & HIGH_BIT) >> 7

    if (cover.header.biHeight == secret.header.biHeight && cover.header.biWidth == secret.header.biWidth)
    {
        // printf("Same size\n");
        int numOfPixels = cover.header.biHeight * cover.header.biWidth;
        int padding = ((cover.header.biWidth) * 3) % 4;
        // printf("\npadding %d\n", padding);
        int dataBytes = numOfPixels * 3 + cover.header.biHeight * padding * 3;
        // printf("\npixels: %d\n and data bytes %d\n\n\n", numOfPixels, dataBytes);

        // exit(0);
        cover.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        secret.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        readData(fp1, &cover, dataBytes);
        readData(fp2, &secret, dataBytes);

        int p = 0;
        // for (p = 0; p < 12; p++)
        // {
        //     printf("%u,", cover.data[p]);
        // }
        int byte = 0;
        for (byte = 0; byte < dataBytes; byte++)
        {
            for (p = 0; p < 4; p++)
            {
                // printf("\n\nsecret : ");
                // printBinary(secret.data, 0);
                // printf("cover : ");
                // printBinary(cover.data, 0);

                int highBit = ((secret.data[byte] & (int)(pow(2, 7 - p))) << p) >> 7; // fernw to bit pou thelw full aristera kai meta full deksia gia na epistrafei
                // decToBin(highBit);
                if (highBit == 1)
                {
                    // printf("\n1 p= %d %d\n", p, (int)(pow(2, 3 - p)));
                    cover.data[byte] = cover.data[byte] | (int)(pow(2, 3 - p)); // ola ta psifia 1 extos to index pou thelw pou einai 0
                }
                else
                {
                    // printf("\n2 p = %d %d\n", p, 254 - (int)pow(2, p) + 1);
                    cover.data[byte] = cover.data[byte] & (254 - (int)pow(2, 3 - p) + 1); // ola 0 ektos to index pu thelw einai 1
                }
                // printf("cover after : ");
                // printBinary(cover.data, 0);
                // // printf("lowbit %d\n", lowBit);
                // printf("highbit %d\n", highBit);
                // printf("pbinary high \n");
                // // int j=0;
                // // for (j=0;j<8;j++) {
                // //     printf("%d", high[j]);
                // // }
                // printf("secret after: ");
                // printBinary(secret.data, 0);
            }
        }
        // printf("\n\n*************************\n\n");
        // for (p = 0; p < 12; p++)
        // {
        //     printf("%u,", cover.data[p]);
        // }
        char c[100];
        char *fpNew = "new-";
        strcat(c, fpNew);
        // printf("file %s\n", fp1);
        strcat(c, fp1);
        // printf("new file : %s\n", c);
        writeImage(cover, c, dataBytes);
        //////////////////////int lowBit = secret.data[0] & 1;
    }
    else
    {
        printf("The two images should have the same size.\n");
        exit(0);
    }
}

static void printBinary(BYTE *data, int index)
{
    printf("in data %u\n", data[index]);
    int n = 0;
    int binary[8];
    for (n = 0; n < 8; n++)
    {
        binary[7 - n] = (data[index] >> n) & 1;
    }
    for (int n = 0; n < 8; n++)
        printf("%d", binary[n]);
    printf("\n");
}

void decodeStegano(int argc, char *argv[])
{
    int nbits = atoi(argv[2]);
    char *filename = argv[3];
    FILE *fp = fopen(filename, "rb");

    BITMAP encrypted;
    fread(&(encrypted.header), sizeof(HEADER), 1, fp);

    fclose(fp);

    // printf("Same size\n");
    int numOfPixels = encrypted.header.biHeight * encrypted.header.biWidth;
    int padding = ((encrypted.header.biWidth) * 3) % 4;
    // printf("\npadding %d\n", padding);
    int dataBytes = numOfPixels * 3 + encrypted.header.biHeight * padding * 3;
    // printf("\npixels: %d\n and data bytes %d\n\n\n", numOfPixels, dataBytes);

    encrypted.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
    readData(filename, &encrypted, dataBytes);
    // #define LOW_BIT 0x01  /* binary 00000001 */
    // #define HIGH_BIT 0x80 /* binary 10000000 */
    // int LowBit_Setting = TheChar &LOW_BIT
    // int HighBit_Setting = (TheChar & HIGH_BIT) >> 7

    BITMAP bm;
    copyHeader(&encrypted, &bm);
    bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);

    int byte = 0;
    for (byte = 0; byte < dataBytes; byte++)
    {
        bm.data[byte] = 0;
    }
    int p = 0;
    int bit;
    for (byte = 0; byte < dataBytes; byte++)
    { // CHANGE 6 TO DATABYTES
        // printf("\n\nbyte %d encrypted before: ", byte);
        // printBinary(encrypted.data, byte);
        // printf("before data[%d] : ", byte);
        // printBinary(bm.data, byte);
        for (p = 0; p < 4; p++)
        {
            // highBit = ((encrypted.data[byte] & (int)(pow(2, 7 - p))) << p) >> 7;
            bit = ((encrypted.data[byte] & (int)pow(2, 3 - p)) << (4 + p)) >> 7;
            // printf("p = %d bit: %d\n", p, bit);
            if (bit == 0)
            {
                // printf("bittttt 0\n");
                bm.data[byte] = bm.data[byte] & (254 - (int)pow(2, 3 - p) + 1);
                // printf("after 0 data[%d] : ", byte);
                // printBinary(bm.data, byte);
            }
            else
            {
                // printf("bittttt 1\n");
                bm.data[byte] = bm.data[byte] | (int)pow(2, 3 - p);
                // printf("after 1 data[%d] : ", byte);
                // printBinary(bm.data, byte);
            }
        }
        bm.data[byte] = bm.data[byte] << 4;
        // printf("after final data[%d] : ", byte);
        // printBinary(bm.data, byte);
    }
    char c[100];
    char *fpNew = "new-";
    strcat(c, fpNew);
    // printf("file %s\n", fp1);
    strcat(c, filename);
    // printf("new file : %s\n", c);
    writeImage(bm, c, dataBytes);
}

void encodeText(int argc, char *argv[])
{
    char *fp1 = argv[2];
    char *fp2 = argv[3];
    FILE *imageFile = fopen(fp1, "rb");
    FILE *txtFile = fopen(fp2, "r");

    BITMAP bm;
    fread(&(bm.header), sizeof(HEADER), 1, imageFile);
    // printHeader(&(bm.header));
    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = ((bm.header.biWidth) * 3) % 4;
    // printf("\npadding %d\n", padding);
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE));
    readData(fp1, &bm, dataBytes);

    if (!txtFile)
    {
        perror("Input error");
    }

    fseek(txtFile, 0, SEEK_END);
    int fileSize = ftell(txtFile);
    printf("filesize: %d\n", fileSize);
    fseek(txtFile, 0, SEEK_SET);

    char *text = (char *)malloc((fileSize + 1) * sizeof(char));

    int i = 0;
    int c;
    while (1)
    {
        c = fgetc(txtFile);
        if (c == EOF)
        {
            break;
        }
        text[i] = (char)c;
        i++;
    }

    text[fileSize] = '\0';
    printf("%s", text);

    int b, o;
    int *permutation = (int *)malloc(sizeof(int) * (fileSize * 8));
    permutation = createPermutationFunction((fileSize * 8), 10);
    // printf("************************strlen %d", fileSize*8);
    // printf("\n\npermutation*****************\n\n");
    // for (i=0;i<fileSize*8;i++) {
    //     printf("%d, ", permutation[i]);
    // }
    // printf("counter i %d\n", i);

    for (i = 0; i < strlen(text) * 8; i++)
    {
        b = getBit(text, i); // pianw to bit
        // printf("bit: %d\n", b);
        o = permutation[i]; // pianw to byte sto opoio tha mpei
        // printf("o: %d\n", o);
        // printf("data before %u\n", bm.data[o]);
        if (b == 0)
        {
            // printf("it is 0\n");
            bm.data[o] = bm.data[o] & 254; // gia na kanw to teleftaio bit 0
        }
        else
        {
            // printf("it is 1\n");
            bm.data[o] = bm.data[o] | 1; // gia na kanw last bit 1
        }
        // printf("data after %u\n", bm.data[o]);
    }
    char new[100];
    char *fpNew = "new-";
    strcat(new, fpNew);
    // printf("file %s\n", fp1);
    strcat(new, fp1);
    // printf("new file : %s\n", c);
    writeImage(bm, new, dataBytes);
}

static int getBit(char *m, int n)
{
    // PIANW SWSTA TA BITS APO TIS LEKSEIS GOOD

    // printf("size in getbit %lu\n", strlen(m));
    int totalSize = strlen(m) * 8;
    int index;
    int bit;
    if (n < totalSize)
    {
        // printf("total size: %d\n", totalSize);
        index = n / 8;
        // printf("char %c ascii %d index %d", m[index], m[index], index);
        bit = ((m[index] & (int)pow(2, 7 - n % 8)) << (0 + (n % 8))) >> 7;
        // printf("bit= %d\n", bit);
        return bit;
    }
    else
    {
        return 0;
    }
}

static int *createPermutationFunction(int N, unsigned int systemkey)
{
    // IT IS CHECKED AND IT IS OKAY

    int *arr = (int *)malloc(sizeof(int) * N); // POTE TO KANW FREE?
    int k;
    for (k = 0; k < N; k++)
    {
        arr[k] = k;
        // printf("%d, ", arr[k]);
    }
    printf("len of permutation %d\n", k);
    int i;
    int j;
    int temp;
    int p;
    srand(systemkey);
    for (k = 0; k < N; k++)
    {
        // printf("\nk %d\n", k);
        i = rand() % (N - 1);
        j = rand() % (N - 1);
        // printf("i : %d j : %d\n", i, j);
        // printf("arr[i] before %d\n", arr[i]);
        // printf("arr[j] before %d\n", arr[j]);
        temp = arr[i];
        // printf("temp %d\n", arr[i]);
        arr[i] = arr[j];
        arr[j] = temp;
        // printf("arr[i] after %d\n", arr[i]);
        // printf("arr[j] after %d\n", arr[j]);
        // for (p = 0; p < N; p++)
        // {
        //     printf("%d, ", arr[p]);
        // }
    }
    // printf("%d %d\n", arr[1029], arr[1095]);
    // for (k = 0; k < 50; k++)
    // {
    //     // arr[k] = k;
    //     printf("%d, ", arr[k]);
    // }
    // printf("gamoto\n");
    return arr;
}

void decodeText(int argc, char *argv[])
{
    char *fp1 = argv[2];
    char *fp2 = argv[4];
    FILE *imageFile = fopen(fp1, "rb");
    FILE *outputFile = fopen(fp2, "wb");
    int msgLength = atoi(argv[3]);

    BITMAP bm;
    fread(&(bm.header), sizeof(HEADER), 1, imageFile);
    fclose(imageFile);
    // printHeader(&(bm.header));
    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = ((bm.header.biWidth) * 3) % 4;
    // printf("\npadding %d\n", padding);
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE));
    readData(fp1, &bm, dataBytes);
    int p;
    char *text = (char *)malloc(msgLength * sizeof(char));

    for (p = 0; p < msgLength; p++)
    {
        text[p] = '0';
    }
    printf("size of text %lu\n", strlen(text));
    printf("\n*****************÷****************************************\n\n");
    text[msgLength] = '\0';

    int *bits = (int *)malloc(((msgLength - 1) * 8) * (sizeof(int)));
    int *bitsSorted = (int *)malloc(((msgLength - 1) * 8) * (sizeof(int)));

    int *permutation = (int *)malloc(sizeof(int) * ((msgLength - 1) * 8));

    permutation = createPermutationFunction(((msgLength - 1) * 8), 10);
    // for (p=0;p<(msgLength-1)*8;p++) {
    //     printf("*%d, ", permutation[p]);
    // }
    int i = 0;
    int bit;
    int index = 0;
    // pianw ta bits apo kathe databyte pou exei mesa kriptografimeno bit
    // gemizw ton pinaka me bits me ta anaktamenwmena bits
    for (i = 0; i < (msgLength - 1) * 8; i++)
    {
        index = permutation[i];
        bit = (bm.data[index] & 1);
        // printf("first %d\n", ((bm.data[i] & 1)));
        // printBinary(bm.data, index);
        // printf("data[%d]: %u\n", i, bm.data[i]);
        // printf("bit : %d\n\n", bit);
        bits[i] = bit;
    }
    // printf("********* %d **********\n", i);
    int temp;
    int byte;
    int j = 0;
    for (i = 0; i < (msgLength - 1) * 8; i++)
    {
        byte = permutation[i];
        printf("byte %d\n", permutation[i]);
        bitsSorted[byte] = bits[i];
    }
    
    for (j = 0; j < 30; j++)
    {
        printf("%d, ", bitsSorted[j]);
    }

    printf("lets laugh \n%d", (msgLength - 1) * 8);
}

static void putBit(char *m, int n, int b)
{
    int totalSize = strlen(m) * 8;
    printf("total size: %d\n", totalSize);
    int index;
    int bit;
    if (n < totalSize)
    {
        printf("hmm\n");
        index = n / 8;
        // bit = ((m[index] & (int)pow(2, 7 - n % 8)) << (0 + (n % 8))) >> 7;
        printf("n: %d m[%d] %c\n", n, index, m[index]);
        if (b == 1)
        {
            m[index] = m[index] | (int)pow(2, 7 - n % 8);
            printf("indx 1 after %c\n", m[index]);
        }
        else
        {
            m[index] = m[index] & (255 - (int)pow(2, 7 - n % 8));
            printf("index 0 after %c\n", m[index]);
        }
    }
}

void stringToImage(int argc, char *argv[])
{
    char *fp1 = argv[2];
    char *fp = argv[3];
    FILE *fileImage = fopen(fp1, "rb");
    FILE *txtFile = fopen(fp, "r");
    ;
    BITMAP bm;
    fread(&(bm.header), sizeof(HEADER), 1, fileImage);
    // fread(&(bm.header), sizeof(HEADER), 1, fileImage); // read header
    fclose(fileImage);
    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = ((bm.header.biWidth) * 3) % 4;
    // printf("\npadding %d\n", padding);
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
    // readData(fp1, &bm, dataBytes);
    if (!txtFile)
    {
        perror("Input error");
    }
    fseek(txtFile, 0, SEEK_END);
    int fileSize = ftell(txtFile);
    printf("filesize: %d\n", fileSize);
    fseek(txtFile, 0, SEEK_SET);

    char *text = (char *)malloc((fileSize + 1) * sizeof(char));

    int i = 0;
    int c;
    while (1)
    {
        c = fgetc(txtFile);
        if (c == EOF)
        {
            break;
        }
        text[i] = (char)c;
        i++;
    }
    // printf("i: %d\n");
    text[fileSize] = '\0';
    // printf("%s", text);

    int bitsLen = fileSize * 8;
    int bits[bitsLen];
    for (i = 0; i < bitsLen; i++)
    {
        bits[i] = getBit(text, i);
    }
    // TIPWMA TOU BITS SWSTA MESA KATAXWRHMENA
    //  for (i=0;i<46;i++) {
    //      printf("bits[%d]= %d\n", i, bits[i]);
    //  }
    printf("hmmm\n");
  

    // int k = 0;
    // for (k = 0; k < dataBytes; k++)
    // {
    //     fwrite(&(bm.data[k]), sizeof(BYTE), 1, fp2);
    // }
    int j;
    int index = 0;
    BYTE pixel[3];
    
    for (i = bm.header.biHeight-1; i >= 0; i--)
    {
        for (j = 0; j < bm.header.biWidth; j++)
        {
            bm.data[index] = 128 * getBit(text, (bm.header.biHeight * j) + i);
            bm.data[index + 1] = 128 * getBit(text, (bm.header.biHeight * j) + i);
            bm.data[index + 2] = 128 * getBit(text, (bm.header.biHeight * j) + i);
            index += 3;
            // fwrite(pixel, 3, 1, fp2);
        }
    }
    char new[100];
    char *fpNew = "new-";
    strcat(new, fpNew);
    // printf("file %s\n", fp1);
    strcat(new, fp1);
    // printf("new file : %s\n", c);
    writeImage(bm, new, dataBytes);
    // for (i = 0; i < bm.header.biWidth; i++)
    // {
    //     for (j = 0; j < bm.header.biHeight; j++)
    //     {
    //         pixel[0] = 128 * getBit(text, (bm.header.biHeight * i) + j);
    //         pixel[1] = 128 * getBit(text, (bm.header.biHeight * i) + j);
    //         pixel[2] = 128 * getBit(text, (bm.header.biHeight * i) + j);
    //         // bm.data[index + 2] = 128 * getBit(text, (bm.header.biHeight * j) + i);
    //         index += 3;
    //         fwrite(pixel, 3, 1, fp2);
    //     }
    // }
    // for (i = 0; i < 27; i++)
    // {
    //     printf("%d, ", bm.data[i]);
    // }
    
}

int main(int argc, char *argv[])
{
    //  READ OPERATION  //
    // printf("psssss\n");
    char *operation = argv[1];
    char *l = "-list\0";
    char *g = "-grayscale\0";
    char *enS = "-encodeStegano\0";
    char *decS = "-decodeStegano\0";
    char *encT = "-encodeText\0";
    char *decT = "-decodeText\0";
    char *strToImg = "-stringToImage\0";
    printf("arg %s\n\n", argv[1]);
    if (strcmp(operation, l) == 0)
    {
        printf("firsttt\n");
        list(argc, argv);
    }
    else if (strcmp(operation, g) == 0)
    {
        printf("seconddd\n\n");
        grayscale(argc, argv);
    }
    else if (strcmp(operation, enS) == 0)
    {
        encodeStegano(argc, argv);
    }
    else if (strcmp(operation, decS) == 0)
    {
        decodeStegano(argc, argv);
    }
    else if (strcmp(operation, encT) == 0)
    {
        encodeText(argc, argv);
    }
    else if (strcmp(operation, decT) == 0)
    {
        decodeText(argc, argv);
    }
    else if (strcmp(operation, strToImg) == 0)
    {
        stringToImage(argc, argv);
    }
}
