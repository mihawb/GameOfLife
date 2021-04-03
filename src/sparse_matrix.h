#ifndef _SPARSE_MATRIX_IS_INCLUDED_
#define _SPARSE_MATRIX_IS_INCLUDED_

void add_cell(int** X, int** Y, int** V, int x, int y, int v, int* sizeF, int* sizeA);
void remove_cell(int** X, int** Y, int** V, int x, int y, int* sizeF, int* sizeA);
void dealloc_if_needed(int** X, int** Y, int** V, int* sizeF, int* sizeA);
int count_alive(int* X, int* Y, int* V, int x, int y, int* sizeF);
int init_from_file(int** X, int** Y, int** V, int* sizeF, int* sizeA, char* filename);

int find_elem(int* X, int* Y, int* V, int x, int y, int sizeF);

#endif
