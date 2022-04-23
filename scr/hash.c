#include "hash.h"
#include "key.h"
#include "lck.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Alloue une cellule de la table de hachage, et initialise ses champs en mettant la valeur à zéro.*/
HashCell *create_hashcell(Key *key) {
    HashCell *hc = (HashCell *) malloc(sizeof(HashCell));
    if (!hc) exit(3);
    hc->key = key;
    hc->val = 0;
    return hc;
}

/* Retourne la position d'un élément dans la table de hachage.*/
int hash_function(Key *key, int size) {
    if (!key) exit(5);
    return (key->n * key->val) % size;
}

/*cherche dans la table t s’il existe un élément dont la clé publique est key, en sachant que les collisions sont gérées
par probing linéaire. Si l’élément a été trouvé, la fonction retourne sa position dans la table, sinon la fonction
retourne la position où il aurait dû être.*/
int find_position(HashTable *t, Key *key) {
    if (!key || !t) return -1;
    int posKey = hash_function(key, t->size), pos = posKey;
    while (t->tab[pos]) {
        if (compare_key(t->tab[pos]->key, key)) break;
        pos = (pos + 1) % (t->size);
        if (pos == posKey) return -1;
    }
    // printf("find!%d\n", pos);
    return pos;
}

/*Créer et initialiser  une table de  hachage */
HashCell **init_tab_hashCell(int size) {
    HashCell **tab = (HashCell **) malloc(sizeof(HashCell *) * size);
    if (!tab) exit(3);
    for (int i = 0; i < size; i++) {
        tab[i] = NULL;
    }
    return tab;
}

/*Cree et initialise une table de hachage de taille size contenant une cellule pour chaque cle de la liste chaınee
keys.*/
HashTable *create_hashtable(CellKey *keys, int size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (!ht) exit(3);
    ht->size = size;
    ht->tab = init_tab_hashCell(size);
    int pos, nbError = 0;
    while (keys) {
        assert(keys->data);
        if ((pos = find_position(ht, keys->data)) != -1) {
            ht->tab[pos] = create_hashcell(keys->data);
        } else {
            ++nbError;
        }
        keys = keys->next;
    }
    printf("position not found: %d(%.2f%%)\n", nbError, (double) nbError / size);
    return ht;
}

/*Supprime une cellule de la table de hachage.*/
void delete_hashcell(HashCell *t) {
    if (!t) return;
    free(t);
}

/*Supprime une table de hachage.*/
void delete_hashtable(HashTable *t) {
    for (int i = 0; i < t->size; i++) {
        delete_hashcell(t->tab[i]);
    }
    free(t->tab);
    free(t);
}

/*Affiche une cellule de la table de hachage.*/
void print_Hashcell(HashCell *hc, int idx) {
    char *key = key_to_str(hc->key);
    printf("(%d,%d,%s)\n", idx, hc->val, key);
    free(key);
}

/*Affiche la table de hachage.*/
void print_Hashtable(HashTable *Hc) {
    int valide = 0;
    for (int i = 0; i < Hc->size; i++) {
        if (!Hc->tab[i]) continue;
        print_Hashcell(Hc->tab[i], i);
        valide++;
    }
    printf("Valeurs valides: %d(%d)\n", valide, Hc->size);
}

int vote_right(Key *vote, CellKey *candidates, HashTable *voter) {
    if ((!vote) || (!candidates)) return 0;
    while (candidates) {
        if (compare_key(vote, candidates->data)) return 0;
        candidates = candidates->next;
    }
    return find_position(voter, vote) != -1;
}

/**Si voté, retournez 1 sinon retournez 0 */
int check_if_vote(HashTable *Hv, Protected *vote) {
    int idx = find_position(Hv, vote->pKey);
    return (idx != -1) && (Hv->tab[idx]) && ((Hv->tab[idx]->val++) != 0);
}

/* Calcule le vainqueur de l’élection.*/
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
    HashTable *Hc = create_hashtable(candidates, sizeC);
    HashTable *Hv = create_hashtable(voters, sizeV);
    // print_Hashable((Hc));
    // print_Hashable((Hv));
    int pos = 0;
    Key *tmpKey;
    while (decl && decl->data) {
        Protected *vote = decl->data;
        // Test pour les droits de vote
        if (vote_right(vote->pKey, candidates, Hv) && !(check_if_vote(Hv, vote))) {
            tmpKey = str_to_key(vote->mess);
            if (tmpKey && ((pos = find_position(Hc, tmpKey)) != -1)) {
                if (Hc->tab[pos]) Hc->tab[pos]->val++;
            }
            free(tmpKey);
        }
        decl = decl->next;
    }
    int gagne = -1;
    for (int i = 1; i < sizeC; i++) {
        if (!Hc->tab[i]) continue;
        int nbVote = Hc->tab[i]->val;
        // Imprimer les statistiques
        printf("candidate: %s votes: %d(%.2f%%)\n", key_to_str_static(Hc->tab[i]->key), nbVote,
               (double) nbVote / sizeV);
        if ((gagne == -1) || (nbVote > Hc->tab[gagne]->val)) {
            gagne = i;
        }
    }
    Key *key = Hc->tab[gagne]->key;
    if (gagne == -1) return NULL;
    delete_hashtable(Hc);
    delete_hashtable(Hv);
    return key;
}