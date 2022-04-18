#include "scr/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_KEYS "keys.txt"
#define FILE_CANDIDATES "candidates.txt"
#define FILE_DECLARATIONS "declarations.txt"
#define FILE_COMPARAISON_EXPONENTIATION "comparaison_exponentiation.txt"
#define FILE_BLOCKS "blocks.txt"
#define FILE_BLOCKS_TEST "blocks_test.txt"
#define FILE_PENDING_VOTES "pending_votes.txt"
#define DIR_BLOCK "./blockchain/"
#define NB_KEYS 200    // Nombre de personnes enregistre aux elections / declaration de vote
#define NB_CANDIDATS 4 // Nombre de candidats parmis les personnes enregistre

// EXERCICE 6
#define NB_TEST_FINDPOSITION 20

int main(void) {

    srand(time(NULL));

    // generate_random_data(NB_KEYS, NB_CANDIDATS);
    printf("----------START READ_PROTECTED----------\n");
    CellProtected *lp = read_protected(FILE_DECLARATIONS);
    printf("----------END READ_PROTECTED----------\n\n\n");

    printf("----------START PRINT_LIST_KEYS----------\n");
    print_list_protected(lp);
    printf("----------END PRINT_LIST_KEYS----------\n\n\n");

    printf("----------START verify_for_list_protected----------\n");
    // verify_for_list_protected(&lp);
    printf("----------END verify_for_list_protected----------\n\n\n");

    // A present toutes les declarations sont bien verifier

    printf("----------START TEST HASH FUNCTIONS----------\n");
    // on supprime pas les cles invalides ici pour faciliter les tests
    CellKey *lk = read_public_keys(FILE_KEYS);
    // print_list_keys(lk);
    HashTable *ht = create_hashtable(lk, NB_KEYS);

    printf("\n-----START TEST FIND POSITION-----\n");
    for (int i = 0; i < NB_TEST_FINDPOSITION; i++) {
        int random = rand() % NB_KEYS;
        CellKey *cursor = lk;
        for (int j = 0; j < random; j++) {
            if (!cursor) break;
            cursor = cursor->next;
        }
        if (cursor) {
            int pos = find_position(ht, cursor->data);
            char *key_str = key_to_str(cursor->data);
            printf("  Cle %-20sPosition %-4d\n", key_str, pos);
            free(key_str);
        }
    }
    printf("-----END TEST FIND POSITION-----\n\n\n");

    delete_hashtable(ht);
    delete_list_key(lk);
    delete_list_protected(lp);
    // free(list_decla);
    printf("----------END TEST HASH FUNCTIONS----------\n");

    printf("----------START COMPUTE WINNER TEST----------\n");
    // lc == liste candidat
    CellKey *lc = read_public_keys(FILE_CANDIDATES);
    // lv == liste votant
    CellKey *lv = read_public_keys(FILE_KEYS);
    // ld == liste declaration
    CellProtected *ld = read_protected(FILE_DECLARATIONS);

    Key *winner_key = compute_winner(ld, lc, lv, NB_CANDIDATS, NB_KEYS);

    delete_list_protected(ld);
    delete_list_key(lc);
    delete_list_key(lv);

    printf("----------END COMPUTE WINNER TEST----------\n");

    return 0;
}