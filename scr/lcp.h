#ifndef __LSP__
#define __LSP__
#include "pro.h"

typedef struct cellProtected {
    Protected            *data;
    struct cellProtected *next;
} CellProtected;

CellProtected *create_cell_protected(Protected *pr);
void           add_head_LCP(CellProtected **LCP, Protected *p);
CellProtected *read_protected(char *fileName);
void           print_list_protected(CellProtected *LCP);
void           delete_cell_protected(CellProtected *c);
void           delete_list_protected(CellProtected *LCP);
int            verifyForList(CellProtected **LCP);

#endif
