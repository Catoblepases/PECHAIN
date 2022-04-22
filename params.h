#ifndef __PARAMS__
#define __PARAMS__

// GENERALS
#define LOW_SIZE 5               // Puissance de 2 minimal qui borne nos nombres premiers
#define UP_SIZE 10               // Puissance de 2 maximal qui borne nos nombres premiers
#define NB_TEST_MILLER_RABIN 256 // Nombre de temoin qu'on test

// EXERCICE 1
#define NB_TEST_MODPOW 100               // Pour la comparaison des modpow
#define ECART_TOUR_EXPONENTIATION 100000 // Pour la comparaison des modpow
#define NB_PREMIER_MILLER_RABIN 20       // Nombre de nombre premier genere aleatoirement puis tester dans l'ex1

// EXERCICE 2
#define NB_TEST_EX2 20000 // Nombre de test encrypt/decrypt
#define TAILLE_CHAINE 16   // Taille des chaines generee aleatoirement pour les tests

// EXERCICE 3
#define NB_TEST_EX3 1000

// EXERCICE 4
#define NB_KEYS 200    // Nombre de personnes enregistre aux elections / declaration de vote
#define NB_CANDIDATS 4 // Nombre de candidats parmis les personnes enregistre

// EXERCICE 6
#define NB_TEST_FINDPOSITION 20

// EXERCICE 8
#define FILE_TEST_KEYS "test_ex8_keys.txt"
#define FILE_TEST_CANDIDATES "test_ex8_candidates.txt"
#define FILE_TEST_DECLARATIONS "test_ex8_declarations.txt"

// EXERCICE 9
#define MOCK_NB_VOTERS 50
#define MOCK_NB_CANDIDATS 2
#define NB_VOTE_PER_BLOCK 10
#define D_VALUE 2

// FICHIERS
#define FILE_KEYS "keys.txt"
#define FILE_CANDIDATES "candidates.txt"
#define FILE_DECLARATIONS "declarations.txt"
#define FILE_COMPARAISON_EXPONENTIATION "comparaison_exponentiation.txt"
#define FILE_BLOCKS "blocks.txt"
#define FILE_BLOCKS_TEST "blocks_test.txt"

// FICHIERS EX9
#define DIR_BLOCKCHAIN "./blockchain/"
#define FILE_PENDING_VOTES "./blockchain/pending/pending_votes.txt"
#define FILE_PENDING_BLOCK "./blockchain/pending/pending_block.txt"


#endif