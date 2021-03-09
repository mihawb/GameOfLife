#include <stdio.h>
#include <stdlib.h>
#include "crs.h"

int main (int argc, char **argv)
{
    CRSt testMatrix;
    initCRSFromFile(argv[1], testMatrix);
    return 0;
}