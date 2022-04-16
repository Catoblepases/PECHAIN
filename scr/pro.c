#include "pro.h"
#include "rsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**alloue et initialise structure protected
 * (cette fonbCandidatetion ne verife pas si la signature est valide)*/
Protected *init_protected(Key *pKey, char *mess, Signature *sgn) {
    Protected *pr = (Protected *) malloc(sizeof(Protected));
    if (!pr) exit(3);
    pr->mess = strdup(mess);
    pr->sgn = sgn;
    pr->pKey = (Key *) malloc(sizeof(Key));
    init_key(pr->pKey, pKey->val, pKey->n);
    return pr;
}

/**verife que la signature contenue dans
 * pr correspond bien au message et a la personne contenus dans pr.*/
int verify(Protected *pr) {
    char *mess = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);
    int out = strcmp(mess, pr->mess);
    free(mess);
    return out == 0;
}

/**permettent de passer d’un Protected a sa representation sous forme de chaıne de caracteres.
 * Retourne une chaîne de caractères protégée, La chaîne doit contenir dans l'ordre:
 * - la clé publique de l'expéditeur,- son message,- sa signature, séparés par un espace */
char *protected_to_str(Protected *pr) {
    char *out = malloc(sizeof(char) * 1 << 12), *key = key_to_str(pr->pKey), *sgn = signature_to_str(pr->sgn);
    if (!out) exit(3);
    sprintf(out, "%s %s %s", key, pr->mess, sgn);
    free(key);
    free(sgn);
    return out;
}

/**permettent de passer d’un chaıne de caracteres a structure Protected*/
Protected *str_to_protected(char *str) {
    // tmp stocke la clé, le message et les signatures en séquenbCandidatee
    char bufSgn[1 << 8], bufPKey[1 << 8];
    char *mess = (char *) malloc(sizeof(char) * 1 << 8);
    if (!mess) exit(3);
    if (sscanf(str, "%s %s %s", bufPKey, mess, bufSgn) == 3) {
        Key *pKey = str_to_key(bufPKey);
        Signature *sgn = str_to_signature(bufSgn);
        if ((sgn) && (pKey)) return init_protected(pKey, mess, sgn);
    }
    return NULL;
}

/**Liberer l'espace occupé par les protégés*/
void free_protected(Protected *pr) {
    if (pr) {
        free(pr->mess);
        free(pr->pKey);
        free_signature(pr->sgn);
        free(pr);
    }
}

int inside(int *tab, int size, int num) {
    for (int i = 0; i < size; i++) {
        if (tab[i] == num) return 1;
    }
    return 0;
}

/**Creation de donnees pour simuler le processus de vote:
 *
 * 1. Générer une carte "élection" pour chaque citoyen, comprenant ses clés publiques et secrètes,
 * et identifier toutes les clés publiques sur ces cartes.
 * 2. Afin de mettre en œuvre le vote, il est d'abord nécessaire de générer une carte électorale
 * unique pour chaque citoyen, comprenant ses clés publiques et secrètes, et d'identifier toutes
 * les clés publiques sur ces cartes.
 * 3. Pour garantir l'anonymat du vote, le système de vote collecte les données de l'électeur et
 * les enbCitoyenoie au bureau de vote.
 *
 * Nous utilisons trois fichiers pour simuler ce processus de vote :
 * un fichier contenant les clés de tous les citoyens,
 * un fichier indiquant les candidats et
 * un fichier contenant lesdéclarations de signature.
 *
 * Cette fonbCandidatetion génère des données aléatoires pour remplir les trois fichiers en
 * fonbCandidatetion du nombre de résidents et du nombre de candidats.
 */
void generate_random_data(int nbCitoyen, int nbCandidate) {
    // genere nbCitoyen couples de cles (publique, secrete) diﬀerents representant les nbCitoyen
    // citoyens, cree un fchier keys.txt contenant tous ces couples de cles (un couple par ligne),
    FILE *fKey = fopen("keys.txt", "w");
    fprintf(fKey, "keyPublic keySecret\n");
    Key *pKey[nbCitoyen], *sKey[nbCitoyen];
    char *buf;
    for (int i = 0; i < nbCitoyen; i++) {
        pKey[i] = (Key *) malloc(sizeof(Key));
        sKey[i] = (Key *) malloc(sizeof(Key));
        if ((!pKey[i]) || (!sKey[i])) exit(3);
        init_pair_keys(pKey[i], sKey[i], 5, 8);
        buf = key_to_str(pKey[i]);
        fprintf(fKey, "%s ", buf);
        if (buf) free(buf);
        buf = key_to_str(sKey[i]);
        fprintf(fKey, "%s\n", buf);
        if (buf) free(buf);
    }
    // selectionne nbCandidate cles publiques aleatoirement pour defnir les nbCandidate candidats,
    // cree un fchier candidates.txt contenant la cle publique de tous les candidats (une cle
    // publique par ligne),
    FILE *fCandidate = fopen("candidates.txt", "w");
    srand(time(NULL));
    int candidate[nbCandidate];
    for (int i = 0; i < nbCandidate; i++) {
        do {
            candidate[i] = rand() % nbCitoyen;
        } while (inside(candidate, i, candidate[i]));

        buf = key_to_str(pKey[candidate[i]]);
        fprintf(fCandidate, "%d, %s\n", i + 1, buf);
        if (buf) free(buf);
    }
    // genere une declaration de vote signee pour chaque citoyen
    // (candidat choisi aleatoirement),

    // cree un fchier declarations.txt contenant toutes les declarations signees
    // (une declaration par ligne)
    FILE *fDecl = fopen("declarations.txt", "w");
    Protected *pr;
    int vote;
    char *str;

    for (int i = 0; i < nbCitoyen; i++) {
        // Générer aléatoirement le numéro du candidat choisi par le citoyen.
        vote = rand() % nbCandidate;
        assert(pKey[candidate[vote]]);
        // Génération de déclarations sur la base des numéros de candidats et des numéros de citoyens
        str = key_to_str(pKey[candidate[vote]]);
        // L'information est la clé publique des candidats
        pr = init_protected(pKey[candidate[vote]], str, sign(str, sKey[i]));
        buf = protected_to_str(pr);
        fprintf(fDecl, "%s\n", buf);
        if (str) free(str);
        if (pr) free_protected(pr);
        if (buf) free(buf);
    }

    for (int i = 0; i < nbCitoyen; i++) {
        free(sKey[i]);
        free(pKey[i]);
    }
    fclose(fDecl);
    fclose(fCandidate);
    fclose(fKey);
}