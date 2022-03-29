#include "scr/pro.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void test1() {
    srand(time(NULL));
    // Testing Init Keys
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey:%lx,%lx\n", pKey->val, pKey->n);
    printf("sKey:-%lx,-%lx-\n", sKey->val, sKey->n);
    // Testing Key Serialization
    char *chaine = key_to_str(pKey);
    printf("key_to_str:.%s.\n", chaine);
    Key *k = str_to_key(chaine);
    printf("str-to-key:-%lx,-%lx-\n", k->val, k->n);
    // Testing signature
    // Candidate keys:
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);
    // Declaration:
    char *mess = key_to_str(pKeyC);
    printf("%svote.pour.%s\n", key_to_str(pKey), mess);
    Signature *sgn = sign(mess, sKey);
    printf("signature:…");
    print_long_vector(sgn->content, sgn->size);
    chaine = signature_to_str(sgn);
    printf("signature-to_str:%s.\n", chaine);
    sgn = str_to_signature(chaine);
    printf("str-to_signature:…");
    print_long_vector(sgn->content, sgn->size);
    // Testing protected:
    Protected *pr = init_protected(pKey, mess, sgn);
    // Verification:
    if (verify(pr)) {
        printf("Signature-valide\n");
    } else {
        printf("Signature. non. valide\n");
    }
    chaine = protected_to_str(pr);
    printf("protected-to-str:.%s\n", chaine);
    pr = str_to_protected(chaine);
    printf("strto-protected:.%s.%s.%s\n", key_to_str(pr->pKey), pr->mess,
           signature_to_str(pr->sgn));
    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
    free_protected(pr);
    free_signature(sgn);
}

int main(void) {
    test1();
    // Creation de donnees pour simuler le processus de vote
    // generate_random_data(100, 10);
    return 0;
}