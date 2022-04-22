#include "key.h"
#include "rsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Initialiser une clé déjà allouée*/
void init_key(Key *key, long val, long n) {
    key->n = n;
    key->val = val;
}

int compare_key(Key *key1, Key *key2) {
    if (!key1 || !key2) return 0;
    return (key1->n == key2->n) && (key1->val == key2->val);
}

/*Initialiser une clé publique et une clé secrète (déjà allouées) en utilisant le protocole RSA.*/
void init_pair_keys(Key *pKey, Key *sKey, int low_size, int up_size) {
    // Generation de cle:
    long p = random_prime_number(low_size, up_size, 5000);
    long q = random_prime_number(low_size, up_size, 5000);
    long n, s, u;
    generate_key_values(p, q, &n, &s, &u);
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

/*Passer d’une variable de type Key à sa représentation sous forme de chaîne de caractères.*/
char *key_to_str(Key *key) {
    if (key == NULL) {
        return strdup("null");
    }
    char *out = (char *) malloc(1 << 8 * sizeof(char));
    if (!out) exit(3);
    sprintf(out, "(%ld,%ld)", key->n, key->val);
    return out;
}

/**Le passage d'une variable clé à sa représentation sous forme de chaîne de caractères avec une variable locale
 * statique signifie qu'aucune mémoire n'est libérée, mais que chaque appel à la fonction écrase le résultat de l'appel
 * précédent. */
char *key_to_str_static(Key *key) {
    static char out[1 << 16];
    if (key == NULL) {
        strcpy(out, "null");
    } else {
        sprintf(out, "(%ld,%ld)", key->n, key->val);
    }
    return out;
}

/*Passer d'une chaîne de caractères à sa représentation sous forme de variable de type Key.*/
Key *str_to_key(char *str) {
    Key *key = (Key *) malloc(sizeof(Key));
    if (!key) exit(3);
    long n = 0, val = 0;
    if (sscanf(str, "(%ld,%ld)", &n, &val) >= 2) {
        init_key(key, val, n);
        return key;
    }
    return NULL;
}

/*Passer d'une chaîne de caractères à sa représentation sous forme de variable de type Key.*/
Key *str_to_key_static(char *str) {
    static Key *key;
    if (sscanf(str, "(%ld,%ld)", &(key->val), &(key->n)) >= 2) {
        return key;
    }
    return NULL;
}