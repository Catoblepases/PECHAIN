#include "lcc.h"
#include  <stdio.h>
#include <stdlib.h>

CellKey* create_cell_key(Key* key){
    CellKey *c=(CellKey*)malloc(sizeof(CellKey));
    if (c==NULL){
        printf("Erreur lors de l'allocation !");
        return NULL;
    }
    else{
        c->data=key;
        c->next=NULL;
        return c;
    }
}

void inserer_en_tete(CellKey* c,Key* k){
    CellKey* ck=create_cell_key(k);
    ck -> next=c;
    c=ck;


}

CellKey* read_public_keys(char* fichier){
    FILE *fic=fopen(fichier,"r");
    char tab[100];
    CellKey* c=(CellKey*)malloc(sizeof(CellKey));
    if (fgets(tab,100,fic)){
        Key* k=str_to_key(tab);
        inserer_en_tete(c,k);
    }
    return c;
}

void print_list_keys(CellKey* LCK){
    while(LCK!=NULL){
        printf("%s\n",key_to_str (LCK->data));
    }
}

void delete_cell_key(CellKey* c){
    if(c!=NULL){
        free(c->data);
        CellKey* tmp=c->next;
        free(c);
        c=tmp;
    }

}

void delete_list_key(CellKey* LCK){
    while(LCK!=NULL){
        delete_cell_key(LCK);
    }
}

