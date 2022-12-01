/* bmpSteganography.c Copyright (C) 2022 Andria-Maria Papageorgiou Marios Epameinonda
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'. 
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
Υou should have received a copy of the GNU General Public License along with 
this program. If not, see <http://www.gnu.org/licenses/>.*/
/**
 * @file bmpSteganography.c
 * @brief This module is the main function in which *argv[] is given from terminal
 * and the program executes the desired operation.
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
#include "operations.h"


int main(int argc, char *argv[])
{
    char *operation = argv[1];
    char *l = "-list\0";
    char *g = "-grayscale\0";
    char *enS = "-encodeStegano\0";
    char *decS = "-decodeStegano\0";
    char *encT = "-encodeText\0";
    char *decT = "-decodeText\0";
    char *strToImg = "-stringToImage\0";
    char *imgToStr="-imageToString\0";
    
    // int i=0;
    // int flag=0;
    // for (i=2;i<strlen(argv);i++) {
    //     if (argv[i])
    // }
    if (strcmp(operation, l) == 0)
    {
        // printf("firsttt\n");
        list(argc, argv);
    }
    else if (strcmp(operation, g) == 0)
    {
        // printf("seconddd\n\n");
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
    else if (strcmp(operation, imgToStr) == 0)
    {
        imageToString(argc, argv);
    }
    else {
        printf("Wrong or missed option.\n");
        exit(0);
    }
}

