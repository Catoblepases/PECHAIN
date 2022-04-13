#include "sml.h"
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
    CellTree *lastNode = last_node(tree);
    block->author = author;
    block->nonce = 0;
    block->votes = lcp;
    block->previous_hash = NULL;
    char *buf = block_to_str(block);
    block->hash = str_to_SHA256(buf);
    system("rm Pending_votes.txt");
    compute_proof_of_work(block, d);
    write_block("Pending_block", block);
    add_child(lastNode, create_node(block));
}

void add_block(int d, char *name) {
    char path[1 << 16];
    strcpy(path, "./Blockchain/");
    strcat(path, name);
    FILE *fWrite = fopen(path, "w");
    FILE *fRead = fopen("Pending_block", "r");
    char buf[1 << 16];
    while (fgets(buf, 1 << 16, fRead) > 0) {
        fputs(buf, fWrite);
    }
    system("rm Pending_block");
    fclose(fWrite);
    fclose(fRead);
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
        cell[i] = read_block(fileName[i]);
    }
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < idx; j++) {
            if (strcmp(cell[i]->block->hash, cell[j]->block->hash)) {
                add_child(cell[i], cell[j]);
            }
        }
    }
    for (int i = 0; i < idx; i++) {
        if (!cell[i]->father) return cell[i];
    }
}

Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);
