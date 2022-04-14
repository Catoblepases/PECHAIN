#include "blo.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *str_to_SHA256(const char *str) {
    unsigned char *d = SHA256((const unsigned char *) str, strlen((const char *) str), 0);
    char *out = malloc(sizeof(char) * (strlen((const char *) str) * 2 + 1));
    out[strlen(str) * 2] = '\0';
    for (unsigned int j = 0; j < SHA256_DIGEST_LENGTH; j++)
        sprintf(out, "%02x", d[j]);
    return (unsigned char *) out;
}

/**Ecrire dans fichier le bloc dans l'ordre :
 * - Clef de l'auteur.
 * - Le hachage du bloc.
 * - Le hachage du bloc precedent.
 * - leurs representants votants.
 * - proof of work. */
void write_block(char *fileName, Block *block) {
    FILE *f = fopen(fileName, "w");
    char buf[1 << 16], *tmp;
    tmp = key_to_str(block->author);
    sprintf(buf, "%s\n%s\n%d\n%s\n", tmp, block->hash, block->nonce, block->previous_hash);
    fputs(buf, f);
    free(tmp);
    CellProtected *lcp = block->votes;
    while (lcp) {
        tmp = protected_to_str(lcp->data);
        fputs(tmp, f);
        fputs("\n", f);
        free(tmp);
        lcp = lcp->next;
    }
    fclose(f);
}

Block *read_block(char *fileName) {
    FILE *f = fopen(fileName, "w");
    Block *block = (Block *) malloc(sizeof(Block));
    char buf[1 << 16];
    int idx = 0;
    while (fgets(buf, 1 << 16, f) && (idx <= 3)) {
        switch (idx++) {
        case 0: block->author = str_to_key(buf); break;
        case 1: block->hash = (unsigned char *) strdup(buf); break;
        case 2: sscanf(buf, "%d", &(block->nonce)); break;
        case 3: block->previous_hash = (unsigned char *) strdup(buf); break;
        default: break;
        }
    }
    block->votes = read_protected(fileName);
    fclose(f);
    return block;
}

/**Genère une chaîne representant le bloc.
 * La chaîne contient dans l'ordre :
 * - Clef de l'auteur.
 * - Le hachage du bloc precedent.
 * - leurs representants votants.
 * - proof of work. */
char *block_to_str(Block *block) {
    char *buf = (char *) malloc(sizeof(char) * 1 << 16), *tmp;
    tmp = key_to_str(block->author);
    sprintf(buf, "%s %s %d ", tmp, block->previous_hash, block->nonce);
    free(tmp);
    CellProtected *lcp = block->votes;
    while (lcp) {
        tmp = protected_to_str(lcp->data);
        sprintf(buf, "%s-", tmp);
        free(tmp);
        lcp = lcp->next;
    }
    sprintf(buf, " %d", block->nonce);
    return buf;
}

void compute_proof_of_work(Block *B, int d) {
    B->nonce = 0;
    while (!verify_block(B, d)) {
        B->nonce++;
    }
}

int verify_block(Block *block, int d) {
    char *str = block_to_str(block);
    unsigned char *c = str_to_SHA256(str);
    for (int i = 0; i < d; i++) {
        if (c[i] != '0') return 0;
    }
    free(str);
    return 1;
}

/**Cette fonction ne libere pas la memoire associee au champs author.
 * Pour la liste chaınee votes, on libere les elements de la liste chaınee (CellProtected),
 * mais pas leur contenu (Protected). */
void delete_block(Block *b) {
    free(b->hash);
    free(b->previous_hash);
    CellProtected *LCP = b->votes, *tmp;
    while (LCP) {
        tmp = LCP->next;
        free(LCP);
        LCP = tmp;
    }
}