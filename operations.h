/* bmplib.h Copyright (C) 2022 Andria-Maria Papageorgiou Marios Epameinonda
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'. 
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
Υou should have received a copy of the GNU General Public License along with 
this program. If not, see <http://www.gnu.org/licenses/>.*/
/**
 * @file bmplib.h
 * @brief This header contains the prototypes of the library bmplib.a
 * 
 * @author Andria-Maria Papageorgiou, Marios Epameinonda
 * 
 * @bug No known bugs
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "header.h"
#include "bitmap.h"

/**
 * @brief Writes a bitmap.
 * 
 * @param bm bitmap to be written as a .bmp
 * @param filename the name of file which will be created
 * @param dataBytes the size of the data of bitmap
 */
static void writeImage(BITMAP bm, char *filename, int dataBytes);

/**
 * @brief Reads the data of a bitmap from the file.
 * 
 * @param filename name of the file
 * @param bm bitmap
 * @param size size of data of bitmap
 */
static void readData(char *filename, BITMAP *bm, int size);

/**
 * @brief Prints the bitmap file header and the bitmap info header of a bitmap.
 * 
 * @param header the header of a bitmap
 */
static void printHeader(HEADER *header);

/**
 * @brief Prints header of bitmap.
 * 
 * @param argc number of agruments
 * @param argv character array with the arguments 
 */
void list(int argc, char *argv[]);

/**
 * @brief Copies the header of an image to the header of another image.
 * 
 * @param bm bitmap of image 1
 * @param bm2 bitmap of image 2
 */
static void copyHeader(BITMAP *bm, BITMAP *bm2);

/**
 * @brief Hides a picture into another picture.
 * 
 * Replaces n lowest bits of data of cover image with 
 * n highest bits of data of secret image.
 * 
 * @param argc number of agruments
 * @param argv character array with the arguments 
 */
void encodeStegano(int argc, char *argv[]);

/**
 * @brief Print the binary version of a specific index in a BYTE* array.
 * 
 * @param data BYTE* array
 * @param index index of array which need to be printed in binary form
 */
static void printBinary(BYTE *data, int index);
static void decToBin(int num);

/**
 * @brief Gets the secret image which is hidden in another image.
 * 
 * The 4 lowest bits of each databyte represent the 4 highest bits
 * of secret image. So we extract them, add them to secret image
 * and shift left each byte in order to fill 8 bits and create the
 * secret image.
 * 
 * @param argc number of agruments
 * @param argv character array with the arguments 
 */
void decodeStegano(int argc, char *argv[]);

/**
 * @brief Reads a text file and hides the text into an image.
 * 
 * It creates an array which has the random bytes in which
 * each bit of the text will be hidden and then you replace 
 * the last bit of each randomly selected byte of data with
 * a bit of the text.
 * 
 * @param argc number of agruments
 * @param argv character array with the arguments 
 */
void encodeText(int argc, char *argv[]);

/**
 * @brief get the specified bit by finding the index of the 
 * char it is and then extracting the bit.
 * 
 * @param m char* array
 * @param n number of bit
 * @return int the bit
 */
static int getBit(char *m, int n);

/**
 * @brief Create an array with integers which represent the
 * number of data bytes, shuffles them randomly and returns the
 * shuffled array.
 * 
 * @param N size of data of bitmap
 * @param systemkey integer number
 * @return int* shuffled array
 */
static int *createPermutationFunction(int N, unsigned int systemkey);

void stringToImage(int argc, char *argv[]);
void imageToString(int argc, char *argv[]);

/**
 * @brief Decodes a text from an image.
 * 
 * Take each random byte from the data of bitmap, which is indicated 
 * in permutation array, extract its last bit and add it to a variable.
 * Each 8 bits are a repserentation of a char to be adder to the
 * char* array. 
 * 
 * @param argc number of agruments
 * @param argv character array with the arguments 
 */
void decodeText(int argc, char *argv[]);

/**
 * @brief This method create the grayscale version of a given image.
 * 
 * It changes the pixels of the given image.
 * 
 * @param argc number of agruments
 * @param argv character array with the arguments 
 */
void grayscale(int argc, char *argv[]);