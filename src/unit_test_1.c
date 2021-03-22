#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"

#define REALLOC_SIZE 10

int main(int argc, char *argv[]) {
	
	int size = 0;                           //fun fact: mozna zaalokowac pamiec na 0 bajtow, kocham C
	int *X = malloc (sizeof (int) * REALLOC_SIZE);  //wspolzedne x komorek zywych lub przeszkod
	int *Y = malloc (sizeof (int) * REALLOC_SIZE);  //wspolzedne y komorek zywych lub przeszkod
    int *V = malloc (sizeof (int) * REALLOC_SIZE);  //wartosci komorek (determinuje czy mamy do czynienia z przeszkoda czy zywa komorka)

    size = init_from_file(X, Y, V, size, "../init_boards/ut_1.txt");
	
    printf("    X Y V\n");
	for (int i = 0; i < size; i++) {
        printf("K%d: %d %d %d\n", i+1, X[i], Y[i], V[i]);
    }

    printf("Usuwamy komorke K6 (5, 0) i K2 (1, 1)\n");
    size = remove_cell(X, Y, V, 5, 0, size);
    size = remove_cell(X, Y, V, 1, 1, size);

    printf("    X Y V\n");
	for (int i = 0; i < size; i++) {
        printf("K%d: %d %d %d\n", i+1, X[i], Y[i], V[i]);
    }

    int sasiedztwoK3 = count_alive(X, Y, V, 4, 5, size);
    int sasiedztwoK4 = count_alive(X, Y, V, 4, 6, size); // tak zrobilem zeby bylo czytelniej niz to printfa wrzucic xd
    printf("Liczba zywych komorek w sasiedztwie K3: %d, oraz K4: %d\n", sasiedztwoK3, sasiedztwoK4);

	return 0;
}
