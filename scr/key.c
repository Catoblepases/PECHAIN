#include "key.h"
#include "rsa.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Initialiser une clé déjà allouée*/
void init_key(Key *key, long val, long n) {
    key->n   = n;
    key->val = val;
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
    sprintf(out, "(%ld,%ld)", key->n, key->val);
    return out;
}

/*Passer d'une chaîne de caractères à sa représentation sous forme de variable de type Key.*/
Key *str_to_key(char *str) {
    Key *key = (Key *) malloc(sizeof(Key));
    long n = 0, val = 0;
    if (sscanf(str, "(%ld,%ld)", &n, &val) >= 2) {
        init_key(key, val, n);
        return key;
    }
    return NULL;
}