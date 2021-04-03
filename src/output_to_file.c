#include "output_to_file.h"
#include "sparse_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void output_to_txt(int* X, int* Y, int* V,int sizeF, int rows, int columns,int cycle_number){

    char number[13];
    sprintf(number, "%d", cycle_number);
    char *dest = "../outputs/output";
    char *exte = ".txt";
    char *outp = (char*) malloc(1 + strlen(dest) + strlen(exte) + strlen(number));
    strcpy(outp,dest);
    strcat(outp,number);
    strcat(outp,exte);
   

    FILE *out = fopen(outp, "w");

    fprintf(out,"%d %d\n",rows,columns);
    for(int i=0;i<rows;i++){
        for(int j=0 ; j<columns ; j++){
            fprintf(out, "%d ", find_elem(X,Y,V,i,j,sizeF));
        }
        fprintf(out,"\n");
    }
    fclose(out);

}
