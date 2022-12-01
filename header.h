/* header.h Copyright (C) 2022 Andria-Maria Papageorgiou Marios Epameinonda
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'. 
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
Υou should have received a copy of the GNU General Public License along with 
this program. If not, see <http://www.gnu.org/licenses/>.*/
/**
 * @file bmpSteganography.c 
 *
 * @brief This header is the struct of the header of a bitmap.
 * 
 * @author Andria-Maria Papageorgiou, Marios Epameinonda
 * 
 * @bug No known bugs
 * 
 */

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