#include "key.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>

void init_key(Key *key, long val, long n) {
    key->n   = n;
    key->val = val;
}

void init_pair_keys(Key *pKey, Key *sKey, int low_size, int up_size) {
    // Generation de cle:
    long p = random_prime_number(low_size, up_size, 5000);
    long q = random_prime_number(low_size, up_size, 5000);
    long n, s, u;
    generate_key_values(p, q, &n, &s, &u);
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

char *key_to_str(Key *key) {
    char *out = (char *) malloc(64 * sizeof(char));
    sprintf(out, "(%ld,%ld)", key->n, key->val);
    return out;
}

Key *str_to_key(char *str) {
    Key *key = (Key *) malloc(sizeof(Key));
    long n, val;
    sscanf(str, "(%ld,%ld)", &val, &n);
    init_key(key, val, n);
    return key;
}