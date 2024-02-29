/* Elijah Paulman */

/* 
    Prototype 2 tests opening and closing a file.
*/
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: insufficient args - no filename given\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("ERROR: Unable to open %s for reading.\n", filename);
        return 2;
    } else {
        printf("DIAGNOSTIC: Successfully opened %s for reading.\n", filename);
        fclose(file);
        printf("DIAGNOSTIC: Input file closed.\n");
    }

    return 0;
}