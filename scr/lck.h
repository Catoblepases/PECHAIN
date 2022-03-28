#ifndef __LCK
#define __LCK
#include "key.h"

typedef struct cellKey {
    Key            *data;
    struct cellKey *next;
} CellKey;

CellKey *create_cell_key(Key *key);
CellKey *read_public_keys(char *fichier);
void     print_list_keys(CellKey *LCK);
void     delete_cell_key(CellKey *c);
void     delete_list_key(CellKey *LCK);

#endif