/* bitmap.h Copyright (C) 2022 Andria-Maria Papageorgiou Marios Epameinonda
This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'. 
This is free software, and you are welcome to redistribute it
under certain conditions; type `show c' for details.
Υou should have received a copy of the GNU General Public License along with 
this program. If not, see <http://www.gnu.org/licenses/>.*/
/**
 * @file bitmap.h
 * @brief This header is the struct of the bitmap of an image.
 * 
 * @author Andria-Maria Papageorgiou, Marios Epameinonda
 * 
 * @bug No known bugs
 */
#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#ifndef BITMAP_H
#define BITMAP_H


typedef struct
{
    HEADER header; 
    BYTE* data;
} __attribute__ ((__packed__)) BITMAP;

//void initializeBM(BITMAP *bm);

#endif