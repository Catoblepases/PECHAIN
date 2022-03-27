#include "key.h"
#ifndef  _LISTECHAINEE
#define _LISTECHAINEE

typedef struct _cellKey{
    Key*data;
    struct _cellKey* next;
} CellKey;

CellKey* create_cell_key(Key* key);
void inserer_en_tete(CellKey* c,Key* k);
CellKey* read_public_keys(char* fichier);
void print_list_keys(CellKey* LCK);
void delete_cell_key(CellKey*c);
void delete_list_key(CellKey* LCK);

#endif