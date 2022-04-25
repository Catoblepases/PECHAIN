#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./scr/utility.h"
#include "scr/blo.h"

int main(void) {

    // Générer des volontaires
    print_with_sepatator("create author");
    Key *pKey = (Key *) malloc(sizeof(Key));
    Key *sKey = (Key *) malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 1 << 3, 1 << 8);

    // Créer un bloc
    print_with_sepatator("create block");
    Block *block = create_random_block(pKey);

    // Blocs d'écriture et de lecture, conversions de chaînes de caractères
    print_with_sepatator("write_block read_block");
    write_block(FILE_BLOCKS, block);
    Block *block_read = read_block(FILE_BLOCKS);
    write_block(FILE_BLOCKS_TEST, block_read);
    print_with_sepatator("block_to_str");
    char *str_block = block_to_str(block_read);
    printf("%s\n", str_block);

    // Test sha256
    print_with_sepatator("sha256");
    unsigned char *hash = SHA256((unsigned char *) str_block, strlen(str_block), 0);
    printf("SHA256: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
    printf("str_to_SHA256: ");
    block->hash = str_to_SHA256(str_block);
    printf("%s\n", (char *) block->hash);
    free(str_block);

    //  PROOF_OF_WORK
    clock_t time_initial, time_final;
    double temps = 0.0;
    int d = 0;
    FILE *f = fopen(FILE_PROOF_OF_WORK, "w");
    fprintf(f, "d,time\n");
    while (temps < TEMP_MAX) {
        block->nonce = 0;
        time_initial = clock();
        compute_proof_of_work(block, d);
        time_final = clock();
        temps = ((double) (time_final - time_initial)) / CLOCKS_PER_SEC;
        fprintf(f, "%d,%.2e\n", d, temps);
        printf("d = %d: %.2e\n", d, temps);
        d += 1;
    }
    fclose(f);
    free(sKey);
    free(pKey);
    delete_block(block_read);
    delete_block(block);
    return 0;
}
