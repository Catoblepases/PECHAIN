#include "../scr/rsa.h"
#include "../scr/libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    srand(time(NULL));
    // Generation de cle:
    int64 p = random_prime_number(15, 16, 500);
    int64 q = random_prime_number(15, 16, 500);
    printf("p=%lld, q=%lld\n", p, q);
    int64 n, s, u;
    generate_key_values(p, q, &n, &s, &u);
    printf("cle. publique.=.(%lld,-%lld)-\n", s, n);
    printf("cle-privee.=(%lld,%lld)-\n", u, n);
    char message[1000] = "Hello";
    int  len           = strlen(message);
    // Chiffrement:
    int64 *crypted = encrypt(message, s, n);
    printf("Initial. message:.%s.\n", message);
    printf("Encoded. representation.:…\n");
    print_long_vector(crypted, len);
    // Dechiffrement
    char *decoded = decrypt(crypted, len, u, n);
    printf("Decoded:%s\n", decoded);
    return 0;
}