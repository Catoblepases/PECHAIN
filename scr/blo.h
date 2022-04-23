#ifndef __BLOCK__
#define __BLOCK__
#include "key.h"
#include "lcp.h"

/* un bloc contiendra :
— La clé publique de son créateur.
— Une liste de déclarations de vote.
— La valeur hachée du bloc.
— La valeur hachée du bloc précédent.
— Une preuve de travail.*/
typedef struct block {
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
} Block;

unsigned char *str_to_SHA256(const char *str);
void write_block(char *fileName, Block *block);
Block *read_block(char *fileName);
char *block_to_str(Block *block);
void compute_proof_of_work(Block *B, int d);
int verify_block(Block *, int d);
void delete_block(Block *b);
void free_block(Block *b);
int verify_and_update_block(Block *block, int d);
Block *create_random_block(Key *author);
Block *init_block(Key *author, CellProtected *lcp);
#endif