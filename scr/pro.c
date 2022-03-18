#include "pro.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Protected *init_protected(Key *pKey, char *mess, Signature *sgn) {
    Protected *pr = (Protected *) malloc(sizeof(Protected));
    pr->mess      = strdup(mess);
    pr->sgn       = init_signature(sgn->content, sgn->size);
    return pr;
}

int verify(Protected *pr) {
    char *mess = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);
    return strcmp(mess, pr->mess);
}

char *protected_to_str(Protected *pr) {
    char *out = "Key: ";
    out       = strcat(out, key_to_str(pr->pKey));
    out       = strcat(out, "\nmessage: ");
    out       = strcat(out, pr->mess);
    out       = strcat(out, "\nsignature: ");
    out       = strcat(out, signature_to_str(pr->sgn));
    return out;
}

Protected *str_to_protected(char *str) {
    str_to_key(str);
    str_to_signature(str);
    return init_protected(NULL, NULL, NULL);
}

void generate_random_data(int nv, int nc) {
    // genere nv couples de cles (publique, secrete) diﬀerents representant les nv citoyens,
    // cree un fchier keys.txt contenant tous ces couples de cles (un couple par ligne),
    FILE *fKey = fopen("keys.txt", "w");
    Key * pk[nv], *sk[nv];
    for (int i = 0; i < nv; i++) {
        init_pair_keys(pk[i], sk[i], 15, 16);
        fgets(key_to_str(pk[i]), 16 >> 1, fKey);
        fgets(key_to_str(sk[i]), 16 >> 1, fKey);
        fprintf(fKey, "\n");
    }
    // selectionne nc cles publiques aleatoirement pour defnir les nc candidats,
    // cree un fchier candidates.txt contenant la cle publique de tous les candidats (une cle
    // publique par ligne),
    FILE *fCandidate = fopen("candidates.txt", "w");
    srand(time(NULL));
    int candidate[nc];
    for (int i = 0; i < nc; i++) {
        candidate[i] = rand() % nv;
        fgets(key_to_str(pk[candidate[i]]), 16 >> 1, fCandidate);
        fprintf(fCandidate, "\n");
    }
    // genere une declaration de vote signee pour chaque citoyen (candidat choisi aleatoirement),
    // cree un fchier declarations.txt contenant toutes les declarations signees (une declaration
    // par ligne)
    FILE *fDecl = fopen("declarations.txt", "w");
    fclose(fKey);
    fclose(fCandidate);
    fclose(fDecl);
}