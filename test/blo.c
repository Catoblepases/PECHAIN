#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "params.h"
#include "scr/blo.h"

int main(void) {

    printf("----------START BLOCK SERIALIZATION TEST----------\n");
    // generation cles author
    char *str_key = "(8977,6817)";
    Key *pKey = str_to_key(str_key);
    char *strKey = key_to_str(pKey);
    printf("%s\n", strKey);
    free(strKey);

    // generation des declaration
    CellProtected *lp = read_protected(FILE_DECLARATIONS);

    Block *b = (Block *) malloc(sizeof(Block));
    if (!b) exit(12);

    // on met des donnees random juste pour test
    b->author = pKey;
    b->hash = strdup("test_hash");
    b->nonce = 0;
    b->previous_hash = strdup("test_previous_hash");
    b->votes = lp;
    free(lp);

    write_block(FILE_BLOCKS, b);

    Block *b_read = read_block(FILE_BLOCKS);
    write_block(FILE_BLOCKS_TEST, b_read);

    printf("-----START BLOCK_TO_STR-----\n\n");
    char *str_b = block_to_str(b_read);
    printf("%s\n", str_b);
    printf("-----END BLOCK_TO_STR-----\n\n");

    printf("----------END BLOCK SERIALIZATION TEST----------\n\n\n");

    printf("----------START TEST OPENSSL----------\n");
    const char *s = "Rosetta code";
    unsigned char *test_sha = SHA256(s, strlen(s), 0);

    printf("Affichage SHA256: \n");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", test_sha[i]);
    }
    printf("\n");

    printf("Affichage de notre SHA256: \n");
    char *s2 = "Rosetta code";
    char *res = str_to_SHA256(s2);
    printf("%s\n", res);
    free(res);

    printf("----------END TEST OPENSSL----------\n\n");

    printf("----------START PROOF_OF_WORK COMPARISON----------\n\n");
    clock_t temps_initial, temps_final;
    double temps_cpu, temps = 0.0;

    int d_value = 0;
    FILE *f = fopen("profOfWork.csv", "w");
    fprintf(f, "d,time\n");
    while (1) {
        fprintf(f, "%d,%.6f\n", d_value, temps);
        printf("Temps: %fs\tHash trouver pour d = %d: \t", temps, d_value);
        temps_initial = clock();
        compute_proof_of_work(b, d_value);
        temps_final = clock();
        temps = ((double) (temps_final - temps_initial)) / CLOCKS_PER_SEC;
        if (temps > 300) {
            break;
        }
        d_value += 1;
    }
    fclose(f);

    printf("\n----------END PROOF_OF_WORK COMPARISON----------\n\n\n");

    free(str_b);
    delete_block(b_read);
    delete_block(b);

    return 0;
}
