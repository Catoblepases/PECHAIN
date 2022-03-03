#include "rsa.h"
#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int   i = -1;
    long *l = malloc(sizeof(long) * strlen(chaine));
    while (chaine[++i] != '\0') {
        l[i] = modpow((long) chaine[i], s, n);
    }
    return l;
}
char *decrypt(long *crypted, int size, long u, long n) {
    int   i = -1;
    char *d = malloc(sizeof(char) * (size + 1));
    while (++i < size) {
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
int main() {
    // Generation de cle:
    long p = random_prime_number(15, 16, 5000);
    long q = random_prime_number(15, 16, 5000);
    printf("p=%ld, q=%ld\n", p, q);
    long n, s, u;
    generate_key_values(p, q, &n, &s, &u);
    printf("cle. publique.=.(%1d,-% ld)-\n", s, n);
    printf("cle-privee.=(% ld,%1d)-\n", u, n);
    char message[1000] = "Hello";
    int  len           = strlen(message);
    // Chiffrement:
    long *crypted = encrypt(message, s, n);
    printf("Initial. message:.%s.\n", message);
    printf("Encoded. representation.:…\n");
    print_long_vector(crypted, len);
    // Dechiffrement
    char *decoded = decrypt(crypted, len, u, n);
    printf("Decoded:%s\n", decoded);
    return 0;
}