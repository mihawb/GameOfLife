#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define REALLOC_SIZE 4
extern int max_x, max_y;

void add_cell(int** X, int** Y, int** V, int x, int y, int v, int* sizeF, int* sizeA) {  //parametry funkcji to kolejno wskazniki do X,Y i V, wspolrzedne x i y komorki, aktualny rozmiar tablicy X i Y

    if (*sizeA < (*sizeF) + 1) {
        void* temp;
        temp = realloc(*X, sizeof(int) * ((*sizeF) + REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *X = temp;

        temp = realloc(*Y, sizeof(int) * ((*sizeF) + REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *Y = temp;

        temp = realloc(*V, sizeof(int) * ((*sizeF) + REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *V = temp;

        (*sizeA) += REALLOC_SIZE;
    }

    (*X)[*sizeF] = x;                //dodaje nowa wartosc na koncu
    (*Y)[*sizeF] = y;
    (*V)[*sizeF] = v;                // przy wczytywaniu z pliku dodawane sa tez przeszkody

    (*sizeF)++;
}

void remove_cell(int** X, int** Y, int** V, int x, int y, int* sizeF, int* sizeA) {

    int i;
    for (i = 0; i < *sizeF; i++) {
        if ((*X)[i] == x && (*Y)[i] == y)
            break;                         //znajduje indeks danej komorki
    }

    memmove(*X + i, *X + i + 1, ((*sizeF) - i) * sizeof(int));    //przesuwa wszystko za dana komorka o 1 w lewo, komorka do usuniecia zostaje nadpisana
    memmove(*Y + i, *Y + i + 1, ((*sizeF) - i) * sizeof(int));
    memmove(*V + i, *V + i + 1, ((*sizeF) - i) * sizeof(int));

    (*sizeF)--;
}

void dealloc_if_needed(int** X, int** Y, int** V, int* sizeF, int* sizeA) {
    int n = (int)((*sizeF) / REALLOC_SIZE); // ilosc pelnych jednostek alokacyjnych
    void* temp;
    if (n * REALLOC_SIZE == (*sizeF)) { // czyli jesli nie bedzie zadnych czesciowo zapelnionych jednostek
        temp = realloc(*X, sizeof(int) * (n * REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *X = temp;

        temp = realloc(*Y, sizeof(int) * (n * REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *Y = temp;

        temp = realloc(*V, sizeof(int) * (n * REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *V = temp;

        *sizeA = n * REALLOC_SIZE;
    } else {
        temp = realloc(*X, sizeof(int) * ((n+1) * REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *X = temp;

        temp = realloc(*Y, sizeof(int) * ((n+1) * REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *Y = temp;

        temp = realloc(*V, sizeof(int) * ((n+1) * REALLOC_SIZE));
        if (temp == NULL) {
            fprintf(stderr, "ERROR in realloc, aborting\n");
            exit(EXIT_FAILURE);
        } else
            *V = temp;

        *sizeA = (n+1) * REALLOC_SIZE;
    }
}

int count_alive(int* X, int* Y, int* V, int x, int y, int* sizeF) {

    int i, j, alive = 0;

    for (i = x - 1; i <= x + 1; i++) {                          //idzie po x w sasiedztwie danej komorki
        for (j = 0; j < *sizeF; j++) {
            if (X[j] == i) {                                     //sprawdza czy w X jest parametr x komorki
                if (Y[j] >= y - 1 && Y[j] <= y + 1) {                //jesli tak to czy w Y jest parametr y komorki
                    if ((X[j] != x || Y[j] != y) && V[j] > 0)   //jesli tak i to nie jest ta komorka ktorej sasiedztwo sprawdzamy oraz czy nie jest to przeszkoda
                        alive++;                                //to zwieksza sie licznik zywych komorek
                }
            }
        }
    }

    if (x == 0 || x == max_x) {  //przypadek gdzie x jest skrajny
        if (x == 0)
            i = max_x;
        if (x == max_x)
            i = 0;


        for (j = 0; j < *sizeF; j++) {
            if (X[j] == i) {
                if (Y[j] >= y - 1 && Y[j] <= y + 1) {
                    if ((X[j] != x || Y[j] != y) && V[j] > 0)
                        alive++;
                }
            }
        }
    }

    if (y == 0 || y == max_y) {    //przypadek gdzie y jest skrajny
        if (y == 0) {
            for (i = x - 1; i <= x + 1; i++) {
                for (j = 0; j < *sizeF; j++) {
                    if (X[j] == i) {
                        if (Y[j] == max_y) {
                            if ((X[j] != x || Y[j] != y) && V[j] > 0)
                                alive++;
                        }
                    }
                }
            }
        }

        if (y == max_y) {
            for (i = x - 1; i <= x + 1; i++) {
                for (j = 0; j < *sizeF; j++) {
                    if (X[j] == i) {
                        if (Y[j] == 0) {
                            if ((X[j] != x || Y[j] != y) && V[j] > 0)
                                alive++;
                        }
                    }
                }
            }
        }
    }

    return alive;
}

int init_from_file(int** X, int** Y, int** V, int* sizeF, int* sizeA, char* filename) { //przypisujemy potem size=init-from_file()
    int sX, sY, val;
    FILE* in = fopen(filename, "r");
    if (in == NULL)
        return -1; //potem sprawdzamy czy size>0, wpp w mainie radzimy sobie z bledem wczytania pliku

    fscanf(in, "%d %d\n", &sX, &sY);

    for (int i = 0; i < sX; i++) {
        for (int j = 0; j < sY; j++) {
            fscanf(in, "%d", &val);
            if (val != 0) {
                //printf("%d %d %d\n", i, j, val); //debug
                add_cell(X, Y, V, i, j, val, sizeF, sizeA);
            }
        }
    }
}


int find_elem(int* X, int* Y, int* V, int x, int y, int sizeF){
    for(int i=0;i<sizeF;i++){
        if(X[i] == x && Y[i] == y)
            return V[i];
    }
    return 0;
}
