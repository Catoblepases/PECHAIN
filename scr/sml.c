#include "sml.h"
#include "utility.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Permettant à un citoyen de soumettre un vote, autrement d'ajouter son vote à la fin du fichier  "Pending votes.txt".*/
void submit_vote(Protected *p) {
    if (!p) return;
    FILE *f = fopen(FILE_PENDING_VOTES, "a+");
    if (!f) exit(3);
    char *str = protected_to_str(p);
    fprintf(f, "%s\n", str);
    free(str);
    fclose(f);
}

CellTree *init_tree(Key *author, int d) {
    CellTree *tree = create_node(init_block(author, read_protected(FILE_PENDING_VOTES)));
    remove(FILE_PENDING_VOTES);
    compute_proof_of_work(tree->block, d);
    write_block(FILE_PENDING_BLOCK, tree->block);
    return tree;
}

/*
— Crée un bloc valide contenant les votes en attente dans le fichier ”Pending votes.txt”,
— Supprime le fichier ”Pending votes.txt” après avoir créé le bloc,
— et écrit le bloc obtenu dans un fichier appelé "Pending block".
*/
void create_block(CellTree *tree, Key *author, int d) {
    Block *block = init_block(author, read_protected(FILE_PENDING_VOTES));
    CellTree *lastNode = last_node(tree);
    if (!lastNode) exit(4);
    block->previous_hash = (unsigned char *) strdup((char *) lastNode->block->hash);
    compute_proof_of_work(block, d);
    CellTree *new = create_node(block);
    add_child(lastNode, new);
    write_block(FILE_PENDING_BLOCK, block);
    remove(FILE_PENDING_VOTES);
}

/*vérifie que le bloc représenté par le fichier  "Pending block" est valide.
Si c'est le cas, la fonction crée un fichier appelé name représentant le bloc, puis l'ajoute dans le répertoire
"Blockchain". Dans tous les cas, le fichier  "Pending block" est ensuite supprimé.*/
void add_block(int d, char *name) {
    char path[1 << 16];
    sprintf(path, "%s%s", DIR_BLOCK, name);
    Block *block = read_block(FILE_PENDING_BLOCK);
    if ((block) && (verify_block(block, d))) write_block(path, block);

    remove(FILE_PENDING_VOTES);
    delete_block(block);
}

// int strcmp_unsigned(const unsigned char *s1, const unsigned char *s2) {
//     unsigned char *p1 = (unsigned char *) s1;
//     unsigned char *p2 = (unsigned char *) s2;
//     while ((*p1) && (*p1 == *p2)) {
//         ++p1;
//         ++p2;
//     }
//     return (*p1 - *p2);
// }

// LECTURE DE L’ARBRE ET CALCUL DU GAGNANT
/*Construire l'arbre correspondant aux blocs contenus dans le répertoire  "Blockchain".*/
CellTree *read_tree() {
    DIR *rep = opendir(DIR_BLOCK);
    char *fileName[1 << 8];
    int idx = 0;
    // Lire les fichiers d'un dossier
    if (!rep) exit(3);
    struct dirent *dir;
    while ((dir = readdir(rep))) {
        if ((strcmp(dir->d_name, ".") != 0) && (strcmp(dir->d_name, "..") != 0)) {
            fileName[idx] = (char *) malloc(sizeof(char) * 1 << 8);
            sprintf(fileName[idx++], "%s%s", DIR_BLOCK, dir->d_name);
            printf("%s\n", fileName[idx - 1]);
        }
    }
    closedir(rep);
    printf("finish dir\n");
    // Créer des noeuds
    // On crée un noeud de l'arbre pour chaque bloc contenu dans le répertoire,
    // et on stocke tous les noeuds dans un tableau T de type CellTree**.
    CellTree *cell[idx];
    for (int i = 0; i < idx; i++) {
        printf("%s\n", fileName[i]);
        cell[i] = create_node(read_block(fileName[i]));
    }
    printf("\nfinish block\n");
    // On parcourt le tableau T de noeuds, et pour chaque noeud T[i], on recherche tous ses fils T[j] ;
    // ce sont les noeuds contenant un bloc dont le champs previous hash est égal au champs hash du bloc du noeud T[i].
    for (int i = 0; i < idx; i++) {
        for (int j = 0; j < idx; j++) {
            if (!(cell[j]->block->previous_hash)) continue;
            if (strcmp((char *) cell[i]->block->hash, (char *) cell[j]->block->previous_hash) == 0) {
                // Chaque fils T[j] est ajouté à la liste des fils du noeud T[i] .
                printf("add child %d %d\n", i, j);
                add_child(cell[i], cell[j]);
            }
        }
    }
    for (int i = 0; i < idx; i++) {
        free(fileName[i]);
    }
    // On parcourt une dernière fois le tableau T pour trouver la racine de l’arbre et la retourner.
    for (int i = 0; i < idx; i++) {
        // noeud dont le champs father est égal à NULL.
        if (!cell[i]->father) return cell[i];
    }
    return NULL;
}

/*Détermine le gagnant de l'élection en se basant sur la plus longue chaîne de l'arbre.*/
Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV) {
    // Extraction de la liste des déclarations de vote
    CellProtected *lcp = longestList(tree);
    // Suppression des déclarations de vote non valides
    int n = verify_for_list_protected(&lcp);
    printf("signature invalide :%d\n", n);
    // Calcule le vainqueur de l'élection
    Key *key = compute_winner(lcp, candidates, voters, sizeC, sizeV);
    delete_list_protected(lcp);
    return key;
}

void Simulation(int d, int sizeC, int sizeV) {
    // Générer des volontaires
    Key *author = (Key *) malloc(sizeof(Key));
    Key *sKey = (Key *) malloc(sizeof(Key));
    init_pair_keys(author, sKey, 1 << 3, 1 << 8);
    // 1. Generation d’un probleme de vote avec 1000 citoyens et 5 candidats
    generate_random_data(sizeV, sizeC);
    // 2. Lecture des declarations de vote (fonction read protected), des candidats et des citoyens
    CellProtected *decl = read_protected(FILE_DECLARATIONS);
    CellKey *voters = read_public_keys(FILE_KEYS);
    CellKey *candidates = read_public_keys(FILE_CANDIDATES);
    CellTree *tree = NULL;
    int idx = 0;
    char *fileName;
    CellProtected *tmp = decl;
    while (tmp) {
        // 3. Soumission de tous les votes (fonction submit vote)
        submit_vote(tmp->data);
        // 4. la creation d’un bloc valide tous les 10 votes soumis
        if ((idx++ % NB_BLOCK_DECLARATIONS == NB_BLOCK_DECLARATIONS - 1) || (tmp->next == NULL)) {
            if (!(tmp->next)) idx += 10;
            fileName = (char *) malloc(sizeof(char) * (1 << 8));
            if (!fileName) exit(3);
            sprintf(fileName, "%s%d%s", FILE_BLOCK_PREFIX, (idx / NB_BLOCK_DECLARATIONS), FILE_BLOCK_SUFFIX);
            printf("create block %s\n", fileName);
            if (!tree) {
                tree = init_tree(author, d);
            } else {
                create_block(tree, author, d);
            }
            // 5. l’ajout du bloc dans la blockchain (fonction add block).
            add_block(d, fileName);
            free(fileName);
        }
        tmp = tmp->next;
    }
    delete_tree(tree);
    delete_list_protected(decl);
    // 6. Lecture (fonction read tree) et afchage (fonction print tree) de l’arbre fnal.
    CellTree *tr = read_tree();
    print_tree(tr);
    // 7.Calcul et afchage du gagnant (fonction compute winner BT).
    Key *key = compute_winner_BT(tr, candidates, voters, sizeC, sizeV);
    printf("winner of this election is %s\n", key_to_str_static(key));

    delete_tree_partial(tr);
    delete_list_key(voters);
    delete_list_key(candidates);
    free(author);
    free(sKey);
}