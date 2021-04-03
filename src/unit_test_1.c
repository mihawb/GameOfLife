#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"
#include "output_to_file.h"
#include "one_cycle.h"

#define REALLOC_SIZE 3

int main(int argc, char *argv[]) {
    char *filename = "../init_boards/ut_1.txt";
    FILE* in = fopen(filename,"r");
    int rows, columns;
    fscanf(in,"%d %d", &rows, &columns);

    int cycle_number = 0;
    int sizeFilled = 0;                           //fun fact: mozna zaalokowac pamiec na 0 bajtow, kocham C
    int sizeAllocated = REALLOC_SIZE;
    int *X = (int*) malloc(sizeof(int) * REALLOC_SIZE);  //wspolzedne x komorek zywych lub przeszkod
    int *Y = (int*) malloc(sizeof(int) * REALLOC_SIZE);  //wspolzedne y komorek zywych lub przeszkod
    int *V = (int*) malloc(sizeof(int) * REALLOC_SIZE);  //wartosci komorek (determinuje czy mamy do czynienia z przeszkoda czy zywa komorka)

    init_from_file(&X, &Y, &V, &sizeFilled, &sizeAllocated, filename); //jak w jakiejs funkcji jest realloc albo cos takiego to trzeba tak przekazywac
 
    //przeprowadzamy 10 cylki i tworzymy dla kazdego nowy plik outputX.txt w folderze outputs
    for(int i=0;i<10;i++) {
        cycle(&X,&Y,&V,&sizeFilled,&sizeAllocated,rows,columns);
        output_to_txt(X,Y,V, sizeFilled, rows,columns,cycle_number);
        cycle_number++;
    }


    return 0;
}

