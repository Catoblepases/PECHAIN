#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define print_with_sepatator(...) printf("-----------%s-----------", __VA_ARGS__)

typedef struct _Key {
    long val;
    long n;
} Key;

char *f() {
    static char p[1 << 8];
    strcpy(p, "oooo");
    return p;
}

char *key_to_str_static(Key *key) {
    static char out[1 << 16];
    if (key == NULL) {
        strcpy(out, "null");
    } else {
        sprintf(out, "(%ld,%ld)", key->n, key->val);
    }
    return out;
}

void print_list_keys(Key *key) { printf("%s\n", key_to_str_static(key)); }

int main(int argc, char const *argv[]) {
    print_with_sepatator("j");
    char *s = f();
    Key *key = malloc(sizeof(Key));
    key->n = 10;
    key->val = 10;
    print_list_keys(key);

    key->n = 10;
    key->val = 10;
    print_list_keys(key);
    printf("%s\n", s);
    return 0;
}
