#include "lcp.h"
#include <stdio.h>
#include <stdlib.h>

CellProtected *create_cell_protected(Protected *pr) {
    CellProtected *LCP = (CellProtected *) malloc(sizeof(CellProtected));
    LCP->data          = pr;
    LCP->next          = NULL;
    return LCP;
}

void add_head(CellProtected **LCP, Protected *p) {
    CellProtected *new = create_cell_protected(p);
    new->next          = *LCP;
    *LCP               = new;
}

void read_protected(char *fichier) {
    FILE          *fic = fopen(fichier, "r");
    char           tab[1 << 12];
    CellProtected *LCP = (CellProtected *) malloc(sizeof(CellProtected));
    while (fgets(tab, 1 << 12, fic)) {
        add_head(&LCP, str_to_protected(tab));
    }
}

void print_list_protected(CellProtected *LCP) {
    char *buf;
    while (LCP != NULL) {
        buf = protected_to_str(LCP->data);
        if (buf != NULL) printf("%s\n", buf);
        LCP = LCP->next;
        free(buf);
    }
}

void delete_cell_protected(CellProtected *c) {
    if (c != NULL) {
        free(c->data);
        free(c);
    }
}

void delete_list_protected(CellProtected *LCP) {
    CellProtected *tmp = LCP, *lcp = LCP;
    while (lcp != NULL) {
        tmp = lcp->next;
        delete_cell_protected(lcp);
        lcp = tmp;
    }
    free(LCP);
}
