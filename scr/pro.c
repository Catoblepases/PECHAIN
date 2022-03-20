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
    fprintf(fKey, "keyPublic,keySecret\n");

    Key * pk[nv], *sk[nv];
    char *kkey;
    for (int i = 0; i < nv; i++) {
        pk[i] = malloc(sizeof(Key));
        sk[i] = malloc(sizeof(Key));
        init_pair_keys(pk[i], sk[i], 3, 7);
        kkey = key_to_str(pk[i]);
        fprintf(fKey, "%s\n", kkey);
    }
    // selectionne nc cles publiques aleatoirement pour defnir les nc candidats,
    // cree un fchier candidates.txt contenant la cle publique de tous les candidats (une cle
    // publique par ligne),
    FILE *fCandidate = fopen("candidates.txt", "w");
    srand(time(NULL));
    int candidate[nc];
    for (int i = 0; i < nc; i++) {
        candidate[i] = rand() % nv;
        fprintf(fCandidate, "%d, %s\n", i + 1, key_to_str(pk[candidate[i]]));
    }
    // genere une declaration de vote signee pour chaque citoyen (candidat choisi
    // aleatoirement),
    // cree un fchier declarations.txt contenant toutes les declarations signees (une
    // declaration par ligne)
    FILE *     fDecl = fopen("declarations.txt", "w");
    Signature *tmp;
    char       vote[1 << 8];

    int64 *mm;

    for (int i = 0; i < nv; i++) {
        sprintf(vote, "00%d", rand() % nc + 1);
        // printf("%s %d ", vote, strlen(vote));

        Key *pKey = malloc(sizeof(Key));
        Key *sKey = malloc(sizeof(Key));
        init_pair_keys(pKey, sKey, 3, 7);
        mm = encrypt(vote, pKey->val, pKey->n);
        // mm = encrypt(vote, sk[i]->val, sk[i]->n);
        // print_long_vector(mm, strlen(vote));

        tmp = sign(vote, sKey);
        fprintf(fDecl, "%s\n", signature_to_str(tmp));
    }

    for (int i = 0; i < nv; i++) {
        free(sk[i]);
        free(pk[i]);
    }
    fclose(fDecl);
    fclose(fCandidate);
    fclose(fKey);
}