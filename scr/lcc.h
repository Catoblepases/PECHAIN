#include "key.h"
#ifndef  _LISTECHAINEEDECLES
#define _LISTECHAINEEDECLES

typedef struct cellKey{
    Key* data;
    struct cellKey* next;
}CellKey;
CellKey* create_cell_key(Key* key);
void inserer_en_tete(CellKey* c,Key* k);
CellKey* read_public_keys(char* fichier);
void print_list_keys(CellKey* LCK);
void delete_cell_key(CellKey*c);
void delete_list_key(CellKey* LCK);

#endif