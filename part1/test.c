#include "libp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[]) {
    long num = 1;
    int  a   = 4;
    for (int i = 0; i < 19; i++) {
        num = num * a;
    }
    printf("%ld,%ld", num, num % 86);
    return 0;
}
