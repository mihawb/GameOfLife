#include <stdio.h>
#include <stdlib.h>
#include "crs.h"

#define CRS_INIT_SIZE 10

int initCRSFromFile(char * fileName, CRSt crs)
{
    FILE *inputData = fopen(fileName, "r");
    if (inputData == NULL)
        return -1; // blad wczytania pliku

    fscanf(inputData, "%d %d", &(crs.rows), &(crs.cols));
    printf("DEBUG rows: %d, cols: %d\n", crs.rows, crs.cols);

    crs.VALUES = malloc(CRS_INIT_SIZE * sizeof(int));
    crs.COL_INDEX = malloc(CRS_INIT_SIZE * sizeof(int));
    crs.ROW_INDEX = malloc((crs.rows+1) * (sizeof(int)));

    /*sprawdzenie poprawnosci alokacji
    for (int i = 0; i <= crs.rows; i++) 
        crs.ROW_INDEX[i] = i;

    for (int i = 0; i <= crs.rows; i++) 
        printf("%d\n", crs.ROW_INDEX[i]);
    */

    int indexForRI = 0, indexForVAL = 0;
    int r, c, val;
    for (r = 0; r < crs.rows; r++) {
        crs.ROW_INDEX[r] = indexForRI;
        for (c = 0; c < crs.cols; c++) {
            fscanf(inputData, "%d", &val);
            if (val != 0) {
                crs.VALUES[indexForVAL] = val;
                crs.COL_INDEX[indexForVAL++] = c;
                indexForRI++;
            }
        }
    }
    crs.ROW_INDEX[r] = indexForRI;

    printf("debug indexForVal: %d, indexForRI: %d\n", indexForVAL, indexForRI);
    printf("DEBUG crs.VALUES:");
    for (int i = 0; i < indexForVAL; i++)
        printf(" %d", crs.VALUES[i]);
    printf("\n");

    printf("DEBUG crs.CLOS_INDEX:");
    for (int i = 0; i < indexForVAL; i++)
        printf(" %d", crs.COL_INDEX[i]);
    printf("\n");

    printf("DEBUG crs.ROW_INDEX:");
    for (int i = 0; i < crs.rows+1; i++)
        printf(" %d", crs.ROW_INDEX[i]);
    printf("\n");

    fclose(inputData);
    return 0;
}