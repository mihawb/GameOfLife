#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

#define REALLOC_SIZE 128


//polecam uruchomic przez pipe do jakiegos txt
int main(int argc, char *argv[]) {
	
	int sizeFilled = 0;                          //fun fact: mozna zaalokowac pamiec na 0 bajtow, kocham C
    int sizeAllocated = REALLOC_SIZE;
	int *X = malloc (sizeof (int) * REALLOC_SIZE);  //wspolrzedne x komorek zywych lub przeszkod
	int *Y = malloc (sizeof (int) * REALLOC_SIZE);  //wspolrzedne y komorek zywych lub przeszkod
    int *V = malloc (sizeof (int) * REALLOC_SIZE);  //wartosci komorek (determinuje czy mamy do czynienia z przeszkoda czy zywa komorka)

    init_from_file(&X, &Y, &V, &sizeFilled, &sizeAllocated, "../init_boards/ut_1000_1000_1.txt");
    
    for (int i = 0; i < sizeFilled; i += 3000) { // zamienic na i++ jak chce sie dokladnie przesledzic ale mi nie zalezy
        printf("%d %d %d\n", X[i], Y[i], V[i]);
    }
    
    int i = 0;
    while (sizeFilled > 0) {
        remove_cell(&X, &Y, &V, X[0], Y[0], &sizeFilled, &sizeAllocated);
        printf("%d: %d\n", i++, sizeFilled);
    }

    free(Y);
    free(X);
    free(V);

	return 0;
}