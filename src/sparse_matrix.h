#ifndef _SPARSE_MATRIX_IS_INCLUDED_
#define _SPARSE_MATRIX_IS_INCLUDED_

typedef struct Color{
    int R;
    int G;
    int B;
}Color;

void add_cell(int** X, int** Y, int** V, Color** C, int x, int y, int v, Color c, int* sizeF, int* sizeA);
void remove_cell(int** X, int** Y, int** V, Color** C, int x, int y, int* sizeF, int* sizeA);
void dealloc_if_needed(int** X, int** Y, int** V, Color** C, int* sizeF, int* sizeA);
int count_alive(int* X, int* Y, int* V, int x, int y, int* sizeF);
int init_from_file(int** X, int** Y, int** V, Color** C, int* sizeF, int* sizeA, char* filename);

int find_elem(int* X, int* Y, int* V, int x, int y, int sizeF);
Color get_color(int* X, int* Y, int* V, Color* C, int x, int y, int sizeF);
Color mix_colors(int* X, int* Y, int* V, Color* C, int x, int y, int* sizeF);

#endif
