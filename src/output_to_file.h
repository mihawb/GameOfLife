#ifndef OUTPUT_TO_FILE_H
#define OUTPUT_TO_FILE_H
#include "sparse_matrix.h"

void output_to_txt(int* X, int* Y, int* V,int sizeF, int rows, int columns,int cycle_number);
void output_to_png(int* X, int* Y, int* V, Color*C, int sizeF, int rows, int columns,int cycle_number);
#endif
