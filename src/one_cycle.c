#include "one_cycle.h"
#include "list.h"
#include <stdio.h>
#include "sparse_matrix.h"

//przechodzimy po wszystkich wierszach i kolumanach i dodajemy do dwóch list komórki do usunięcia i komórki do dodania

void cycle(int** X, int** Y, int** V, Color** C, int *sizeF,int *sizeA, int rows, int columns){
    list_t elem_to_add = NULL;
    list_t elem_to_del = NULL;
    for(int i=0;i<rows;i++){
        for(int j=0;j<columns;j++){
            if(find_elem(*X,*Y,*V,i,j,*sizeF) == 0 && count_alive(*X,*Y,*V,i,j, sizeF) == 3)
                elem_to_add = add_elem(elem_to_add,i,j,1);
            if(find_elem(*X,*Y,*V,i,j,*sizeF) >= 1 && count_alive(*X,*Y,*V,i,j, sizeF) != 3 && count_alive(*X,*Y,*V,i,j, sizeF) != 2)
                elem_to_del = add_elem(elem_to_del,i,j,0);
        }
    }

//dodajemy i odejmujemy komórki
    while(elem_to_add != NULL){
        Color c = mix_colors(*X,*Y,*V,*C, elem_to_add->x,elem_to_add->y,sizeF);
        add_cell(X,Y,V,C,elem_to_add->x,elem_to_add->y,elem_to_add->v,c, sizeF,sizeA);
        elem_to_add = elem_to_add->next;
    }
    while(elem_to_del != NULL){
        remove_cell(X,Y,V,C,elem_to_del->x,elem_to_del->y,sizeF,sizeA);
        elem_to_del = elem_to_del->next;
    }

    free_list(elem_to_add);
    free_list(elem_to_del);
}
