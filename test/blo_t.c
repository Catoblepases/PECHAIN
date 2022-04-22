#include <stdio.h>
#include <stdlib.h>

#include "params.h"
#include "scr/blo_t.h"
#define NB_BLOCKS 10
#define TEST_NB_KEYS 20
#define TEST_NB_CANDIDATS 2

// fichier particulier car les tests sont hard-coded ici pour des raisons pratique
// Ce main sert juste a verifier l'implementation de l'arbre et pas autres choses
// Les tests dynamiques sont l'objet de l'exercice suivant

void print_clean_tree(CellTree *ct, int max_height) {
    if (ct == NULL) return;

    CellTree *firstBro, *firstChild;
    firstBro = ct->nextBro;
    firstChild = ct->firstChild;

    // affichage de la cellule courant
    for (int i = max_height; i > ct->height; i--) {
        printf("\t");
    }
    print_node(ct);

    // appel recursif sur le premier frere et le premier fils
    print_clean_tree(firstChild, max_height);
    print_clean_tree(firstBro, max_height);

    return;
}

int main(void) {
    printf("----------START CREATION BLOCKS----------\n");

    // creation d'un tableau de blocs
    Block **tab_block = (Block **) malloc(sizeof(Block *) * NB_BLOCKS);

    for (int i = 0; i < NB_BLOCKS; i++) {
        tab_block[i] = NULL;
    }

    // generations de blocks aleatoire
    for (int i = 0; i < NB_BLOCKS; i++) {
        generate_random_data(TEST_NB_KEYS, TEST_NB_CANDIDATS);
        tab_block[i] = read_block(FILE_DECLARATIONS);
        printf("%s\n", block_to_str(tab_block[i]));
    }

    printf("----------FIN CREATION BLOCKS----------\n\n\n");
    printf("----------START CREATION NODE----------\n");

    // Creation d'un tableau de noeud
    CellTree **tab_node = (CellTree **) malloc(sizeof(CellTree *) * NB_BLOCKS);
    for (int i = 0; i < NB_BLOCKS; i++) {
        tab_node[i] = create_node(tab_block[i]);
    }
    printf("test\n");

    for (int i = 0; i < NB_BLOCKS; i++) {
        printf("tab_node[%d] = ", i);
        print_node(tab_node[i]);
    }

    printf("----------END CREATION NODE----------\n\n\n");
    printf("----------START TEST ADD CHILD----------\n");

    add_child(tab_node[0], tab_node[1]);
    add_child(tab_node[1], tab_node[2]);
    add_child(tab_node[2], tab_node[3]);
    add_child(tab_node[2], tab_node[4]);
    add_child(tab_node[0], tab_node[5]);
    add_child(tab_node[5], tab_node[6]);
    add_child(tab_node[6], tab_node[7]);
    add_child(tab_node[7], tab_node[8]);
    add_child(tab_node[8], tab_node[9]);

    print_clean_tree(tab_node[0], tab_node[0]->height);

    printf("----------END TEST ADD CHILD----------\n\n\n");
    printf("----------START TEST HIGHEST_CHILD LAST_NODE----------\n");

    printf("RACINE: \n");
    print_node(tab_node[0]);

    CellTree *high_child = highest_child(tab_node[0]);
    printf("PLUS GRAND FILS DE LA RACINE:\n");
    print_node(high_child);
    printf("LAST NODE:\n");
    CellTree *last = last_node(tab_node[0]);
    print_node(last);

    printf("----------END TEST HIGHEST_CHILD LAST_NODE----------\n\n\n");
    printf("----------START CLEANNING----------\n");

    delete_tree(tab_node[0]);
    free(tab_node);
    free(tab_block);

    // ces fichiers ne sont la que pour les tests statique de cette exo on les suppriment donc après
    remove(FILE_TEST_DECLARATIONS);
    remove(FILE_TEST_KEYS);
    remove(FILE_TEST_CANDIDATES);

    printf("----------END CLEANNING----------\n\n\n");

    return 0;
}
