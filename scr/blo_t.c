#include "blo_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Créer et initialiser un noeud avec une hauteur égale à zéro.*/
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

/*Mettre à jour la hauteur du noeud father quand l'un de ses fils a été modifié:
la hauteur du noeud father doit être égale au max entre sa hauteur courante et la hauteur du noeud child + 1.
Cette fonction doit retourner 1 si la hauteur du noeud father a changé, et 0 sinon.*/
int update_height(CellTree *father, CellTree *child) {
    if (!father || !child) return 0;

    if (father->height < child->height + 1) {
        father->height = child->height + 1;
        return 1;
    }
    return 0;
}

/*Ajoute un fils à un noeud, en mettant à jour la hauteur de tous les ascendants.*/
void add_child(CellTree *father, CellTree *child) {
    if (!father || !child) return;

    if (!father->firstChild) {
        father->firstChild = child;
    } else { // s'il existe déjà un fils
        child->nextBro = father->firstChild;
        father->firstChild = child;
    }
    child->father = father;
    CellTree *Tfather = father;
    while (Tfather) {
        // Mettre à jour la houteur du noeud Tfather
        update_height(Tfather, child);
        child = Tfather;
        Tfather = Tfather->father;
    }
}

/*Affiche un noeud: la hauteur du noeud et la valeur hachée du bloc correspondant.*/
void print_node(CellTree *node) {
    if (!node) return;
    printf("(%d,%s) ", node->height, node->block->hash);
}

/*Affiche un arbre.*/
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

/*Supprimer un noeud de l'arbre.*/
void delete_node(CellTree *node) {
    if (!node) return;
    delete_block(node->block);
    free(node);
}

/*Supprimer un arbre.*/
void delete_tree(CellTree *ct) {
    if (!ct) return;
    delete_tree(ct->firstChild);
    delete_tree(ct->nextBro);
    delete_node(ct);
}

/*Supprimer l'arbre ne supprime pas la liste des déclarations*/
void delete_tree_partial(CellTree *ct) {
    if (!ct) return;
    delete_tree_partial(ct->firstChild);
    delete_tree_partial(ct->nextBro);
    delete_block_partial(ct->block);
    free(ct);
}

/* Renvoie le noeud fils avec la plus grande hauteur.*/
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

/*Retourner le dernier bloc de cette plus longue chaîne.*/
CellTree *last_node(CellTree *tree) {
    if ((!tree) || (!(tree->block))) return NULL;
    if (!tree->firstChild) return tree;
    return last_node(highest_child(tree));
}

/*Fusionner deux listes chaînées de déclarations signées.*/
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

/* Retourner la liste obtenue par fusion des listes chaînées de déclarations contenues dans les blocs de la plus longue
 * chaîne.*/
CellProtected *longestList(CellTree *tree) {
    if (!tree) return NULL;
    return fusion(tree->block->votes, longestList(highest_child(tree)));
}