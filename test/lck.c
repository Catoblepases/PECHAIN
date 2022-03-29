#include "scr/lck.h"
#include "scr/key.h"
#include <stdio.h>
#include <stdlib.h>
#define FILENAME "keys.txt"

int test_file() {
    FILE *f = fopen(FILENAME, "r");
    if (f == NULL) {
        printf("warnning!\n");
        return -1;
    }
    char buf[100];
    printf("running!\n");
    int n = 0;
    while (fgets(buf, 100, f)) {
        n++;
    }
    printf("%s with %d liines\n", FILENAME, n);
    fclose(f);
    return 0;
}

int main(int argc, char const *argv[]) {
    if (!test_file()) exit(EXIT_FAILURE);
    CellKey *LCK = read_public_keys(FILENAME);
    print_list_keys(LCK);
    delete_list_key(LCK);
    return 0;
}