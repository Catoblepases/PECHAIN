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
    if (!father || !child) return 0;

    if (father->height < child->height + 1) {
        father->height = child->height + 1;
        return 1;
    }
    return 0;
}

void add_child(CellTree *father, CellTree *child) {
    if (!father || !child) return;

    if (!father->firstChild) {
        father->firstChild = child;
    } else {
        child->nextBro = father->firstChild;
        father->firstChild = child;
    }
    child->father = father;
    CellTree *Tfather = father;
    while (Tfather) {
        update_height(Tfather, child);
        child = Tfather;
        Tfather = Tfather->father;
    }
}

void print_node(CellTree *node) {
    if (!node) return;
    printf("(%d,%s) ", node->height, node->block->hash);
}

void print_tree(CellTree *cell) {
    if (!cell) return;
    CellTree *tr = cell;
    while (tr) {
        print_node(tr);
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
    if (!node) return;
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree *ct) {
    if (!ct) return;
    delete_tree(ct->firstChild);
    delete_tree(ct->nextBro);
    delete_node(ct);
}

void delete_tree_partial(CellTree *ct) {
    if (!ct) return;
    delete_tree_partial(ct->firstChild);
    delete_tree_partial(ct->nextBro);
    delete_block_partial(ct->block);
    free(ct);
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
    if ((!tree) || (!(tree->block))) return NULL;
    if (!tree->firstChild) return tree;
    return last_node(highest_child(tree));
}

CellProtected *fusion(CellProtected *lcp1, CellProtected *lcp2) {
    if (lcp1 == NULL) return lcp2;
    if (lcp2 == NULL) return lcp1;
    CellProtected *cell = lcp1;
    while (cell->next) {
        cell = cell->next;
    }
    cell->next = lcp2;
    return lcp1;
}

CellProtected *longestList(CellTree *tree) {
    if (!tree) return NULL;
    return fusion(tree->block->votes, longestList(highest_child(tree)));
}