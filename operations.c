/* bmplib.c Copyright (C) 2022 Andria-Maria Papageorgiou Marios Epameinonda
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'. 
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
Υou should have received a copy of the GNU General Public License along with 
this program. If not, see <http://www.gnu.org/licenses/>.*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "header.h"
#include "bitmap.h"
#include "operations.h"

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

    int i = 2; 
    while (i < argc && argc > 2) //for all given images
    { 
        BITMAP bm;
        BITMAP bmGray;
        char *filename = argv[i];

        FILE *fp = fopen(filename, "rb");
        fread(&(bm.header), sizeof(HEADER), 1, fp); // read header

        int numOfPixels = bm.header.biHeight * bm.header.biWidth;
        int padding = ((bm.header.biWidth) * 3) % 4;
        int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
        bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        readData(filename, &bm, dataBytes);

        // printHeader(&(bm.header));

        int j = 0;
        BYTE luminance = 0;

        copyHeader(&bm, &bmGray);
        bmGray.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);

        for (j = 0; j < dataBytes; j = j + 3)
        {
            BYTE R = bm.data[j], G = bm.data[j + 1], B = bm.data[j + 2];

            luminance = round(R * 0.299 + G * 0.587 + B * 0.114);
            bmGray.data[j] = luminance;
            bmGray.data[j + 1] = luminance;
            bmGray.data[j + 2] = luminance;
            luminance = 0;
        }
        i++;
        writeImage(bmGray, "grayscale.bmp", dataBytes);
        free(bm.data);
        free(bmGray.data);
        fclose(fp);
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
    fclose(fp2);
}

void list(int argc, char *argv[])
{
    int i = 2; 
    while (i < argc && argc > 2)
    { 
        BITMAP bm;

        char *filename = argv[i];

        FILE *fp = fopen(filename, "rb");
        fread(&(bm.header), sizeof(HEADER), 1, fp); // read header

        printHeader(&(bm.header));

        int numOfPixels = bm.header.biHeight * bm.header.biWidth;
        int padding = ((bm.header.biWidth) * 3) % 4;
        int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;

        bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        readData(filename, &bm, dataBytes);

        i++;
        if (i != argc)
        {
            printf("\n*******************************");
        }
        fclose(fp);
        free(bm.data);
    }
}

static void readData(char *filename, BITMAP *bm, int size)
{
    FILE *fp = fopen(filename, "rb");
    fseek(fp, 54, SEEK_SET);
    int padding = ((bm->header.biWidth) * 3) % 4;
    int i = 0;
    int j = 0;
    int count = 0;
    int index = 0;
    for (i = 0; i < bm->header.biHeight; i++)
    {
        for (j = 0; j < (bm->header.biWidth + padding) * 3; j++)
        {
            count++;
            fread(&(bm->data[index]), 1, 1, fp); 
            index++;
        }
    }
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
    fread(&(secret.header), sizeof(HEADER), 1, fpSecret); // read header

    fclose(fpCover);
    fclose(fpSecret);

    if (cover.header.biHeight == secret.header.biHeight && cover.header.biWidth == secret.header.biWidth)
    {
        int numOfPixels = cover.header.biHeight * cover.header.biWidth;
        int padding = ((cover.header.biWidth) * 3) % 4;
        int dataBytes = numOfPixels * 3 + cover.header.biHeight * padding * 3;

        cover.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        secret.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
        readData(fp1, &cover, dataBytes);
        readData(fp2, &secret, dataBytes);

        int p = 0;
        int byte = 0;
        //get the bits i want from secret image and replaces the bits i want of cover image in order 
        //to hide the most important bits into the less important bits of cover image
        for (byte = 0; byte < dataBytes; byte++)
        {
            for (p = 0; p < 4; p++)
            {

                int highBit = ((secret.data[byte] & (int)(pow(2, 7 - p))) << p) >> 7; // fernw to bit pou thelw full aristera kai meta full deksia gia na epistrafei
                
                if (highBit == 1)
                {
                    
                    cover.data[byte] = cover.data[byte] | (int)(pow(2, 3 - p)); // ola ta psifia 1 extos to index pou thelw pou einai 0
                }
                else
                {
                    cover.data[byte] = cover.data[byte] & (254 - (int)pow(2, 3 - p) + 1); // ola 0 ektos to index pu thelw einai 1
                }
            }
        }
        char c[100];
        char *fpNew = "new-";
        strcat(c, fpNew);
        strcat(c, fp1);
        writeImage(cover, c, dataBytes);
        free(cover.data);
        free(secret.data);
    }
    else
    {
        printf("The two images should have the same size.\n");
        exit(0);
    }
}

static void printBinary(BYTE *data, int index)
{
    int n = 0;
    int binary[8];
    for (n = 0; n < 8; n++)
    {
        binary[7 - n] = (data[index] >> n) & 1; //get each bit of BYTE
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

    int numOfPixels = encrypted.header.biHeight * encrypted.header.biWidth;
    int padding = ((encrypted.header.biWidth) * 3) % 4;
    int dataBytes = numOfPixels * 3 + encrypted.header.biHeight * padding * 3;

    encrypted.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
    readData(filename, &encrypted, dataBytes);

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
    { 
        //get the 4 lowest bits from encrypted image and insert them as highest bits in 
        //the secret image to be created
        for (p = 0; p < 4; p++)
        {
            bit = ((encrypted.data[byte] & (int)pow(2, 3 - p)) << (4 + p)) >> 7; //get each 1 of 4 dersired bits
            if (bit == 0)
            {
                bm.data[byte] = bm.data[byte] & (254 - (int)pow(2, 3 - p) + 1);
            }
            else
            {
                bm.data[byte] = bm.data[byte] | (int)pow(2, 3 - p);
            }
        }
        bm.data[byte] = bm.data[byte] << 4; //fill the remaining 4 bits with 0 by shifting
    }
    char c[100];
    int t;
    for (t = 0; t < 100; t++)
    {
        c[t] = 0;
    }
    char *fpNew = "new-";
    strcat(c, fpNew);
    strcat(c, filename);
    writeImage(bm, c, dataBytes);
    free(encrypted.data);
    free(bm.data);
}

void encodeText(int argc, char *argv[])
{
    char *fp1 = argv[2];
    char *fp2 = argv[3];
    FILE *imageFile = fopen(fp1, "rb");
    FILE *txtFile = fopen(fp2, "r");

    BITMAP bm;
    fread(&(bm.header), sizeof(HEADER), 1, imageFile);

    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = ((bm.header.biWidth) * 3) % 4;
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE));
    readData(fp1, &bm, dataBytes);

    if (!txtFile)
    {
        perror("Input error");
    }

    fseek(txtFile, 0, SEEK_END);
    int fileSize = ftell(txtFile);
    // printf("filesize: %d\n", fileSize);
    fseek(txtFile, 0, SEEK_SET);

    char *text = (char *)malloc((fileSize + 1) * sizeof(char)); //array with text

    int i = 0;
    int c;
    //read text from file and save it to the char* array
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
    int *permutation;
    permutation = createPermutationFunction((fileSize * 8), 10); //random bytes

    for (i = 0; i < strlen(text) * 8; i++)
    {
        b = getBit(text, i); // pianw to bit
        
        o = permutation[i]; // pianw to byte sto opoio tha mpei
        
        if (b == 0)
        {
            bm.data[o] = bm.data[o] & 254; // gia na kanw to teleftaio bit 0
        }
        else
        {
            bm.data[o] = bm.data[o] | 1; // gia na kanw last bit 1
        }
    }
    char new[100];
    char *fpNew = "new-";
    strcat(new, fpNew);
    strcat(new, fp1);
    writeImage(bm, new, dataBytes);
    fclose(imageFile);
    fclose(txtFile);
    free(text);
    free(bm.data);
    free(permutation);
}

static int getBit(char *m, int n)
{
    int totalSize = strlen(m) * 8;
    int index;
    int bit;
    if (n < totalSize)
    {
        index = n / 8; //find index of array
        bit = ((m[index] & (int)pow(2, 7 - n % 8)) << (0 + (n % 8))) >> 7; //get the bit of the char
        return bit;
    }
    else
    {
        return 0;
    }
}

static int *createPermutationFunction(int N, unsigned int systemkey)
{
    int *arr = (int *)malloc(sizeof(int) * N); 
    int k;
    //create an int array with values [0, N-1]
    for (k = 0; k < N; k++)
    {
        arr[k] = k;
    }

    int i;
    int j;
    int temp;
    int p;
    srand(systemkey);
    //shuffle int *arr 
    for (k = 0; k < N; k++)
    {
        // pick two random numbers
        i = rand() % (N - 1);
        j = rand() % (N - 1);
        temp = arr[i];
        //swaping the two indeces
        arr[i] = arr[j];
        arr[j] = temp;
    }

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

    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = ((bm.header.biWidth) * 3) % 4;
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE));
    readData(fp1, &bm, dataBytes);

    int p;
    BYTE *text = (BYTE *)malloc(msgLength * sizeof(BYTE)); //array for the chars to be saved

    text[msgLength] = '\0';

    int *permutation = (int *)malloc(sizeof(int) * ((msgLength - 1) * 8));

    permutation = createPermutationFunction(((msgLength - 1) * 8), 10);

    int i = 0;
    int bit;
    int index = 0;
    char c;
    int ind = 0;
    int counter = 0;

    // take each random byte drom Permutation and extract its last bit which is part of
    // the representation of each char
    for (i = 0; i < (msgLength - 1) * 8; i++)
    {
        index = permutation[i];
        bit = (bm.data[index] & 1);
        c = c << 1;
        c = c | bit;
        counter++;
        //each 8 bits which are extracted a character is created and added to the array
        if (counter == 8)
        {
            text[ind] = c;
            ind++;
            counter = 0;
        }
    }

    printf("%s ", text);
    fwrite(text, msgLength, 1, outputFile);
    fclose(outputFile);
    free(bm.data);
    free(text);
    free(permutation);
}

void stringToImage(int argc, char *argv[])
{
    char *fp1 = argv[2];
    char *fp2 = argv[3];
    FILE *fileImage = fopen(fp1, "rb");
    FILE *txtFile = fopen(fp2, "r");

    BITMAP bm;
    fread(&(bm.header), sizeof(HEADER), 1, fileImage);
    fclose(fileImage);

    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = (bm.header.biWidth * 3) % 4;
    // printf("padding %d\n", padding);
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);

    if (!txtFile)
    {
        perror("Input error\n");
    }
    fseek(txtFile, 0, SEEK_END);
    int fileSize = ftell(txtFile);
    // printf("filesize: %d\n", fileSize);
    fseek(txtFile, 0, SEEK_SET);

    //read each char of the file and add it to the char* array
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
    // printf("%s\n", text);

    int totalBits = fileSize * 8;

    // }
    BYTE **pixels = (BYTE **)malloc(bm.header.biHeight * sizeof(BYTE *));
    for (i = 0; i < bm.header.biHeight; i++)
    {
        pixels[i] = (BYTE *)malloc(bm.header.biWidth * sizeof(BYTE));
    }
    // printf("height %d\n", bm.header.biHeight);
    // printf("width %d\n", bm.header.biWidth);

    int j = 0;
    int counter = 0;
    for (i = 0; i < bm.header.biHeight; i++)
    {
        for (j = 0; j < bm.header.biWidth; j++)
        {
            if (counter < totalBits) // in case our text is smaller than databytes
            {
                // the other formula didnt word
                // printf("\ni %d j %d\n", i, j);
                // printf("num of bit %d\n", counter);
                pixels[i][j] = 128 * getBit(text, counter);
                // printf("pixels[%d][%d]=%d\n", i, j, pixels[i][j]);
                counter++;
            }
            else // text smaller than image then fill remaining pixels with 0
            {
                pixels[i][j] = 0;
            }
        }
    }

    // printf("\n\n counter %d \n\n", counter);
    // printf("pixels %d\n", numOfPixels);
    // printf("totalBits %d\n", totalBits);
    // printf("databytes %d\n", dataBytes);

    counter = 0;
    int p;
    for (j = bm.header.biWidth + padding - 1; j >= 0; j--)
    {
        for (i = 0; i < bm.header.biHeight; i++)
        {
            bm.data[counter] = pixels[i][j - padding];
            bm.data[counter + 1] = pixels[i][j - padding];
            bm.data[counter + 2] = pixels[i][j - padding];
            // printf("pixels[%d][%d]=%u bm.data[%d]=%u\n", i, j, pixels[i][j-padding], counter, bm.data[counter]);
            // printf("pixels[%d][%d]=%u bm.data[%d]=%u\n", i, j, pixels[i][j-padding], counter+1, bm.data[counter+1]);
            // printf("pixels[%d][%d]=%u bm.data[%d]=%u\n", i, j, pixels[i][j-padding], counter+2, bm.data[counter+2]);
            counter += 3;
        }
        // insert padding
        for (p = 0; p < padding; p++)
        {
            bm.data[counter] = 0;
            bm.data[counter + 1] = 0;
            bm.data[counter + 2] = 0;
            counter += 3;
        }
    }

    char new[100];
    char *fpNew = "new-";
    strcat(new, fpNew);
    // printf("file %s\n", fp1);
    strcat(new, fp1);
    // printf("new file : %s\n", c);
    writeImage(bm, new, dataBytes);
    fclose(txtFile);
    free(text);
    free(bm.data);
    for (i = 0; i < bm.header.biHeight; i++)
    {
        free(pixels[i]); 
    }
    free(pixels);
    
}

void imageToString(int argc, char *argv[])
{
    // printf("fuck\n");
    char *fp1 = argv[2];
    FILE *imageFile = fopen(fp1, "rb");
    BITMAP bm;
    FILE *outputFile = fopen("output.txt", "r");

    fread(&(bm.header), sizeof(HEADER), 1, imageFile);
    fclose(imageFile);

    int numOfPixels = bm.header.biHeight * bm.header.biWidth;
    int padding = (bm.header.biWidth * 3) % 4;
    int dataBytes = numOfPixels * 3 + bm.header.biHeight * padding * 3;
    bm.data = (BYTE *)malloc(sizeof(BYTE) * dataBytes);
    readData(fp1, &bm, dataBytes);
    // printf("padding %d\n", padding);

    int len = (dataBytes / 3) / 8;

    BYTE *text = (BYTE *)malloc(len + 1 * sizeof(BYTE));

    text[len] = '\0';

    int i = 0;
    // for (i = 0; i < dataBytes; i += 3)
    // {
    //     printf("%d, ", bm.data[i]);
    // }
    int bit;
    int index = 0;
    char c;
    int ind = 0;
    int counter = 0;

    for (i = 0; i < dataBytes / 3; i += 3)
    {
        bit = (int)bm.data[i];
        if (bit == 128)
        {
            bit = 1;
        }
        // printf("bit %d data[%d]=%u\n", bit, i, bm.data[i]);
        c = c << 1;
        c = c | bit;
        counter++;
        if (counter == 8)
        {
            // printf("c *%c*\n", c);
            text[ind] = c;
            ind++;
            counter = 0;
        }
    }

    printf("%s ", text);
    fwrite(text, sizeof(BYTE), len+1, outputFile);
    fclose(outputFile);
    free(bm.data);
    free(text);
    // fwrite(text, msgLength, 1, outputFile);
}

#ifdef DEBUG
int main()
{
    char *argvList[4] = {"./bmpSteganography", "-list", "4x3.bmp", "image2.bmp"};
    list(4, argvList);
    char *argvGray[4] = {"./bmpSteganography", "-grayscale", "image1.bmp"};
    grayscale(3, argvGray);
    char *argvEnS[5] = {"./bmpSteganography", "-encodeStegano", "4", "IMG_6865.bmp", "IMG_6875.bmp"};
    encodeStegano(5, argvEnS);
    char *argvDeS[4] = {"./bmpSteganography", "-decodeStegano", "4", "new-IMG_6865.bmp"};
    decodeStegano(4, argvDeS);
    char *argvEnTxt[4] = {"./bmpSteganography", "-encodeText", "tux-bonaparte.bmp", "poem.txt"};
    encodeText(4, argvEnTxt);
    char *argvDecTxt[5] = {"./bmpSteganography", "-decodeText", "new-tux-bonaparte.bmp", "280", "new-poem.txt"};
    decodeText(5, argvDecTxt);
    char *argvStrBmp[4] = {"./bmpSteganography", "-stringToImage", "tux-pirate.bmp", "strFile.txt"};
    stringToImage(4, argvStrBmp);
    char *argvBmpStr[3] = {"./bmpSteganography", "-imageToString", "encryptedTextImage.bmp";
    imageToString(3, argvBmpStr);


}
#endif