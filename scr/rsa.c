#include "rsa.h"
#include "prime.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**permet de generer la cle publique pkey = (s, n) et la cle secrete skey = (u,
 * n), a partir des nombres premiers p et q, en suivant le protocole RSA.*/
void generate_key_values(long p, long q, long *n, long *s, long *u) {
    *n = p * q;
    long S, T = (p - 1) * (q - 1), U, V, num = 0;
    do {
        if (num++ >= (1 << 16)) exit(2);
        S = rand_long(0, T);
    } while (extended_gcd(S, T, &U, &V) != 1);
    if (U < 0) U = U + T;
    *s = S;
    *u = U;
}

/**chiﬀre la chaıne de caracteres chaine avec la cle publique pKey = (s, n).
 * la fonction convertit chaque caractere en un entier de type int (sauf le
 caractere special '\0'),
 * et retourne le tableau de long obtenu enchiﬀrant ces entiers*/
long *encrypt(char *chaine, long s, long n) {
    int i = -1;
    long *l = malloc(sizeof(long) * strlen(chaine));
    if (!l) exit(3);
    while (chaine[++i] != '\0') {
        l[i] = modpow((int) chaine[i], s, n);
    }
    return l;
}

/**dechiﬀre un message a l'aide de la cle secrete skey = (u, n),
 * en connaissant la taille du tableau d'entiers.
 * Cette fonction renvoie la chaˆıne de caracteres obtenue.*/
char *decrypt(long *crypted, int size, long u, long n) {
    char *d = (char *) malloc(sizeof(char) * (size + 1));
    if (!d) exit(3);
    for (int i = 0; i < size; i++) {
        d[i] = modpow(crypted[i], u, n);
    }
    d[size] = '\0';
    return d;
}

void print_long_vector(long *result, int size) {
    printf("Vector:…[");
    for (int i = 0; i < size; i++) {
        printf("%ld-\t", result[i]);
    }
    printf("]\n");
}

long extended_gcd(long s, long t, long *u, long *v) {
    if (t == 0) {
        *u = 1;
        *v = 0;
        return s;
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t, s % t, &uPrim, &vPrim);
    *u = vPrim;
    *v = uPrim - (s / t) * vPrim;
    return gcd;
}