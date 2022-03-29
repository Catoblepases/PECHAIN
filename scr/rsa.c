#include "rsa.h"
#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long extended_gcd(long s, long t, long *u, long *v) {
    if (t == 0) {
        *u = 1;
        *v = 0;
        return s;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t, s % t, &uPrim, &vPrim);
    *u       = vPrim;
    *v       = uPrim - (s / t) * vPrim;
    return gcd;
}

void generate_key_values(long p, long q, long *n, long *s, long *u) {
    *n = p * q;
    long S, T = (p - 1) * (q - 1), U, V, num = 0;
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

long *encrypt(char *chaine, long s, long n) {
    int   i = -1, m;
    long *l = malloc(sizeof(long) * strlen(chaine));
    while (chaine[++i] != '\0') {
        m    = chaine[i];
        l[i] = modpow(m, s, n);
    }
    return l;
}

char *decrypt(long *crypted, int size, long u, long n) {
    char *d = (char *) malloc(sizeof(char) * (size + 1));
    d[size] = '\0';
    for (int i = 0; i < size; i++) {
        d[i] = modpow(crypted[i], u, n);
        // printf("(%d-%ld) ", d[i], tmp);
    }
    return d;
}

void print_long_vector(long *result, int size) {
    printf("Vector:…[");
    for (int i = 0; i < size; i++) {
        printf("%ld-\t", result[i]);
    }
    printf("]\n");
}
