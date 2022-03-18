#include "key.h"
#include "rsa.h"
#include <stdio.h>
#include <stdlib.h>

void init_key(Key *key, int64 val, int64 n) {
    key->n   = n;
    key->val = val;
}

void init_pair_keys(Key *pKey, Key *sKey, int low_size, int up_size) {
    // Generation de cle:
    int64 p = random_prime_number(low_size, up_size, 5000);
    int64 q = random_prime_number(low_size, up_size, 5000);
    printf("p=%lld, q=%lld\n", p, q);
    int64 n, s, u;
    generate_key_values(p, q, &n, &s, &u);
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

char *key_to_str(Key *key) {
    char *out = (char *) malloc(64 * sizeof(char));
    sprintf(out, "(%lld,%lld)", key->n, key->val);
    return out;
}

Key *str_to_key(char *str) {
    Key * key = (Key *) malloc(sizeof(Key));
    int64 n, val;
    sscanf(str, "(%lld,%lld)", &val, &n);
    init_key(key, val, n);
    return key;
}