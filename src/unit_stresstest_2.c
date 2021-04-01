#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

#define REALLOC_SIZE 1


//polecam uruchomic przez pipe do jakiegos txt
int main(int argc, char *argv[]) {
	
	int size = 0;                           //fun fact: mozna zaalokowac pamiec na 0 bajtow, kocham C
	int *X = malloc (sizeof (int) * REALLOC_SIZE);  //wspolrzedne x komorek zywych lub przeszkod
	int *Y = malloc (sizeof (int) * REALLOC_SIZE);  //wspolrzedne y komorek zywych lub przeszkod
    int *V = malloc (sizeof (int) * REALLOC_SIZE);  //wartosci komorek (determinuje czy mamy do czynienia z przeszkoda czy zywa komorka)

    size = init_from_file(&X, &Y, &V, size, "../init_boards/ut_1000_1000_1.txt");
    printf("size = %d\n", size);
    
    for (int i = 0; i < size; i += 3000) { // zamienic na i++ jak chce sie dokladnie przesledzic ale mi nie zalezy
        printf("%d %d %d\n", X[i], Y[i], V[i]);
    }

    int i = 0;
    while (size > 0) {
        size = remove_cell(&X, &Y, &V, X[0], Y[0], size);
        printf("%d: %d\n", i++, size);
    }

    free(Y);
    free(X);
    free(V);

	return 0;
}