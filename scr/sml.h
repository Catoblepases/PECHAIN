#ifndef __SIMULATION__
#define __SIMULATION__
#include "blo_t.h"
#include "lck.h"
#include "hash.h"
void submit_vote(Protected *p);
void create_block(CellTree *tree, Key *author, int d);
void add_block(int d, char *name);
// LECTURE DE L’ARBRE ET CALCUL DU GAGNANT
CellTree *read_tree();
Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);
void Simulation(int d,int sizeC,int sizeV);
#endif