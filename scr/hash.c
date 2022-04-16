#include "hash.h"
#include "key.h"
#include "lck.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashCell *create_hashcell(Key *key) {
    HashCell *hc = (HashCell *) malloc(sizeof(HashCell));
    if (!hc) exit(3);
    hc->key = key;
    hc->val = 0;
    return hc;
}

int hash_function(Key *key, int size) {
    char *str = key_to_str(key);
    int hash = 1;
    for (int i = 0; i < strlen(str); i++) {
        hash *= (int) str[i];
    }
    free(str);
    if (hash < 0) hash *= -1;
    return hash % size;
}

int find_position(HashTable *t, Key *key) {
    if (!key || !t) return -1;
    int posKey = hash_function(key, t->size), pos = posKey;
    // printf("hash: %d %s\n", posKey, key_to_str(key));
    while (t->tab[pos]) {
        if (compare_key(t->tab[pos]->key, key)) break;
        pos = (pos + 1) % t->size;
        if (pos == posKey) return -1;
    }
    return pos;
}

/*Cree et initialise une table de hachage de taille size contenant une cellule pour chaque cle de la liste chaınee
keys.*/
HashTable *create_hashtable(CellKey *keys, int size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (!ht) exit(3);
    ht->size = size;
    ht->tab = (HashCell **) malloc(sizeof(HashCell *) * size);
    if (!ht->tab) exit(3);
    for (int i = 0; i < size; i++) {
        ht->tab[i] = NULL;
    }
    int pos, nbError = 0;
    while (keys) {
        if ((pos = find_position(ht, keys->data)) == -1) continue;
        // if ((pos = find_position(ht, keys->data)) == -1 && (++nbError)) continue;
        ht->tab[pos] = create_hashcell(keys->data);
        // printf("%d %s\n", pos, key_to_str(ht->tab[pos]->key));
        keys = keys->next;
    }

    HashCell *t = ht->tab;
    printf("%d ", ht->size);
    for (int i = 0; i < ht->size; i++) {
        printf("%s ", key_to_str(t->key));
    }
    printf("\n");
    printf("position not found: \n");
    return ht;
}

void delete_hashtable(HashTable *t) {
    for (int i = 0; i < t->size; i++) {
        if (t->tab[i]) free(t->tab[i]->key);
    }
    free(t);
}

int vote_right(Key *vote, CellKey *candidates) {
    while (candidates) {
        if (compare_key(vote, candidates->data)) return 0;
        candidates = candidates->next;
    }
    return 1;
}

Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
    // verify_for_list_protected(&decl);
    HashTable *Hc = create_hashtable(candidates, sizeC);
    HashTable *Hv = create_hashtable(voters, sizeV);
    int pos = 0;
    Key *tmpKey;
    while (decl) {
        Protected *vote = decl->data;
        // Test pour les droits de vote
        if (!vote_right(vote, candidates)) continue;
        // Vérifier si les électeurs ont voté
        if (Hv->tab[find_position(Hv, vote->pKey)]->val++ != 0) continue;
        tmpKey = str_to_key(vote->mess);
        if (tmpKey && ((pos = find_position(Hc, tmpKey)) != -1)) {
            Hc->tab[pos]->val++;
        }
        free(tmpKey);
    }
    int gagne = 0;
    for (int i = 1; i < sizeC; i++) {
        if (Hc->tab[i]->val > Hc->tab[gagne]->val) gagne = i;
    }
    return Hc->tab[gagne]->key;
}