#include "pro.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Protected *init_protected(Key *pKey, char *mess, Signature *sgn) {
    Protected *pr = (Protected *) malloc(sizeof(Protected));
    pr->mess      = strdup(mess);
    pr->sgn       = sgn;
    return pr;
}

int verify(Protected *pr) {
    char *mess = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);
    return strcmp(mess, pr->mess);
}

/**Returns a string of protected, The string must contain in order :
- the sender's public key,- his message,- his signature, separated by a space */
char *protected_to_str(Protected *pr) {
    char *out = strdup("");
    out       = strcat(out, key_to_str(pr->pKey));
    out       = strcat(out, " ");
    out       = strcat(out, pr->mess);
    out       = strcat(out, " ");
    out       = strcat(out, signature_to_str(pr->sgn));
    return out;
}

Protected *str_to_protected(char *str) {
    // Storing key, message and signatures in sequence
    char **tmp      = malloc(sizeof(char *) * 3);
    int    separate = 1;
    int    begin, idx = -1, pointAt = 0;
    while (str[++idx] != '\0') {
        if (separate) {
            begin    = idx;
            separate = 0;
        } else if (str[idx] == ' ') {
            separate     = 1;
            tmp[pointAt] = malloc(sizeof(char) * (idx - begin + 2));
            strncpy(tmp[pointAt], str + begin, idx - begin + 1);
        }
    }
    Key       *key = str_to_key(tmp[0]);
    Signature *sgn = str_to_signature(tmp[1]);
    Protected *pr  = init_protected(key, tmp[2], sgn);
    for (int i = 0; i < 3; i++) {
        free(tmp[i]);
    }
    free(tmp);
    return pr;
}

void free_protected(Protected *pr) {
    free(pr->mess);
    free(pr->pKey);
    free_signature(pr->sgn);
    free(pr);
}

void generate_random_data(int nv, int nc) {
    // genere nv couples de cles (publique, secrete) diﬀerents representant les nv citoyens,
    // cree un fchier keys.txt contenant tous ces couples de cles (un couple par ligne),
    FILE *fKey = fopen("keys.txt", "w");
    fprintf(fKey, "keyPublic,keySecret\n");

    Key  *pk[nv], *sk[nv];
    char *buf;
    for (int i = 0; i < nv; i++) {
        pk[i] = malloc(sizeof(Key));
        sk[i] = malloc(sizeof(Key));
        init_pair_keys(pk[i], sk[i], 3, 7);
        buf = key_to_str(pk[i]);
        fprintf(fKey, "%s\n", buf);
        if (buf) free(buf);
    }
    // selectionne nc cles publiques aleatoirement pour defnir les nc candidats,
    // cree un fchier candidates.txt contenant la cle publique de tous les candidats (une cle
    // publique par ligne),
    FILE *fCandidate = fopen("candidates.txt", "w");
    srand(time(NULL));
    int candidate[nc];
    for (int i = 0; i < nc; i++) {
        candidate[i] = rand() % nv;
        buf          = key_to_str(pk[candidate[i]]);
        fprintf(fCandidate, "%d, %s\n", i + 1, buf);
        if (buf) free(buf);
    }
    // genere une declaration de vote signee pour chaque citoyen (candidat choisi
    // aleatoirement),
    // cree un fchier declarations.txt contenant toutes les declarations signees (une
    // declaration par ligne)
    FILE      *fDecl = fopen("declarations.txt", "w");
    Protected *pr;
    int        vote;
    char      *str;
    for (int i = 0; i < nv; i++) {
        vote = rand() % nc + 1;
        // printf("%s %d ", vote, strlen(vote));
        // encr = encrypt(vote, pKey->val, pKey->n);
        str = key_to_str(pk[vote]);
        pr  = init_protected(pk[i], str, sign(str, sk[i]));
        buf = protected_to_str(pr);
        fprintf(fDecl, "%s\n", buf);
        if (str) free(str);
        if (pr) free_protected(pr);
        if (buf) free(buf);
    }

    for (int i = 0; i < nv; i++) {
        free(sk[i]);
        free(pk[i]);
    }

    fclose(fDecl);
    fclose(fCandidate);
    fclose(fKey);
}