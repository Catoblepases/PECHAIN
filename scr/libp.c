#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

long modpow(long a, long m, long n) {
    a = a % n;
    if (m == 0) return 1;
    if (m == 1) return a;
    if (m % 2 == 0) {
        long x = modpow(a, m / 2, n);
        return (x * x) % n;
    } else {
        long x = modpow(a, m - 1, n);
        return (x * a) % n;
    }
}

int witness(long a, long b, long d, long p) {
    long x = modpow(a, d, p);
    if (x == 1) {
        return 0;
    }
    for (long i = 0; i < b; i++) {
        if (x == p - 1) {
            return 0;
        }
        x = modpow(x, 2, p);
    }
    return 1;
}

long rand_long(long low, long up) { return rand() % (up - low + 1) + low; }

int is_prime_miller(long p, int k) {
    if (p == 2) {
        return 1;
    }
    if (!(p & 1) || p <= 1) { // on verifie que p est impair et different de 1
        return 0;
    }
    // on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1)) { // tant que d n’est pas impair
        d = d / 2;
        b = b + 1;
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int  i;
    for (i = 0; i < k; i++) {
        a = rand_long(2, p - 1);
        if (witness(a, b, d, p)) return 0;
    }
    return 1;
}

long random_prime_number(int low_size, int up_size, int k) {
    if (up_size > 32) {
        up_size = 32;
    }
    if (low_size < 0) {
        low_size = 0;
    }
    long n   = rand_long(1 << low_size, 1 << up_size);
    long num = 0;
    while (is_prime_miller(n, k) == 0) {
        if (num++ >= (1 << 16)) {
            printf("erreur after %ld\n", num);
            exit(-1);
        }
        n = rand_long(1 << low_size, 1 << up_size);
    }
    return n;
}
