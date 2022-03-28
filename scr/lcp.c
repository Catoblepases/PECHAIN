#include "lcp.h"
#include <stdio.h>
#include <stdlib.h>

CellProtected *create_cell_protected(Protected *pr) {
    CellProtected *LCP = (CellProtected *) malloc(sizeof(CellProtected));
    LCP->data          = pr;
    LCP->next          = NULL;
    return LCP;
}

void add_head_LCP(CellProtected **LCP, Protected *pr) {
    CellProtected *new = create_cell_protected(pr);
    new->next          = *LCP;
    *LCP               = new;
}

CellProtected *read_protected(char *fileName) {
    FILE          *f = fopen(fileName, "r");
    char           buf[1 << 12];
    CellProtected *LCP = NULL;
    Protected     *pr;
    while (fgets(buf, 1 << 12, f)) {
        pr = str_to_protected(buf);
        if (!LCP) {
            LCP = create_cell_protected(pr);
        } else {
            add_head_LCP(&LCP, pr);
        }
    }
    fclose(f);
    return LCP;
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
