#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int add_cell(int *X, int *Y, int *V, int x, int y, int v, int size){  //parametry funkcji to kolejno wskazniki do X,Y i V, wspolrzedne x i y komorki, aktualny rozmiar tablicy X i Y

	X = realloc(X, size + 1);   //zwieksza rozm X
	X[size] = x;                //dodaje nowa wartosc na koncu

	Y = realloc(Y, size + 1);
	Y[size] = y;

    V = realloc(V, size + 1);
	V[size] = v;                // przy wczytywaniu z pliku dodawane sa tez przeszkody

    return size + 1;
}

int remove_cell(int *X, int *Y, int *V, int x, int y, int size){
	
	int i;
	for(i=0; i<size; i++)
		if(X[i]==x && Y[i]==y)
			break;                                  //znajduje indeks danej komorki
	
	memmove(X+i, X+i+1, (size - i)*sizeof(int));    //przesuwa wszystko za dana komorka o 1 w lewo, komorka do usuniecia zostaje nadpisana
	X = realloc(X, (size-1)*sizeof(int));               //zeby zwolnic ostatnie miejsce
	
	memmove(Y+i, Y+i+1, (size - i)*sizeof(int));
	Y = realloc(Y, (size-1)*sizeof(int));

    memmove(V+i, V+i+1, (size - i)*sizeof(int));
	V = realloc(V, (size-1)*sizeof(int));

    return size - 1;
}

int count_alive(int *X, int *Y, int *V, int x, int y, int size){
	
	int i, j, alive = 0;
	
	for (i = x - 1; i <= x + 1; i++) {                          //idzie po x w sasiedztwie danej komorki
		for (j = 0; j < size; j++) {
			if (X[j] == i){                                     //sprawdza czy w X jest parametr x komorki
				if (Y[j] >= y-1 && Y[j] <= y+1){                //jesli tak to czy w Y jest parametr y komorki
					if ((X[j] != x || Y[j] != y) && V[j] > 0)   //jesli tak i to nie jest ta komorka ktorej sasiedztwo sprawdzamy oraz czy nie jest to przeszkoda
						alive++;                                //to zwieksza sie licznik zywych komorek
				}
			}
		}
	}
	
	return alive;
}

int init_from_file(int *X, int *Y, int *V, int size, char *filename) { //przypisujemy potem size=init-from_file()
    int sX, sY, val;
    FILE *in = fopen(filename, "r");
    if (in == NULL)
        return -1; //potem sprawdzamy czy size>0, wpp w mainie radzimy sobie z bledem wczytania pliku

    fscanf(in, "%d %d\n", &sX, &sY);

    for (int i = 0; i < sX; i++) {
        for (int j = 0; j < sY; j++) {
            fscanf(in, "%d", &val);
            if (val != 0) {
                printf("%d %d %d\n", i, j, val);
                size = add_cell(X, Y, V, i, j, val, size);
            }
        }
    }
    return size;
}