#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int is_prime_naive(long p) {
    for (int i = 2; i < p / 2; i++) {
        if (p % i == 0) return 0;
    }
    return 1;
}

long modpow_naive(long a, long m, long n) {
    int res = 1;
    for (int i = 0; i < m; i++) {
        res *= a;
        res = res % n;
    }
    return res;
}

int modpow(long a, long m, long n) {
    if (m == 1) return a % n;
    return modpow(a * a, m / 2, n);
}
int witness(long a, long b, long d, long p) {
    long x = modpow(a, d, p);
    if (x == 1) {
        return 0;
        for (long i = 0; i < b; i++) {
            if (x == p - 1) {
                return 0;
            }
            x = modpow(x, 2, p);
            return 1;
        }
    }
}
long rand_long(long low, long up) { return rand() % (up - low + 1) + low; }
int  is_prime_miller(long p, int k) {
    if (p == 2) {
        return 1;
    }
    if (!(p & 1) || p <= 1) { // on verifie que p est impair et different de 1
        return 0;
    }
    // on determine b etd:
    long b = 0;
    long d = p - 1;
    while (!(d & 1)) {
        // //tant que d n'est pas impair
        d = d / 2;
        b = b + 1; // On genere k valeurs
        // pour a,et on teste si c'est un temoin:
        long a;
        int  i;
        for (i = 0; i < k; i++) {
            a = rand_long(2, p - 1);
            if (witness(a, b, d, p)) {
                return 0;
            }
        }
        return 1;
    }
}

long random_prime_number(int low_size, int up_size, int k) {
    long n;
    while ((&n == NULL) || (is_prime_miller(n, k) == 0)) {
        n = (long) (((up_size - low_size) * ((float) rand()) / RAND_MAX)) + low_size;
    }
    return n;
}

int main(int argc, char const *argv[]) {
    int n, up_size = 100000, low_size = 100;
    srand(0);
    for (int i = 0; i < 100; i++) {
        n = (long) (((up_size - low_size) * ((float) rand()) / RAND_MAX)) + low_size;
        printf("%d\n", n);
    }
    return 0;
}
