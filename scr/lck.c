#include "lck.h"
#include <stdio.h>
#include <stdlib.h>

/* Alloue et initialise une cellule de liste chaînée.*/
CellKey *create_cell_key(Key *key) {
    CellKey *LCK = (CellKey *) malloc(sizeof(CellKey));
    if (LCK == NULL) {
        printf("Erreur lors de l'allocation !");
        return NULL;
    } else {
        LCK->data = key;
        LCK->next = NULL;
        return LCK;
    }
}

/*Ajoute une clé en tête de liste.*/
void add_head(CellKey **LCK, Key *key) {
    CellKey *new = create_cell_key(key);
    new->next    = *LCK;
    *LCK         = new;
}

/*Prend en entrée le fichier keys.txt ou le fichier candidates.txt, et retourne une liste chaînée contenant toutes les clés publiques du fichier.*/
CellKey *read_public_keys(char *fileName) {
    FILE    *f = fopen(fileName, "r");
    char     buf[1 << 12];
    CellKey *LCK = NULL;
    Key     *key;
    while (fgets(buf, 1 << 12, f)) {
        key = str_to_key(buf);
        if (LCK == NULL) {
            LCK = create_cell_key(key);
        } else {
            add_head(&LCK, key);
        }
    }
    fclose(f);
    return LCK;
}

/*Affiche une liste chaînée de clés.*/
void print_list_keys(CellKey *LCK) {
    char *buf;
    // printf("print_list_keys\n");
    while (LCK != NULL) {
        // printf("----\n");
        buf = key_to_str(LCK->data);
        if (buf != NULL)
            printf("%s\n", buf);
        else
            printf("print_list_key detected nullpointer\n");
        LCK = LCK->next;
        free(buf);
    }
}

/* Supprime une cellule de liste chaînée de clés.*/
void delete_cell_key(CellKey *LCK) {
    if (LCK != NULL) {
        free(LCK->data);
        free(LCK);
    }
}

/*Supprime une liste chaînée de clés.*/
void delete_list_key(CellKey *LCK) {
    if (LCK == NULL) return;
    CellKey *tmp, *lck = LCK;
    while (lck != NULL) {
        tmp = lck->next;
        delete_cell_key(lck);
        lck = tmp;
    }
}
