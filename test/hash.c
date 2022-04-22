#include "scr/hash.h"
#include "scr/utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    srand(time(NULL));

    // generate_random_data(NB_KEYS, NB_CANDIDATS);
    print_with_sepatator("read_protected");
    CellKey *candidates = read_public_keys(FILE_CANDIDATES);
    CellKey *voters = read_public_keys(FILE_KEYS);
    CellProtected *declarations = read_protected(FILE_DECLARATIONS);
    print_with_sepatator("verify_for_list_protected");
    verify_for_list_protected(&declarations);
    print_with_sepatator("create_hashtable");
    HashTable *ht = create_hashtable(voters, NB_KEYS);
    print_Hashtable(ht);
    delete_hashtable(ht);
    print_with_sepatator("compute_winner");
    Key *winner_key = compute_winner(declarations, candidates, voters, NB_CANDIDATS, NB_KEYS);
    printf("%s\n", key_to_str(winner_key));

    delete_list_protected(declarations);
    delete_list_key(candidates);
    delete_list_key(voters);
    return 0;
}