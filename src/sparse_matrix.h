#ifndef _SPARSE_MATRIX_IS_INCLUDED_
#define _SPARSE_MATRIX_IS_INCLUDED_

int add_cell(int** X, int** Y, int** V, int x, int y, int v, int size);
int remove_cell(int** X, int** Y, int** V, int x, int y, int size);
int count_alive(int* X, int* Y, int* V, int x, int y, int size);
int init_from_file(int** X, int** Y, int** V, int size, char* filename);

#endif