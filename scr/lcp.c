#include "lcp.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Alloue et initialise une cellule de liste chaînée de déclarations signées.*/
CellProtected *create_cell_protected(Protected *pr) {
    CellProtected *LCP = (CellProtected *) malloc(sizeof(CellProtected));
    LCP->data = pr;
    LCP->next = NULL;
    return LCP;
}

/*Ajoute une déclaration signée en tête de liste.*/
void add_head_LCP(CellProtected **LCP, Protected *pr) {
    CellProtected *new = create_cell_protected(pr);
    new->next = *LCP;
    *LCP = new;
}

/*Lit le fichier declarations.txt, et crée une liste contenant toutes les déclarations signées du fichier.*/
CellProtected *read_protected(char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) exit(3);
    char buf[1 << 12];
    CellProtected *LCP = NULL;
    Protected *pr = NULL;
    while (fgets(buf, 1 << 12, f)) {
        pr = str_to_protected(buf);
        if (!pr) continue;
        add_head_LCP(&LCP, pr);
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
        if (buf) printf("%s\n", buf);
        LCP = LCP->next;
        free(buf);
    }
}

/*Supprime une cellule de liste chaînée de déclarations sigées.*/
void delete_cell_protected(CellProtected *c) {
    if (c) {
        free_protected(c->data);
        free(c);
    }
}

/*Supprime une liste chaînée de déclarations signées.*/
void delete_list_protected(CellProtected *LCP) {
    CellProtected *tmp;
    while (LCP) {
        tmp = LCP->next;
        delete_cell_protected(LCP);
        LCP = tmp;
    }
}

/*Renvoie le nombre de signatures invalides et les supprime.*/
int verify_for_list_protected(CellProtected **LCP) {
    CellProtected *lcp = *LCP, *tmp;
    int nb = 0;
    // Vérifie la validité de la première déclaration signée.*/
    assert(lcp->data);
    if (!verify(lcp->data)) {
        lcp = lcp->next;
        tmp = *LCP;
        *LCP = (*LCP)->next;
        delete_cell_protected(tmp);
        nb++;
    }
    while (lcp->next) {
        assert(lcp->next->data);
        // Vérifie la validité de la prochaine déclaration signée.
        if (!verify(lcp->next->data)) {
            tmp = lcp->next;
            lcp->next = lcp->next->next;
            delete_cell_protected(tmp);
            nb++;
        }
        lcp = lcp->next;
    }
    return nb;
}
