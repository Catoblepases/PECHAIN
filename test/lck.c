#include "scr/lck.h"
#include "scr/key.h"
#include "scr/utility.h"
#include <stdio.h>
#include <stdlib.h>


/**Tester si le fichier existe et compter le nombre de lignes valides*/
int test_file() {
    FILE *f = fopen(FILE_KEYS, "r");
    if (f == NULL) {
        printf("warnning!\n");
        return 0;
    }
    char buf[100];
    printf("running!\n");
    int n = 0;
    while (fgets(buf, 100, f)) {
        n++;
    }
    printf("%s with %d liines\n", FILE_KEYS, n);
    fclose(f);
    return 1;
}

int main(int argc, char const *argv[]) {
    if (!test_file()) exit(EXIT_FAILURE);
    CellKey *LCK = read_public_keys(FILE_KEYS);
    print_list_keys(LCK);
    delete_list_key(LCK);
    return 0;
}