#include "scr/pro.h"
#include "scr/rsa.h"
#include "scr/utility.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void test1() {
    srand(time(NULL));
    // Testing Init Keys
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 5, 10);
    printf("pKey:%lx,%lx\n", pKey->val, pKey->n);
    printf("sKey:-%lx,-%lx-\n", sKey->val, sKey->n);
    // Testing Key Serialization
    printf("key_to_str:.%s.\n", key_to_str_static(pKey));
    Key *k = str_to_key(key_to_str_static(pKey));
    printf("str-to-key:-%lx,-%lx-\n", k->val, k->n);
    free(k);
    // Testing signature
    // Candidate keys:
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);
    // Declaration:
    printf("%svote.pour.%s\n", key_to_str_static(pKey), key_to_str_static(pKeyC));
    Signature *sgn = sign(key_to_str_static(pKey), sKey);
    printf("signature:…");
    print_long_vector(sgn->content, sgn->size);
    printf("signature-to_str:%s.\n", signature_to_str_static(sgn));
    char *chaine = signature_to_str(sgn);
    free_signature(sgn);
    sgn = str_to_signature(chaine);
    printf("str-to_signature:…");
    print_long_vector(sgn->content, sgn->size);
    free(chaine);
    // Testing protected:
    Protected *pr = init_protected(pKey, key_to_str_static(pKey), sgn);
    // Verification:
    if (verify(pr)) {
        printf("Signature-valide\n");
    } else {
        printf("Signature. non. valide\n");
    }

    free_protected(pr);
    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);
}

int main(void) {
    // for (int i = 0; i < 20; i++) {
    test1();
    // }
    // Creation de donnees pour simuler le processus de vote
    generate_random_data(NB_KEYS, NB_CANDIDATS);
    return 0;
}