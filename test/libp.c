#include "scr/libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void q1_5() {
    FILE *f = fopen("q1.5.csv", "w");
    fprintf(f, "m,time(ms)\n");
    time_t ini, final;
    long   a, m, n;
    long   N1 = 100000, N2 = 1000;
    for (m = 0; m < 1 << 16; m += 10) {
        a   = rand_long(1, 1 << 8);
        n   = rand_long(1, 1 << 8);
        ini = clock();
        for (int i = 0; i < N1; i++) {
            modpow(a, m, n);
        }
        final = clock();
        fprintf(f, "%ld,%f\n", m, ((double) (final - ini)) / N1);
        // fprintf(f, "%ld,%f,", m, ((double) (final - ini)) / N1);

        // ini = clock();
        // for (int i = 0; i < N2; i++) {
        //     modpow_naive(a, m, n);
        // }
        // final = clock();
        // fprintf(f, "%f\n", ((double) (final - ini)) / N2);
    }
    fclose(f);
}

void q1_2() {
    int  fin = 0, ini = 0, b = 0;
    long p, res;
    for (int i = 0; i < 100; i++) {
        fin = 0, ini = 0;
        p = 10001;
        while (fin - ini <= 2) {
            if (b) {
                res = p;
            }
            ini = clock();
            b   = is_prime_naive(p);
            fin = clock();
            p += 2;
        }
        printf("%ld\n", res);
    }
}

int main(int argc, char const *argv[]) {
    // q1_2();
    q1_5();
    return 0;
}
