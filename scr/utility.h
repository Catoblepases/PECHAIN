#ifndef __UTILITY__
#define __UTILITY__

// Constantes
#define NB_KEYS 100    // Nombre d'électeurs
#define NB_CANDIDATS 10 // Nombre de candidats
#define NB_BLOCK_DECLARATIONS 10   // Nombre de declaration dans un bloc
#define LOW_SIZE 5
#define UP_SIZE 10
#define NB_TEST_MILLER 256
#define VALUE_D 3

// Nom du fichier de stockage
#define FILE_KEYS "./temp/keys.txt"
#define FILE_CANDIDATES "./temp/candidates.txt"
#define FILE_DECLARATIONS "./temp/declarations.txt"
#define FILE_BLOCKS "./temp/blocks.txt"
#define DIR_BLOCK "./blockchain/"
#define FILE_BLOCK_PREFIX "block"
#define FILE_BLOCK_SUFFIX ".txt"
#define FILE_PENDING_VOTES "./temp/Pending_votes.txt"
#define FILE_PENDING_BLOCK "./temp/Pending_block.txt"

// Nom du fichier pour tester
#define FILE_BLOCK_DECLARATIONS "./temp/block_declarations.txt"
#define FILE_PROOF_OF_WORK "./temp/proof_of_work.csv"
#define FILE_DECLARATIONS_TEST "./temp/declarations_test.txt"
#define FILE_BLOCKS_TEST "./temp/blocks_test.txt"

// Constantes de test
#define NB_KEYS_TEST 10    // Nombre d'électeurs
#define NB_CANDIDATS_TEST 2 // Nombre de candidats
#define NB_BLOCKS 10   // Nombre de bloc pour tester
#define UP_SIZE_TEST_MOD_POW 1<<8
#define TEMP_MAX 0.2

// Macros créées pour faciliter les tests
#define print_with_sepatator(...) printf("-----------%s-----------\n", __VA_ARGS__)

#endif