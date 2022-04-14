#include "scr/sml.h"
#include "scr/blo_t.h"
#include "scr/key.h"
#include "scr/lck.h"
#include "scr/lcp.h"
#include "scr/pro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    int d = 4;
    Key *author = (Key *) malloc(sizeof(Key));
    Key *sKey = (Key *) malloc(sizeof(Key));
    init_pair_keys(author, sKey, 1 << 3, 1 << 8);
    int sizeV = 1000;
    int sizeC = 5;

    generate_random_data(sizeV, sizeC);
    CellProtected *cellp = read_protected("declarations.txt");
    CellKey *cellk = read_public_keys("keys.txt");

    FILE *f = fopen("declarations.txt", "r");
    char buf[1 < 16];
    int idx = 0;
    CellTree *tree = NULL;
    char *fileName;
    const char fn = "block";
    while (fgets(buf, 1 << 16, f) > 0) {
        Protected *pr = str_to_protected(buf);
        submit_vote(pr);
        while (idx++ % 10 == 9) {
            create_block(tree, author, d);
            fileName = (char *) malloc(sizeof(char) * (1 << 8));
            sprintf(fileName, "%s%d", fn, idx / 2);
            add_block(d, fileName);
            free(fileName);
        }
    }
    CellTree *tr = read_tree();
    print_tree(tr);
    compute_winner_BT(tr, cellp, cellk, sizeC, sizeV);
    delete_tree(tr);
    delete_list_key(cellk);
    delete_list_protected(cellp);
    return 0;
}
