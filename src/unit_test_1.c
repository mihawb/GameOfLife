#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"
#include "output_to_file.h"
#include "one_cycle.h"

#define REALLOC_SIZE 3

int main(int argc, char *argv[]) {
    //argv[1] = ile cykli chcemy przeprowadzić     
    int n_cykli = argc > 1 ? atoi(argv[1]) : 10;
    char *filename = "../init_boards/ut_10_10.txt";
    FILE* in = fopen(filename,"r");
    if(in == NULL){
	printf("Nie udało się odczytać pliku");
	return EXIT_FAILURE;
    }

    int rows, columns;
    fscanf(in,"%d %d", &rows, &columns);

    int cycle_number = 0;                           //licznik cykli -> pomaga tworzyć plik o takiej nazwie 
    int sizeFilled = 0;                           //fun fact: mozna zaalokowac pamiec na 0 bajtow, kocham C
    int sizeAllocated = REALLOC_SIZE;
    int *X = (int*) malloc(sizeof(int) * REALLOC_SIZE);  //wspolzedne x komorek zywych lub przeszkod
    int *Y = (int*) malloc(sizeof(int) * REALLOC_SIZE);  //wspolzedne y komorek zywych lub przeszkod
    int *V = (int*) malloc(sizeof(int) * REALLOC_SIZE);  //wartosci komorek (determinuje czy mamy do czynienia z przeszkoda czy zywa komorka)

    init_from_file(&X, &Y, &V, &sizeFilled, &sizeAllocated, filename); //jak w jakiejs funkcji jest realloc albo cos takiego to trzeba tak przekazywac

    for(int i=0;i<n_cykli;i++){
	output_to_png(X,Y,V, sizeFilled, rows,columns,cycle_number); 
   	output_to_txt(X,Y,V, sizeFilled, rows,columns,cycle_number);
	cycle(&X, &Y, &V, &sizeFilled, &sizeAllocated, rows, columns);
	cycle_number++;
    }

    return 0;
}

