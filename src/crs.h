#ifndef _CRS_H_IS_INCLUDED_
#define _CRS_H_IS_INCLUDED_

typedef struct x {
    int rows;
    int cols;
    int *VALUES;
    int *COL_INDEX;
    int *ROW_INDEX;
} CRSt;

int initCRSFromFile(char * fileName, CRSt crs); // MIEJMY NADZIEJE ZE TU JEST DOBRZE ZEBY NIE BYLO KWASU Z ALOKACJA
/*void addElementToCRS(int row, int col, int val, CRSt crs);
void rmElementFromCRS(int row, int col, CRSt crs);
void debugPrintCRS(CRSt crs);*/

#endif