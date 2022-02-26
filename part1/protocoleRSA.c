#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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
    int *v;
    int  t = (p - 1) * (q - 1);
    srand(0);
    // while () {
    //     /* code */
    // }

    while ((s == NULL) || (extended_gcd(s, t, u, v)) != 1) {
        *s = (long) ((t * ((float) rand()) / RAND_MAX));
    }
}