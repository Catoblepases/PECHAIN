#include "lcp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*Alloue et initialise une cellule de liste chaînée de déclarations signées.*/ 
CellProtected *create_cell_protected(Protected *pr) {
    assert(pr);
    CellProtected *LCP = (CellProtected *) malloc(sizeof(CellProtected));
    LCP->data          = pr;
    LCP->next          = NULL;
    return LCP;
}

/*Ajoute une déclaration signée en tête de liste.*/
void add_head_LCP(CellProtected **LCP, Protected *pr) {
    assert(pr);
    CellProtected *new = create_cell_protected(pr);
    new->next          = *LCP;
    *LCP               = new;
}

/*Lit le fichier declarations.txt, et crée une liste contenant toutes les déclarations signées du fichier.*/
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

/*Affiche une liste chaînée de déclarations signées.*/
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

/*Supprime une cellule de liste chaînée de déclarations sigées.*/
void delete_cell_protected(CellProtected *c) {
    if (c != NULL) {
        free_protected(c->data);
        free(c);
    }
}

/*Supprime une liste chaînée de déclarations signées.*/
void delete_list_protected(CellProtected *LCP) {
    CellProtected *tmp = LCP;
    while (LCP != NULL) {
        tmp = LCP->next;
        delete_cell_protected(LCP);
        LCP = tmp;
    }
}

