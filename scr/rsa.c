#include "rsa.h"
#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int64 extended_gcd(int64 s, int64 t, int64 *u, int64 *v) {
    if (t == 0) {
        *u = 1;
        *v = 0;
        return s;
    }
    int64 uPrim, vPrim;
    int64 gcd = extended_gcd(t, s % t, &uPrim, &vPrim);
    *u        = vPrim;
    *v        = uPrim - (s / t) * vPrim;
    return gcd;
}

void generate_key_values(int64 p, int64 q, int64 *n, int64 *s, int64 *u) {
    *n = p * q;
    int64 S, T = (p - 1) * (q - 1), U, V, num = 0;
    srand(0);
    S = rand_long(0, T);
    while ((extended_gcd(S, T, &U, &V) != 1)) {
        if (num++ >= (1 << 16)) {
            printf("erreur!\n");
            exit(-1);
        }
        S = rand_long(0, T);
    }
    *s = S;
    *u = U;
}

int64 *encrypt(char *chaine, int64 s, int64 n) {
    int    i = -1, m;
    int64 *l = malloc(sizeof(int64) * strlen(chaine));
    while (chaine[++i] != '\0') {
        m    = chaine[i];
        l[i] = modpow(m, s, n);
    }
    return l;
}

char *decrypt(int64 *crypted, int size, int64 u, int64 n) {
    char *d = (char *) malloc(sizeof(char) * (size + 1));
    d[size] = '\0';
    for (int i = 0; i < size; i++) {
        d[i] = modpow(crypted[i], u, n);
        // printf("(%d-%lld) ", d[i], tmp);
    }
    return d;
}

void print_long_vector(int64 *result, int size) {
    printf("Vector:…[");
    for (int i = 0; i < size; i++) {
        printf("%lld-\t", result[i]);
    }
    printf("]\n");
}
