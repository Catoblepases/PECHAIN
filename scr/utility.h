#ifndef __UTILITY__
#define __UTILITY__

#define LOW_SIZE 5          
#define UP_SIZE 10          
#define NB_TEST_MILLER 256 

// Créer des données
#define NB_KEYS 200    // Nombre d'électeurs
#define NB_CANDIDATS 4 // Nombre de candidats

// Nom du fichier de stockage
#define FILE_KEYS "./temp/keys.txt"
#define FILE_CANDIDATES "./temp/candidates.txt"
#define FILE_DECLARATIONS "./temp/declarations.txt"
#define FILE_BLOCKS "./temp/blocks.txt"
#define DIR_BLOCK "./blockchain/"
#define FILE_BLOCK_PREFIX "block"
#define FILE_BLOCK_SUFFIX ".txt"
#define FILE_PENDING_VOTES "./temp/Pending_votes.txt"
#define FILE_PENDING_BLOCK "./temp/Pending_block"

// Nom du fichier pour tester
#define FILE_BLOCK_DECLARATIONS "./temp/block_declarations.txt"
#define FILE_PROOF_OF_WORK "./temp/proof_of_work.csv"
#define FILE_BLOCKS_TEST "./temp/blocks_test.txt"
#define NB_BLOCKS 10
#define NB_BLOCK_DECLARATIONS 10
#define print_with_sepatator(...) printf("-----------%s-----------\n",__VA_ARGS__)

#endif