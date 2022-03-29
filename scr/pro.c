#include "pro.h"
#include "rsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**alloue et initialise structure protected
 * (cette fonbCandidatetion ne verife pas si la signature est valide)*/
Protected *init_protected(Key *pKeyey, char *mess, Signature *sgn) {
    Protected *pr = (Protected *) malloc(sizeof(Protected));
    pr->mess      = strdup(mess);
    pr->sgn       = sgn;
    pr->pKeyey    = (Key *) malloc(sizeof(Key));
    init_key(pr->pKeyey, pKeyey->val, pKeyey->n);
    return pr;
}

/**verife que la signature contenue dans
 * pr correspond bien au message et a la personne contenus dans pr.*/
int verify(Protected *pr) {
    char *mess = decrypt(pr->sgn->content, pr->sgn->size, pr->pKeyey->val, pr->pKeyey->n);
    int   out  = strcmp(mess, pr->mess);
    free(mess);
    if (out == 0) return 1;
    return 0;
}

/**permettent de passer d’un Protected a sa representation sous forme de chaıne de caracteres.
 * Retourne une chaîne de caractères protégée, La chaîne doit contenir dans l'ordre:
 * - la clé publique de l'expéditeur,- son message,- sa signature, séparés par un espace */
char *protected_to_str(Protected *pr) {
    char *out = malloc(sizeof(char) * 1 << 16), *tmp = key_to_str(pr->pKeyey);
    out = strcpy(out, tmp);
    free(tmp);
    out = strcat(out, " ");
    out = strcat(out, pr->mess);
    out = strcat(out, " ");
    tmp = signature_to_str(pr->sgn);
    out = strcat(out, tmp);
    free(tmp);
    return out;
}
/**permettent de passer d’un chaıne de caracteres a structure Protected*/
Protected *str_to_protected(char *str) {
    // tmp stocke la clé, le message et les signatures en séquenbCandidatee
    char *tmp[3];
    int   idx    = 0;
    char *result = strtok(str, " ");
    while (result != NULL) {
        if (idx >= 3) return NULL;
        tmp[idx++] = result;
        result     = strtok(NULL, " ");
    }
    if (idx != 3) return NULL;
    // construct
    Key       *key = str_to_key(tmp[0]);
    Signature *sgn = str_to_signature(tmp[2]);
    if ((!key) || (!sgn) || (!tmp[1])) return NULL;
    Protected *pr = init_protected(key, tmp[1], sgn);
    // free
    free(key);
    return pr;
}

/**Liberer l'espace occupé par les protégés*/
void free_protected(Protected *pr) {
    free(pr->mess);
    free(pr->pKeyey);
    free_signature(pr->sgn);
    free(pr);
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
    fprintf(fKey, "keyPublic,keySecret\n");
    Key  *pKey[nbCitoyen], *sKey[nbCitoyen];
    char *buf;
    for (int i = 0; i < nbCitoyen; i++) {
        pKey[i] = (Key *) malloc(sizeof(Key));
        sKey[i] = (Key *) malloc(sizeof(Key));
        init_pair_keys(pKey[i], sKey[i], 5, 8);
        buf = key_to_str(pKey[i]);
        printf("%d ok : %s", i, buf);
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
        candidate[i] = rand() % nbCitoyen;
        buf          = key_to_str(pKey[candidate[i]]);
        fprintf(fCandidate, "%d, %s\n", i + 1, buf);
        if (buf) free(buf);
    }
    // genere une declaration de vote signee pour chaque citoyen
    // (candidat choisi aleatoirement),

    // cree un fchier declarations.txt contenant toutes les declarations signees
    // (une declaration par ligne)
    FILE      *fDecl = fopen("declarations.txt", "w");
    Protected *pr;
    int        vote;
    char      *str;

    for (int i = 0; i < nbCitoyen; i++) {
        // Générer aléatoirement le numéro du candidat choisi par le citoyen.
        vote = rand() % nbCandidate;
        assert(pKey[candidate[vote]]);
        // Génération de déclarations sur la base des numéros de candidats et des numéros de citoyens
        str = key_to_str(pKey[candidate[vote]]);
        // L'information est la clé publique des candidats
        pr  = init_protected(pKey[candidate[vote]], str, sign(str, sKey[i]));
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