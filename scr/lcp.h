#include "pro.h"
#ifndef _LISTECHAINEEDEDECLARATIONSSIGNEES
#define _LISTECHAINEEDEDECLARATIONSSIGNEES
typedef struct cellProtected {
    Protected            *data;
    struct cellProtected *next;
} CellProtected;

CellProtected *create_cell_protected(Protected *pr);
void           add_head(CellProtected **cp, Protected *p);
void           read_protected(char *fichier);
void           print_list_protected(CellProtected *LCP);
void           delete_cell_protected(CellProtected *c);
void           delete_list_protected(CellProtected *LCP);

#endif
