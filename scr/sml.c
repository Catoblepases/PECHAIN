#include "sml.h"
#include "blo_t.h"
#include "hash.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void submit_vote(Protected *p) {
    FILE *f = fopen("Pending_votes.txt", "a+");
    char *str = protected_to_str(p);
    fputs(str, f);
    free(str);
    fclose(f);
}

void create_block(CellTree *tree, Key *author, int d) {
    Block *block = (Block *) malloc(sizeof(Block));
    CellProtected *lcp = read_protected("Pending_votes.txt");
    block->author = author;
    block->nonce = 0;
    block->votes = lcp;
    block->previous_hash = NULL;
    char *buf = block_to_str(block);
    block->hash = str_to_SHA256(buf);
    system("rm Pending_votes.txt");
    compute_proof_of_work(block, d);
    write_block("Pending_block", block);
    CellTree *new = create_node(block);
    if (tree->block) {
        CellTree *lastNode = last_node(tree);
        add_child(lastNode, new);
    } else {
        tree->block = block;
    }
}

void add_block(int d, char *name) {
    char path[1 << 16];
    sprintf(path, "./Blockchain/%s", name);
    FILE *fWrite = fopen(path, "w");
    FILE *fRead = fopen("Pending_block", "r");
    Block *block = read_block("Pending_block");
    if ((!block) || (!verify_block(block, 4))) exit(5);
    char buf[1 << 16];
    while (fgets(buf, 1 << 16, fRead)) {
        fputs(buf, fWrite);
    }
    system("rm Pending_block");
    fclose(fWrite);
    fclose(fRead);
}

int strcmp_unsigned(const unsigned char *s1, const unsigned char *s2) {
    unsigned char *p1 = (unsigned char *) s1;
    unsigned char *p2 = (unsigned char *) s2;
    while ((*p1) && (*p1 == *p2)) {
        ++p1;
        ++p2;
    }
    return (*p1 - *p2);
}

// LECTURE DE L’ARBRE ET CALCUL DU GAGNANT
CellTree *read_tree() {
    DIR *rep = opendir("./Blockchain/");
    char *fileName[1 << 8];
    int idx = 0;
    if (rep != NULL) {
        struct dirent *dir;
        while ((dir = readdir(rep))) {
            if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
                fileName[idx] = (char *) malloc(sizeof(char) * 1 << 16);
                sprintf(fileName[idx++], "./Blockchain/%s", dir->d_name);
            }
        }
        closedir(rep);
    }
    CellTree *cell[idx];
    for (int i = 0; i < idx; i++) {
        cell[i] = create_node(read_block(fileName[i]));
    }

    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < idx; j++) {
            if (strcmp_unsigned(cell[i]->block->hash, cell[j]->block->hash)) {
                add_child(cell[i], cell[j]);
            }
        }
    }

    for (int i = 0; i < idx; i++) {
        free(fileName[i]);
    }

    for (int i = 0; i < idx; i++) {
        if (!cell[i]->father) return cell[i];
    }
    return NULL;
}

Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
    CellProtected *lcp = fusionAll(tree);
    verify_for_list_protected(&lcp);
    Key *key = compute_winner(lcp, candidates, voters, sizeC, sizeV);
    delete_cell_protected(lcp);
    return key;
}
