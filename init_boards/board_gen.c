#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>

int main (int argc, char **argv)
{
    srand(time(NULL));
    int opt;
    char *output_file;
    int width = 10;
    int height = 10;
    int rodziny = 1;
    
    while ((opt = getopt (argc, argv, "f:w:h:r:")) != -1) {
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
            case 'r':
                rodziny = atoi(optarg);
                break;
            default:
                fprintf (stderr, "%s: unexpected error occured\n", argv[0]);
                exit (EXIT_FAILURE);
        }
    }

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

    for (int i = 0; i < width * height; i++) {
        fprintf(out, "%d ", board[i]);
        if ((i + 1) % width == 0) {
            fprintf(out, "\n");
        }
    }

    fclose(out);
    return 0;
}
