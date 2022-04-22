#include "sml.h"
#include "blo_t.h"
#include "hash.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void submit_vote(Protected *p) {
    if (!p) return;
    FILE *f = fopen("Pending_votes.txt", "a+");
    char *str = protected_to_str(p);
    fprintf(f, "%s\n", str);
    free(str);
    fclose(f);
}

void create_block(CellTree *tree, Key *author, int d) {
    Block *block = (Block *) malloc(sizeof(Block));
    CellProtected *lcp = read_protected("Pending_votes.txt");

    // print_list_protected(lcp);

    block->author = author;
    block->nonce = 0;
    block->votes = lcp;
    block->previous_hash = NULL;
    block->hash = NULL;

    CellTree *last = last_node(tree);
    if (!last) {
        block->previous_hash = NULL;
    } else {
        block->previous_hash = last->block->hash;
    }

    system("rm Pending_votes.txt");
    compute_proof_of_work(block, d);
    write_block("Pending_block", block);

    // printf("create node\n");
    CellTree *new = create_node(block);
    if ((tree) && (tree->block)) {
        // printf("last node\n");
        CellTree *lastNode = last_node(tree);
        // printf("add child\n");
        add_child(lastNode, new);
    } else {
        tree->block = block;
    }
}

void add_block(int d, char *name) {
    char path[1 << 16];
    sprintf(path, "./Blockchain/%s.txt", name);
    Block *block = read_block("Pending_block");

    if ((!block) || (!verify_block(block, d))) exit(5);

    write_block(path, block);
    system("rm Pending_block");
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
                fileName[idx] = (char *) malloc(sizeof(char) * 1 << 8);
                sprintf(fileName[idx++], "./Blockchain/%s", dir->d_name);
                printf("%s\n", fileName[idx - 1]);
            }
        }
        closedir(rep);
    }
    printf("finish dir\n");
    CellTree *cell[idx];
    for (int i = 0; i < idx; i++) {
        printf("%s\n", fileName[i]);
        cell[i] = create_node(read_block(fileName[i]));
        print_node(cell[i]);
    }
    printf("\nfinish block\n");
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < idx; j++) {
            if (!(cell[j]->block->previous_hash)) continue;
            if (strcmp(cell[i]->block->hash, cell[j]->block->previous_hash) == 0) {
                printf("add child %d %d\n", i, j);
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
    CellProtected *lcp = longestList(tree);
    print_list_protected(lcp);
    int n = verify_for_list_protected(&lcp);
    printf("signature invalide :%d\n", n);
    Key *key = compute_winner(lcp, candidates, voters, sizeC, sizeV);
    return key;
}

void Simulation(int d,int sizeC,int sizeV) {
    // Générer des volontaires
    Key *author = (Key *) malloc(sizeof(Key));
    Key *sKey = (Key *) malloc(sizeof(Key));
    init_pair_keys(author, sKey, 1 << 3, 1 << 8);
    // Générer des datas
    // generate_random_data(sizeV, sizeC);
    // Lire datas
    CellProtected *cellp = read_protected("declarations.txt");
    CellKey *voters = read_public_keys("keys.txt");
    CellKey *candidates = read_public_keys("candidates.txt");
    FILE *f = fopen("declarations.txt", "r");
    char buf[1 << 16];
    int idx = 0;
    CellTree *tree = create_node(NULL);
    char *fileName;
    char fn[] = "block";
    Protected *pr;
    while (fgets(buf, 1 << 16, f) > 0) {
        pr = str_to_protected(buf);
        if (!pr) continue;
        submit_vote(pr);
        // printf("read protection %s\n", protected_to_str(pr));
        if (idx++ % 10 == 9) {
            fileName = (char *) malloc(sizeof(char) * (1 << 8));
            if (!fileName) exit(3);
            sprintf(fileName, "%s%d", fn, (idx / 10));
            printf("create block %s\n", fileName);

            create_block(tree, author, d);
            add_block(d, fileName);
            free(fileName);
        }
    }

    CellTree *tr = read_tree();
    print_tree(tr);
    compute_winner_BT(tr, candidates, voters, sizeC, sizeV);

    delete_tree(tr);
    delete_list_key(voters);
}