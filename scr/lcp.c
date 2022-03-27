#include "lcp.h"
#include <stdlib.h>
#include <stdio.h>

CellProtected* create_cell_protected(Protected* pr){
    CellProtected* cp=(CellProtected*)malloc(sizeof(CellProtected));
    cp->data=pr;
    cp->next=NULL;
    return cp;
}

void inserer_en_tete(CellProtected* cp, Protected* p){
    CellProtected* np=create_cell_protected(p);
    np->next=cp;
    cp=np;

}

void read_protected(char* fichier){
    FILE *fic=fopen(fichier,"r");
    char tab[100];
    CellProtected* cp=(CellProtected*)malloc(sizeof(CellProtected));
    while (fgets(tab,100,fic)){
        inserer_en_tete(cp,str_to_protected(tab));
    }
}

void print_list_protected(CellProtected* LCP){
    while(LCP!=NULL){
        printf("%s\n",protected_to_str(LCP->data));
        LCP=LCP->next;
    }
}

void delete_cell_protected (CellProtected* c){
    if(c!=NULL){
        free(c->data);
        CellProtected* tmp=c->next;
        free(c);
        c=tmp;
    }
}

void delete_list_protected(CellProtected* LCP){
    while (LCP!=NULL){
        delete_cell_protected(LCP);
    }
}
