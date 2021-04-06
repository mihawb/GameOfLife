#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "sparse_matrix.h"
#include "output_to_file.h"
#include "one_cycle.h"

#define REALLOC_SIZE 8

int main(int argc, char *argv[]) {

    int opt;
    char* filename;
    int n_cykli = 10;

    while ((opt = getopt (argc, argv, "f:n:")) != -1) {
        switch (opt) {
            case 'f':
                filename = optarg;
                break;
            case 'n':
                n_cykli = atoi(optarg);
                break;
            default:
                fprintf (stderr, "%s: unexpected error occured\n", argv[0]);
                exit (EXIT_FAILURE);
        }
    }
    
    FILE* in = fopen(filename,"r");
    if(in == NULL){
	    printf("Nie udało się odczytać pliku");
	    return EXIT_FAILURE;
    }

    int rows, columns;
    fscanf(in,"%d %d", &rows, &columns);

    int cycle_number = 0;                            
    int sizeFilled = 0;                           
    int sizeAllocated = REALLOC_SIZE;
    int *X = (int*) malloc(sizeof(int) * REALLOC_SIZE);
    int *Y = (int*) malloc(sizeof(int) * REALLOC_SIZE);
    int *V = (int*) malloc(sizeof(int) * REALLOC_SIZE);
    Color *C = (Color*) malloc(sizeof(Color) * REALLOC_SIZE);

    init_from_file(&X, &Y, &V, &C, &sizeFilled, &sizeAllocated, filename);

    for(int i=0;i<n_cykli;i++){
        output_to_png(X,Y,V,C, sizeFilled, rows,columns,cycle_number); 
        output_to_txt(X,Y,V,sizeFilled,rows, columns,cycle_number);
        cycle(&X, &Y, &V, &C, &sizeFilled, &sizeAllocated, rows, columns);
        dealloc_if_needed(&X, &Y, &V, &C, &sizeFilled, &sizeAllocated);
        cycle_number++;
    }

    return 0;
}

