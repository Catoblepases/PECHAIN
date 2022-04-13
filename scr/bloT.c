#include "bloT.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CellTree *create_node(Block *b) {
    CellTree *ct = (CellTree *) malloc(sizeof(CellTree));
    ct->block = b;
    ct->father = NULL;
    ct->firstChild = NULL;
    ct->height = 0;
    ct->nextBro = NULL;
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
    update_height(father, child);
}

void print_tree(CellTree *cell) {
    if (!cell) return;
    if (!cell->father) {
        printf("(%d,%s)\n", cell->height, cell->block->hash);
    }
    CellTree *child = cell->firstChild;
    while (child) {
        printf("(%d,%s) ", child->height, child->block->hash);
        child = child->nextBro;
    }
    printf("\n");
    print_tree(cell->firstChild);
}

void delete_node(CellTree *node) {
    delete_block(node->block);
    free(node);
}

void delete_tree(CellTree *cell) {
    if (!cell) return;
    if (!cell->father) delete_tree(cell);
    CellTree *tmpBro = cell->firstChild, tmp;
    while (tmpBro) {
        tmp = tmpBro->nextBro;
        delete_tree(tmpBro);
        tmpBro = tmp;
    }
}

CellTree *highest_child(CellTree *cell) {
    CellTree *hc = NULL;
    CellTree *child = father->firstChild;
    while (child) {
        if ((!hc) || (child->height > hc->height)) {
            hc = child;
        }
        child = child->nextBro;
    }
    return hc;
}

CellTree *last_node(CellTree *tree) {
    CellTree *highestChild = highest_child(tree);
    if (highestChild->height != 0) {
        return last_node(highestChild);
    }
    return highestChild;
}
