#include "lck.h"
#include <stdio.h>
#include <stdlib.h>

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

void add_head(CellKey **LCK, Key *key) {
    CellKey *new = create_cell_key(key);
    new->next    = *LCK;
    *LCK         = new;
}

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

void print_list_keys(CellKey *LCK) {
    char *buf;
    while (LCK != NULL) {
        buf = key_to_str(LCK->data);
        if (buf != NULL) printf("%s\n", buf);
        LCK = LCK->next;
        free(buf);
    }
}

void delete_cell_key(CellKey *LCK) {
    if (LCK != NULL) {
        free(LCK->data);
        free(LCK);
    }
}

void delete_list_key(CellKey *LCK) {
    if (LCK == NULL) return;
    CellKey *tmp, *lck = LCK;
    while (lck != NULL) {
        tmp = lck->next;
        delete_cell_key(lck);
        lck = tmp;
    }
    free(LCK);
}
