#include "hash.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*Renvoie le nombre de signatures invalides et les supprime.*/
int verify_for_list_protected(CellProtected **LCP) {
    CellProtected *lcp = *LCP, *tmp;
    int nb = 0;
    // Vérifie la validité de la première déclaration signée.*/
    if (!verify(lcp->data)) {
        lcp = lcp->next;
        tmp = *LCP;
        *LCP = (*LCP)->next;
        delete_cell_protected(tmp);
        nb++;
    }
    while (lcp->next) {
        assert(lcp->next->data);
        // Vérifie la validité de la prochaine déclaration signée.
        if (!verify(lcp->next->data)) {
            tmp = lcp->next;
            lcp->next = lcp->next->next;
            delete_cell_protected(tmp);
            nb++;
        }
        lcp = lcp->next;
    }
    return nb;
}

/*Alloue une cellule de la table de hachage, et initialise ses champs en mettant la valeur à zéro.*/
HashCell *create_hashcell(Key *key) {
    HashCell *hc = (HashCell *) malloc(sizeof(HashCell));
    if (hc == NULL) {
        printf("Erreur lors de l'allocation.");
        return NULL;
    } else {
        hc->key = key;
        hc->val = 0;
        return hc;
    }
}

/*Retourne la position d’un élément dans la table de hachage.*/
int hash_function(Key *key, int size) { return (key->n) * (key->val) % size; }

/*cherche dans la table t s’il existe un élément dont la clé publique est key, en sachant que les collisions sont gérées par probing linéaire. 
Si l’élément a été trouvé, la fonction retourne sa position dans la table, sinon la fonction retourne la position où il aurait dû être.*/
int find_position(HashTable *t, Key *key) {
    int i;
    for (i = 0; i < t->size; i++) {
        if (t->tab[i] != NULL && (t->tab[i])->key == key) {
            return i;
        }
    }
    int pos = hash_function(key, t->size);
    while (t->tab[pos] != NULL) {
        pos = (pos + 1) % t->size;
    }
    return pos;
}

/*Cree et initialise une table de hachage de taille size contenant une cellule pour chaque cle de la liste chaınee
keys.*/
HashTable *create_hashtable(CellKey *keys, int size) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    int i;
    if (ht == NULL) {
        printf("Erreur lors de l'allocation.");
        return NULL;
    } else {
        ht->size = size;
        HashCell **hc = (HashCell **) malloc(sizeof(HashCell *) * size);
        if (hc == NULL) {
            printf("Erreur lors de l'allocation.");
            return NULL;
        } else {
            while (keys != NULL) {
                i = find_position(ht, keys->data);
                hc[i] = create_hashcell(keys->data);
                keys = keys->next;
            }
        }
        ht->tab = hc;
        return ht;
    }
}

/*Supprime une table de hachage.*/
void delete_hashtable(HashTable *t) {
    int i;
    for (i = 0; i < t->size; i++) {
        if (t->tab[i] != NULL) {
            free(t->tab[i]->key);
        }
    }
    free(t);
}

/* Calcule le vainqueur de l’élection.*/
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
    //Verifie la validité de message contenue dans la déclaration signée
    verify_for_list_protected(&decl);
    HashTable *Hc = create_hashtable(candidates, sizeC);
    HashTable *Hv = create_hashtable(voters, sizeV);
    int i, j, max = 0, gagne;
    while (decl != NULL) {
        for (i = 0; i < sizeV; i++) {
            //La personne qui vote a le droit de voter
            if (Hv->tab[i] != NULL && (Hv->tab[i])->key == decl->data->pKey) {
                //La personne qui vote  n'a pas deja vote
                if ((Hv->tab[i])->val == 0) {
                    (Hv->tab[i])->val++;
                    Key *k = str_to_key(decl->data->mess);
                    for (j = 0; j < sizeC; j++) {
                        // La personne sur qui porte le vote est bien un candidat de l'election
                        if ((Hc->tab[j] != NULL) && ((Hc->tab[j])->key == k)) {
                            (Hc->tab[j])->val++;
                            //Trouve le gagnant
                            if ((Hc->tab[j])->val > max) {
                                max = (Hc->tab[j])->val;
                                gagne = j;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
        decl = decl->next;
    }
    return Hc->tab[gagne]->key;
}