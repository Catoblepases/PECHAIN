#include "scr/prime.h"
#include "scr/utility.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void q1_5() {
    FILE *f = fopen("./temp/q1_5.csv", "w");
    fprintf(f, "m,time1(ms),time2(ms)\n");
    time_t temp_initial, temp_final;
    long a, m, n;
    long N1 = 10000, N2 = 100;
    for (m = 0; m < UP_SIZE_TEST_MOD_POW; m += 10) {
        if (m > 1 << 8) {
            N1 = 100000;
            N2 = 1000;
        }
        a = rand_long(1, 1 << 8);
        n = rand_long(1, 1 << 8);
        temp_initial = clock();
        for (int i = 0; i < N1; i++) {
            modpow(a, m, n);
        }
        temp_final = clock();
        fprintf(f, "%ld,%f,", m, ((double) (temp_final - temp_initial)) / N1);
        temp_initial = clock();
        for (int i = 0; i < N2; i++) {
            modpow_naive(a, m, n);
        }
        temp_final = clock();
        fprintf(f, "%f\n", ((double) (temp_final - temp_initial)) / N2);
    }
    fclose(f);
}

void q1_2() {
    int temp_final = 0, temp_initial = 0, b = 0;
    long p, res;
    FILE *f = fopen("./temp/q1_2.csv", "w");
    fprintf(f, "m,time(ms)\n");
    for (int i = 0; i < 10; i++) {
        temp_final = 0, temp_initial = 0;
        p = 10001;
        while (temp_final - temp_initial <= 2) {
            if (b) {
                res = p;
            }
            temp_initial = clock();
            b = is_prime_naive(p);
            temp_final = clock();
            p += 2;
        }
        fprintf(f, "%i, %ld\n", i, res);
        printf("%i, %ld\n", i, res);
    }
    fclose(f);
}

void check_validity() {
    // is_prime_naive
    assert(is_prime_naive(1) == 0);
    assert(is_prime_naive(2) == 1);
    assert(is_prime_naive(42) == 0);
    assert(is_prime_naive(53) == 1);
    assert(is_prime_naive(199) == 1);
    assert(is_prime_naive(267) == 0);
    assert(is_prime_naive(977) == 1);
    assert(is_prime_naive(983) == 1);
    assert(is_prime_naive(2601) == 0);
    assert(is_prime_naive(3371) == 1);
    assert(is_prime_naive(3333) == 0);
    assert(is_prime_naive(7643) == 1);
    assert(is_prime_naive(17497) == 1);
    // modpow_naive
    assert(modpow_naive(2, 10, 255) == 4);
    assert(modpow_naive(5, 10, 56) == 9);
    assert(modpow_naive(7, 11, 33) == 7);
    assert(modpow_naive(3, 24, 22) == 15);
    assert(modpow_naive(53534, 0, 232) == 1);
    assert(modpow_naive(6, 4, 1296) == 0);
    assert(modpow_naive(8, 5, 7) == 1);
    assert(modpow_naive(12, 5, 2) == 0);
    // modpow
    assert(modpow(2, 10, 255) == 4);
    assert(modpow(5, 10, 56) == 9);
    assert(modpow(7, 11, 33) == 7);
    assert(modpow(3, 24, 22) == 15);
    assert(modpow(53534, 0, 232) == 1);
    assert(modpow(6, 4, 1296) == 0);
    assert(modpow(8, 5, 7) == 1);
    assert(modpow(12, 5, 2) == 0);
}

int main(int argc, char const *argv[]) {
    check_validity();
    q1_2();
    q1_5();
    return 0;
}
