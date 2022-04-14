#include "scr/rsa.h"
#include "scr/prime.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));
    // Generation de cle:
    long p = random_prime_number(15, 16, 500);
    long q = random_prime_number(15, 16, 500);
    printf("p=%ld, q=%ld\n", p, q);
    long n, s, u;
    generate_key_values(p, q, &n, &s, &u);
    printf("cle. publique.=.(%ld,-%ld)-\n", s, n);
    printf("cle-privee.=(%ld,%ld)-\n", u, n);
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
    // free
    free(crypted);
    free(decoded);
    return 0;
}