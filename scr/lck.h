#ifndef __LCK__
#define __LCK__
#include "key.h"

/*Une cellule de la liste chaînée de clés CellKey qui contient une clé et la suivant.*/
typedef struct cellKey {
    Key            *data;
    struct cellKey *next;
} CellKey;

CellKey *create_cell_key(Key *key);
CellKey *read_public_keys(char *fichier);
void     print_list_keys(CellKey *LCK);
void     delete_cell_key(CellKey *c);
void     delete_list_key(CellKey *LCK);
void add_head(CellKey **LCK, Key *key);

#endif