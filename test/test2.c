#include <math.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    const char    *s = "Rosetta. code";
    unsigned char *d = SHA256(s, strlen(s), 0);
    for (unsigned int j = 0; j < SHA256_DIGEST_LENGTH; j++)
        printf("%02hhX ", d[j]);
    putchar('\n');
    return 0;
}
