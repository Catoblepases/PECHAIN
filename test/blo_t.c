#include <stdio.h>
#include <stdlib.h>

#include "scr/blo_t.h"
#include "scr/utility.h"

int main(void) {
    // Générer des volontaires
    print_with_sepatator("create author");
    Key *author = (Key *) malloc(sizeof(Key));
    Key *sKey = (Key *) malloc(sizeof(Key));
    init_pair_keys(author, sKey, 1 << LOW_SIZE, 1 << UP_SIZE);
    // creation d'un tableau de blocs
    CellTree **tab_node = (CellTree **) malloc(sizeof(CellTree *) * NB_BLOCKS);
    print_with_sepatator("create_node");
    for (int i = 0; i < NB_BLOCKS; i++) {
        tab_node[i] = create_node(create_random_block(author));
    }
    for (int i = 0; i < NB_BLOCKS; i++) {
        printf("tab_node[%d] = ", i);
        print_node(tab_node[i]);
    }
    // test des fontions and create un arbre
    print_with_sepatator("add_child");
    for (int i = 0; i < NB_BLOCKS - 2; i++) {
        add_child(tab_node[i], tab_node[i + 1]);
    }
    add_child(tab_node[0], tab_node[9]);
    print_with_sepatator("print_tree");
    print_tree(tab_node[0]);
    print_with_sepatator("highest_child");
    CellTree *high_child = highest_child(tab_node[0]);
    print_node(high_child);
    print_with_sepatator("last_node");
    CellTree *last = last_node(tab_node[0]);
    print_node(last);
    print_with_sepatator("delete_tree and delete_node");
    delete_tree(tab_node[0]);
    free(tab_node);
    free(sKey);
    free(author);
    return 0;
}
