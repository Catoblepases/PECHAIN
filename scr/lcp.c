#include "lcp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

CellProtected *create_cell_protected(Protected *pr) {
    assert(pr);
    CellProtected *LCP = (CellProtected *) malloc(sizeof(CellProtected));
    LCP->data          = pr;
    LCP->next          = NULL;
    return LCP;
}

void add_head_LCP(CellProtected **LCP, Protected *pr) {
    assert(pr);
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
        if (!pr) continue;
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
        assert(LCP->data);
        buf = protected_to_str(LCP->data);
        if (buf != NULL) printf("%s\n", buf);
        LCP = LCP->next;
        free(buf);
    }
}

void delete_cell_protected(CellProtected *c) {
    if (c != NULL) {
        free_protected(c->data);
        free(c);
    }
}

void delete_list_protected(CellProtected *LCP) {
    CellProtected *tmp = LCP;
    while (LCP != NULL) {
        tmp = LCP->next;
        delete_cell_protected(LCP);
        LCP = tmp;
    }
}

// Returns the number of error signatures and removes all incorrect objects
int verifyForList(CellProtected **LCP) {
    CellProtected *lcp = *LCP, *tmp;
    int            nb  = 0;
    if (!verify(lcp->data)) {
        lcp  = lcp->next;
        tmp  = *LCP;
        *LCP = (*LCP)->next;
        delete_cell_protected(tmp);
        nb++;
    }
    while (lcp->next) {
        assert(lcp->next->data);
        if (!verify(lcp->next->data)) {
            tmp       = lcp->next;
            lcp->next = lcp->next->next;
            delete_cell_protected(tmp);
            nb++;
        }
        lcp = lcp->next;
    }
    return nb;
}