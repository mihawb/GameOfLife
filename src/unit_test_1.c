#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

int main(int argc, char *argv[]) {
	
	int size = 0;                           //fun fact: mozna zaalokowac pamiec na 0 bajtow, kocham C
	int *X = malloc (sizeof (int) * size);  //wspolzedne x komorek zywych lub przeszkod
	int *Y = malloc (sizeof (int) * size);  //wspolzedne y komorek zywych lub przeszkod
    int *V = malloc (sizeof (int) * size);  //wartosci komorek (determinuje czy mamy do czynienia z przeszkoda czy zywa komorka)

    size = init_from_file(X, Y, V, size, "../init_boards/ut_1.txt");
    printf("size: %d\n", size);
	
    printf("    X Y V\n");
	for (int i = 0; i < size; i++) {
        printf("K%d: %d %d %d\n", i+1, X[i], Y[i], V[i]);
    }

	return 0;
}
