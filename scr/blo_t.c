#include "blo_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CellTree *create_node(Block *b) {
    CellTree *ct = (CellTree *) malloc(sizeof(CellTree));
    if (!ct) exit(3);
    ct->block = b;
    ct->father = NULL;
    ct->firstChild = NULL;
    ct->height = 0;
    ct->nextBro = NULL;
    return ct;
}

int update_height(CellTree *father, CellTree *child) {
    if (father->height < child->height + 1) {
        father->height = child->height + 1;
        return 1;
    }
    return 0;
}

void add_child(CellTree *father, CellTree *child) {
    if (!father->firstChild) {
        father->firstChild = child;
    } else {
        CellTree *tmpChild = father->firstChild;
        while (tmpChild->nextBro) {
            tmpChild = tmpChild->nextBro;
        }
        tmpChild->nextBro = child;
    }
    child->father = father;
    CellTree *Tfather = father;
    while (Tfather) {
        update_height(Tfather, child);
        child = Tfather;
        Tfather = Tfather->father;
    }
}

void print_tree(CellTree *cell) {
    if (!cell) return;
    CellTree *tr = cell;
    while (tr) {
        printf("(%d,%s) ", tr->height, tr->block->hash);
        tr = tr->nextBro;
    }
    printf("\n");
    tr = cell;
    while (tr) {
        print_tree(tr->firstChild);
        tr = tr->nextBro;
    }
}

void delete_node(CellTree *node) {
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree *cell) {
    if (!cell) return;
    CellTree *tmpBro = cell, *tmp;
    while (tmpBro) {
        tmp = tmpBro->nextBro;
        delete_tree(tmpBro->firstChild);
        delete_node(tmpBro);
        tmpBro = tmp;
    }
}

CellTree *highest_child(CellTree *cell) {
    CellTree *hc = NULL;
    CellTree *child = cell->firstChild;
    while (child) {
        if ((!hc) || (child->height > hc->height)) {
            hc = child;
        }
        child = child->nextBro;
    }
    return hc;
}

CellTree *last_node(CellTree *tree) {
    if (!tree) exit(4);
    if (!tree->firstChild) return tree;
    return last_node(highest_child(tree));
}

CellProtected *fusion(CellProtected *lcp1, CellProtected *lcp2) {
    if (lcp1 == NULL) return lcp2;
    if (lcp2 == NULL) return lcp1;
    CellProtected *lcp = fusion(lcp1->next, lcp2->next);
    add_head_LCP(&lcp, lcp1->data);
    add_head_LCP(&lcp, lcp2->data);
    return lcp;
}

CellProtected *fusionAll(CellTree *tree) {
    if (!tree) return NULL;
    CellTree *tr = tree;
    CellProtected *lcp = fusionAll(tree->firstChild);
    while (tr->block) {
        lcp = fusion(lcp, tr->block->votes);
        tr = tr->nextBro;
    }
    return lcp;
}

CellProtected *LongestList(CellTree *tree) {
    CellTree *highestChild = highest_child(tree);
    CellProtected *lcp = fusionAll(highestChild);
    return lcp;
}