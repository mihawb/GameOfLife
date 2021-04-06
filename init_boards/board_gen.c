// gcc board_gen.c -o testgen.out
// testgen.out -f test_out.txt -w 10 -h 9 -g -l -o -s

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int main (int argc, char **argv) // ./a.out -f output_file -w w -h h -gun(glider gun) -osc(krokodyl lub fontanna) -lwss -stat
{
    srand(time(NULL));
    int opt;
    char *output_file;
    int width;
    int height;
    int guns = 0;
    int gliders = 0;
    int oscillators = 0;
    int statics = 0;
    int rodziny = 1;

    // jak bedzie mi sie kiedys chcialo to dodam zeby program generowal
    // losowo rozmieszczone struktury (glider guny, dakoty, oscylatory itp)
    // flagi dodate tak przyszlosciowo 
    while ((opt = getopt (argc, argv, "f:w:h:g:o:l:s:r:")) != -1) { //file, width, height, gun, osCillator, LWSS, static, liczba rodzin
        switch (opt) {
            case 'f':
                output_file = optarg;
                break;
            case 'w':
                width = atoi(optarg);
                break;
            case 'h':
                height = atoi(optarg);
                break;
            case 'g':
                guns = 1;
                break;
            case 'o':
                oscillators = 1;
                break;
            case 'l':
                gliders = 1;
                break;
            case 's':
                statics = 1;
                break;
            case 'r':
                rodziny = atoi(optarg);
                break;
            default:
                fprintf (stderr, "%s: unexpected error occured\n", argv[0]);
                exit (EXIT_FAILURE);
        }
    }
/*
    printf("DEBUG: file=%s, w=%d, h=%d, guns=%d, osc=%d, gliders=%d, statics=%d\n",
                   output_file, width, height, guns, oscillators, gliders, statics);
*/

    FILE *out = fopen(output_file, "w");
    if (out == NULL) {
        fprintf(stderr, "%s cannot create return file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int *board = calloc(width * height, sizeof (int));

/*
    for (int i = 0; i < width * height; i++) {
        board[i] = 1; // do testow gdzie potrzeba calkowicie zapelnionej planszy
    }
*/

    for (int i = 0; i < (width * height) / 10; i++) { // 10% planszy to beda losowo generowane zywe komorki
        board[rand() % (width * height)] = rand() % rodziny + 1;
    }

    fprintf(out, "%d %d\n", width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(out, "%d ", board[i*height + j]);
        }
        fprintf(out, "\n");
    }

    fclose(out);
    return 0;
}