#include "blo.h"
#include "utility.h"
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char *str_to_SHA256(const char *str) {
    unsigned char *d = SHA256((const unsigned char *) str, strlen((const char *) str), 0);
    char *out = malloc(sizeof(char) * (strlen((char *) str) * 2 + 1));
    char *tmp[1 << 4];
    for (unsigned int j = 0; j < SHA256_DIGEST_LENGTH; j++) {
        sprintf(tmp, "%02x", d[j]);
        if (j == 0) {
            strcpy(out, tmp);
        } else {
            strcat(out, tmp);
        }
    }
    return (unsigned char *) out;
}

/**Ecrire dans fichier le bloc dans l'ordre :
 * - Clef de l'auteur.
 * - Le hachage du bloc.
 * - proof of work.
 * - Le hachage du bloc precedent.
 * - leurs representants votants.*/
void write_block(char *fileName, Block *block) {
    FILE *f = fopen(fileName, "w");
    if (!block) return;
    char *tmp;
    fprintf(f, "%s\n%s\n%d\n", key_to_str_static(block->author), block->hash, block->nonce);
    if (block->previous_hash) fprintf(f, "%s\n", block->previous_hash);

    CellProtected *lcp = block->votes;
    while (lcp) {
        tmp = protected_to_str(lcp->data);
        fprintf(f, "%s\n", tmp);
        free(tmp);
        lcp = lcp->next;
    }
    fclose(f);
}

/** Éviter l'inexistence de la fonction strndup sur certains systèmes */
char *_strndup(char *str, int size) {
    size_t len = strnlen(str, size);
    char *new = (char *) malloc(len + 1);
    if (new == NULL) return NULL;
    new[len] = '\0';
    return (char *) memcpy(new, str, len);
}

unsigned char *read_hash(char *buf) {
    if (strncmp(buf, "(null)", strlen("(null)")) == 0) {
        return NULL;
    }
    return (unsigned char *) _strndup(buf, strlen(buf) - 1);
}

Block *read_block(char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (!f) return NULL;
    Block *block = (Block *) malloc(sizeof(Block));
    char buf[1 << 16];
    int idx = 0;
    while (fgets(buf, 1 << 16, f) && (idx <= 3)) {
        switch (idx++) {
        case 0: block->author = str_to_key(buf); break;
        case 1: block->hash = read_hash(buf); break;
        case 2: sscanf(buf, "%d", &(block->nonce)); break;
        case 3: block->previous_hash = read_hash(buf); break;
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
    sprintf(buf, "%s %s %d ", key_to_str_static(block->author), block->previous_hash, block->nonce);
    CellProtected *lcp = block->votes;
    while (lcp) {
        tmp = protected_to_str(lcp->data);
        strcat(buf, tmp);
        strcat(buf, "-");
        free(tmp);
        lcp = lcp->next;
    }
    tmp = malloc(sizeof(char) * 1 << 8);
    sprintf(tmp, "%d", block->nonce);
    strcat(buf, tmp);
    return buf;
}

void compute_proof_of_work(Block *B, int d) {
    B->nonce = 0;
    while (!verify_and_update_block(B, d)) {
        B->nonce++;
    }
}

int verify_and_update_block(Block *block, int d) {
    if (block->hash) free(block->hash);
    char *str = block_to_str(block);
    block->hash = str_to_SHA256(str);
    for (int i = 0; i < d; i++) {
        if (block->hash[i] != '0') return 0;
    }
    free(str);
    return 1;
}

int verify_block(Block *block, int d) {
    if (!block->hash) return 0;
    for (int i = 0; i < d; i++) {
        if (block->hash[i] != '0') return 0;
    }
    return 1;
}

/**Cette fonction ne libere pas la memoire associee au champs author.
 * Pour la liste chaınee votes, on libere les elements de la liste chaınee (CellProtected),
 * mais pas leur contenu (Protected). */
void delete_block_partial(Block *b) {
    if (b->hash) free(b->hash);
    if (b->author) free(b->author);
    if (b->previous_hash) free(b->previous_hash);
    CellProtected *lcp = b->votes, *tmp;
    while (lcp) {
        tmp = lcp->next;
        free(lcp);
        lcp = tmp;
    }
    free(b);
}

void delete_block(Block *b) {
    if (b->hash) free(b->hash);
    if (b->author) free(b->author);
    if (b->previous_hash) free(b->previous_hash);
    delete_list_protected(b->votes);
    free(b);
}

Block *create_random_block(Key *author) {
    generate_random_data(100, NB_BLOCK_DECLARATIONS);
    CellProtected *decl = read_protected(FILE_DECLARATIONS);
    Block *block = (Block *) malloc(sizeof(Block));
    block->author = author;
    block->nonce = 0;
    block->votes = decl;
    block->previous_hash = NULL;
    block->hash = NULL;
    return block;
}