#ifndef __BLOCK__
#define __BLOCK__
#include "key.h"
#include "lcp.h"
typedef struct block {
    Key *author;
    CellProtected *votes;
    unsigned char *hash;
    unsigned char *previous_hash;
    int nonce;
} Block;

unsigned char *str_to_SHA256(const char *str);
void write_block(const char *file_name, Block *block);
Block *read_block(const char *file_name);
char *block_to_str(Block *block);
void compute_proof_of_work(Block *B, int d);
int verify_block(Block *, int d);
void delete_block(Block *b);
void free_block(Block *b);
#endif